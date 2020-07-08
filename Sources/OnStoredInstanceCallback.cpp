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


#include "OnStoredInstanceCallback.h"

#include "PythonObject.h"
#include "Autogenerated/sdk.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"


static PyObject*   storedInstanceCallback_ = NULL;


static OrthancPluginErrorCode OnStoredInstanceCallback(const OrthancPluginDicomInstance *instance,
                                                       const char *instanceId)
{
  try
  {
    PythonLock lock;

    /**
     * Construct an instance object of the "orthanc.RestOutput"
     * class. This is done by calling the constructor function
     * "sdk_OrthancPluginRestOutput_Type".
     **/
    PythonObject args(lock, PyTuple_New(2));
    PyTuple_SetItem(args.GetPyObject(), 0, PyLong_FromSsize_t((intptr_t) instance));
    PyTuple_SetItem(args.GetPyObject(), 1, PyBool_FromLong(true /* borrowed, don't destruct */));
    PyObject *pInst = PyObject_CallObject(GetOrthancPluginDicomInstanceType(), args.GetPyObject());
    
    /**
     * Construct the arguments tuple (output, uri)
     **/
    PythonObject args2(lock, PyTuple_New(2));
    PyTuple_SetItem(args2.GetPyObject(), 0, pInst);
    PyTuple_SetItem(args2.GetPyObject(), 1, PyUnicode_FromString(instanceId));

    PythonObject result(lock, PyObject_CallObject(storedInstanceCallback_, args2.GetPyObject()));

    std::string traceback;
    if (lock.HasErrorOccurred(traceback))
    {
      OrthancPlugins::LogError("Error in the Python on-change callback, "
                               "traceback:\n" + traceback);
      return OrthancPluginErrorCode_Plugin;
    }
    else
    {
      return OrthancPluginErrorCode_Success;
    }
  }
  catch (OrthancPlugins::PluginException& e)
  {
    return e.GetErrorCode();
  }
}

   
PyObject* RegisterOnStoredInstanceCallback(PyObject* module, PyObject* args)
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

  if (storedInstanceCallback_ != NULL)
  {
    PyErr_SetString(PyExc_RuntimeError, "Can only register one Python on-stored-instance callback");
    return NULL;
  }
  
  OrthancPlugins::LogInfo("Registering a Python on-stored-instance callback");

  OrthancPluginRegisterOnStoredInstanceCallback(
    OrthancPlugins::GetGlobalContext(), OnStoredInstanceCallback);

  storedInstanceCallback_ = callback;
  Py_XINCREF(storedInstanceCallback_);
  
  Py_INCREF(Py_None);
  return Py_None;
}


void FinalizeOnStoredInstanceCallback()
{
  PythonLock lock;
        
  if (storedInstanceCallback_ != NULL)
  {
    Py_XDECREF(storedInstanceCallback_);
  }
}
