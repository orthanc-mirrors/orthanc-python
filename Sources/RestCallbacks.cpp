/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2023 Osimis S.A., Belgium
 * Copyright (C) 2021-2023 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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


#include "RestCallbacks.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"
#include "Autogenerated/sdk.h"
#include "PythonString.h"

#include <boost/regex.hpp>


class RestCallback : public boost::noncopyable
{
private:
  boost::regex  regex_;
  PyObject*     callback_;

public:
  RestCallback(const std::string& uri,
               PyObject* callback) :
    regex_(uri),
    callback_(callback)
  {
    Py_XINCREF(callback_);
  }

  ~RestCallback()
  {
    Py_XDECREF(callback_);
  }

  bool IsMatch(const std::string& uri) const
  {
    return boost::regex_match(uri, regex_);
  }

  PyObject* GetCallback()
  {
    return callback_;
  }
};


// Concurrent accesses to the callbacks are protected by the
// "PythonLock" (GIL mutex)
static std::list<RestCallback*> restCallbacks_;


void RestCallbackHandler(OrthancPluginRestOutput* output,
                         const char* uri,
                         const OrthancPluginHttpRequest* request)
{
  PythonLock lock;

  for (std::list<RestCallback*>::const_iterator it = restCallbacks_.begin();
       it != restCallbacks_.end(); ++it)
  {
    assert(*it != NULL);
    if ((*it)->IsMatch(uri))
    {
      /**
       * Construct an instance object of the "orthanc.RestOutput"
       * class. This is done by calling the constructor function
       * "sdk_OrthancPluginRestOutput_Type".
       **/
      PythonObject args(lock, PyTuple_New(2));
      PyTuple_SetItem(args.GetPyObject(), 0, PyLong_FromSsize_t((intptr_t) output));
      PyTuple_SetItem(args.GetPyObject(), 1, PyBool_FromLong(true /* borrowed, don't destruct */));
      PyObject *pInst = PyObject_CallObject((PyObject*) GetOrthancPluginRestOutputType(), args.GetPyObject());


      /**
       * Construct the arguments tuple (output, uri)
       **/
      PythonString str(lock, uri);
      
      PythonObject args2(lock, PyTuple_New(2));
      PyTuple_SetItem(args2.GetPyObject(), 0, pInst);
      PyTuple_SetItem(args2.GetPyObject(), 1, str.Release());
      // No need to decrement refcount with "PyTuple_SetItem()"

      /**
       * Construct the named arguments from the "request" argument
       **/
      const char* method;
      switch (request->method)
      {
        case OrthancPluginHttpMethod_Get:
          method = "GET";
          break;

        case OrthancPluginHttpMethod_Post:
          method = "POST";
          break;

        case OrthancPluginHttpMethod_Put:
          method = "PUT";
          break;

        case OrthancPluginHttpMethod_Delete:
          method = "DELETE";
          break;

        default:
          ORTHANC_PLUGINS_THROW_EXCEPTION(ParameterOutOfRange);
      }

      PythonObject kw(lock, PyDict_New());

      {
        PythonString tmp(lock, method);
        PyDict_SetItemString(kw.GetPyObject(), "method", tmp.Release());
      }

      {
        PythonObject groups(lock, PyTuple_New(request->groupsCount));

        for (uint32_t i = 0; i < request->groupsCount; i++)
        {
          PythonString tmp(lock, request->groups[i]);
          PyTuple_SetItem(groups.GetPyObject(), i, tmp.Release());
        }

        PyDict_SetItemString(kw.GetPyObject(), "groups", groups.Release());
      }

      if (request->method == OrthancPluginHttpMethod_Get)
      {
        PythonObject get(lock, PyDict_New());

        for (uint32_t i = 0; i < request->getCount; i++)
        {
          PythonString value(lock, request->getValues[i]);
          PyDict_SetItemString(get.GetPyObject(), request->getKeys[i], value.Release());
        }

        PyDict_SetItemString(kw.GetPyObject(), "get", get.Release());
      }

      {
        PythonObject headers(lock, PyDict_New());

        for (uint32_t i = 0; i < request->headersCount; i++)
        {
          PythonString value(lock, request->headersValues[i]);
          PyDict_SetItemString(headers.GetPyObject(), request->headersKeys[i], value.Release());
        }

        PyDict_SetItemString(kw.GetPyObject(), "headers", headers.Release());
      }

      if (request->method == OrthancPluginHttpMethod_Post ||
          request->method == OrthancPluginHttpMethod_Put)
      {
        PyDict_SetItemString(kw.GetPyObject(), "body", PyBytes_FromStringAndSize(
                               reinterpret_cast<const char*>(request->body), request->bodySize));
      }

      /**
       * Call the user-defined function
       **/
      PythonObject result(lock, PyObject_Call(
                            (*it)->GetCallback(), args2.GetPyObject(), kw.GetPyObject()));

      std::string traceback;
      if (lock.HasErrorOccurred(traceback))
      {
        OrthancPlugins::LogError("Error in the REST callback, traceback:\n" + traceback);
        ORTHANC_PLUGINS_THROW_EXCEPTION(Plugin);
      }

      return;
    }
  }

  // Should never happen
  OrthancPlugins::LogError("Unable to find the Python handler for URI: " + std::string(uri));
  ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
}



PyObject* RegisterRestCallback(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")
  
  // https://docs.python.org/3/extending/extending.html#calling-python-functions-from-c
  const char* uri = NULL;
  PyObject* callback = NULL;

  if (!PyArg_ParseTuple(args, "sO", &uri, &callback) ||
      uri == NULL ||
      callback == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Expected a string (URI) and a callback function");
    return NULL;
  }
  
  OrthancPlugins::LogInfo("Registering a Python REST callback on URI: " + std::string(uri));
  OrthancPlugins::RegisterRestCallback<RestCallbackHandler>(uri, true /* thread safe */);
  
  restCallbacks_.push_back(new RestCallback(uri, callback));

  Py_INCREF(Py_None);
  return Py_None;
}



void FinalizeRestCallbacks()
{
  PythonLock lock;
        
  for (std::list<RestCallback*>::iterator it = restCallbacks_.begin();
       it != restCallbacks_.end(); ++it)
  {
    assert(*it != NULL);
    delete *it;
  }

  restCallbacks_.clear();
}
