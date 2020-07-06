/**
 * Python plugin for Orthanc
 * Copyright (C) 2017-2020 Osimis S.A., Belgium
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/


#include "OnChangeCallback.h"

#include "PythonObject.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"

#include <Compatibility.h>  // For std::unique_ptr<>

#include <boost/thread.hpp>


class PendingChange : public boost::noncopyable
{
private:
  OrthancPluginChangeType    changeType_;
  OrthancPluginResourceType  resourceType_;
  std::string                resourceId_;

public:
  PendingChange(OrthancPluginChangeType changeType,
                OrthancPluginResourceType resourceType,
                const char* resourceId) :
    changeType_(changeType),
    resourceType_(resourceType)
  {
    if (resourceId == NULL)
    {
      resourceId_.clear();
    }
    else
    {
      resourceId_.assign(resourceId);
    }
  }

  OrthancPluginChangeType  GetChangeType() const
  {
    return changeType_;
  }

  OrthancPluginResourceType  GetResourceType() const
  {
    return resourceType_;
  }

  const std::string& GetResourceId() const
  {
    return resourceId_;
  }
};



class PendingChanges : public boost::noncopyable
{
private:
  typedef std::list<PendingChange*>  Queue;
  
  boost::mutex               mutex_;
  Queue                      queue_;
  boost::condition_variable  elementAvailable_;

public:
  ~PendingChanges()
  {
    for (Queue::iterator it = queue_.begin(); it != queue_.end(); ++it)
    {
      assert(*it != NULL);
      delete *it;
    }
  }
  
  void Enqueue(OrthancPluginChangeType changeType,
               OrthancPluginResourceType resourceType,
               const char* resourceId)
  {
    boost::mutex::scoped_lock lock(mutex_);
    queue_.push_back(new PendingChange(changeType, resourceType, resourceId));
    elementAvailable_.notify_one();
  }

  PendingChange* Dequeue(unsigned int millisecondsTimeout)
  {
    if (millisecondsTimeout == 0)
    {
      ORTHANC_PLUGINS_THROW_EXCEPTION(ParameterOutOfRange);
    }
    
    boost::mutex::scoped_lock lock(mutex_);

    // Wait for a message to arrive in the FIFO queue
    while (queue_.empty())
    {
      bool success = elementAvailable_.timed_wait
        (lock, boost::posix_time::milliseconds(millisecondsTimeout));
      if (!success)
      {
        return NULL;
      }
    }

    std::unique_ptr<PendingChange> change(queue_.front());
    queue_.pop_front();

    return change.release();
  }
};



static PendingChanges  pendingChanges_;
static bool            stopping_ = false;
static boost::thread   changesThread_;
static PyObject*       changesCallback_ = NULL;


static void ChangesWorker()
{
  while (!stopping_)
  {
    for (;;)
    {
      std::unique_ptr<PendingChange> change(pendingChanges_.Dequeue(100));
      if (change.get() == NULL)
      {
        break;
      }
      else if (changesCallback_ != NULL)
      {
        try
        {
          PythonLock lock;
          PythonObject args(lock, PyTuple_New(3));
          PyTuple_SetItem(args.GetPyObject(), 0, PyLong_FromLong(change->GetChangeType()));
          PyTuple_SetItem(args.GetPyObject(), 1, PyLong_FromLong(change->GetResourceType()));
          PyTuple_SetItem(args.GetPyObject(), 2, PyUnicode_FromString(change->GetResourceId().c_str()));
          PythonObject result(lock, PyObject_CallObject(changesCallback_, args.GetPyObject()));

          std::string traceback;
          if (lock.HasErrorOccurred(traceback))
          {
            OrthancPlugins::LogError("Error in the Python on-change callback, "
                                     "traceback:\n" + traceback);
          }
        }
        catch (OrthancPlugins::PluginException& e)
        {
          OrthancPlugins::LogError("Error during Python on-change callback: " +
                                   std::string(e.What(OrthancPlugins::GetGlobalContext())));
        }
      }
    }
  }
}


static OrthancPluginErrorCode OnChangeCallback(OrthancPluginChangeType changeType,
                                               OrthancPluginResourceType resourceType,
                                               const char* resourceId)
{
  {
    PythonLock lock;
    pendingChanges_.Enqueue(changeType, resourceType, resourceId);
  }
  
  return OrthancPluginErrorCode_Success;
}


PyObject* RegisterOnChangeCallback(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")
  
  // https://docs.python.org/3/extending/extending.html#calling-python-functions-from-c
  PyObject* callback = NULL;

  if (!PyArg_ParseTuple(args, "O", &callback) ||
      callback == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a callback function");
    return NULL;
  }

  if (changesCallback_ != NULL)
  {
    PyErr_SetString(PyExc_RuntimeError, "Can only register one Python on-changes callback");
    return NULL;
  }
  
  OrthancPlugins::LogInfo("Registering a Python on-changes callback");

  OrthancPluginRegisterOnChangeCallback(OrthancPlugins::GetGlobalContext(), OnChangeCallback);

  stopping_ = false;
  changesThread_ = boost::thread(ChangesWorker);

  changesCallback_ = callback;
  Py_XINCREF(changesCallback_);
  
  Py_INCREF(Py_None);
  return Py_None;
}




void FinalizeOnChangeCallback()
{
  stopping_ = true;

  if (changesThread_.joinable())
  {
    changesThread_.join();
  }

  {
    PythonLock lock;
    
    if (changesCallback_ != NULL)
    {
      Py_XDECREF(changesCallback_);
    }
  }
}
