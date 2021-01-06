/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2021 Osimis S.A., Belgium
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


#include "IncomingHttpRequestFilter.h"

#include "PythonString.h"
#include "Autogenerated/sdk.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"


static PyObject*  incomingHttpRequestFilter_ = NULL;


static int32_t IncomingHttpRequestFilter(OrthancPluginHttpMethod method,
                                         const char *uri,
                                         const char *ip,
                                         uint32_t headersCount,
                                         const char *const *headersKeys,
                                         const char *const *headersValues,
                                         uint32_t getArgumentsCount,
                                         const char *const *getArgumentsKeys,
                                         const char *const *getArgumentsValues)
{
  try
  {
    PythonLock lock;

    PythonObject args(lock, PyTuple_New(1));

    {
      PythonString str(lock, uri);
      PyTuple_SetItem(args.GetPyObject(), 0, str.Release());
    }

    PythonObject kw(lock, PyDict_New());
    PyDict_SetItemString(kw.GetPyObject(), "method", PyLong_FromLong(method));

    {
      PythonString str(lock, ip);
      PyDict_SetItemString(kw.GetPyObject(), "ip", str.Release());
    }

    {
      PythonObject headers(lock, PyDict_New());

      for (uint32_t i = 0; i < headersCount; i++)
      {
        PythonString str(lock, headersValues[i]);
        PyDict_SetItemString(headers.GetPyObject(), headersKeys[i], str.Release());
      }

      PyDict_SetItemString(kw.GetPyObject(), "headers", headers.Release());
    }

    if (method == OrthancPluginHttpMethod_Get)
    {
      PythonObject getArguments(lock, PyDict_New());

      for (uint32_t i = 0; i < getArgumentsCount; i++)
      {
        PythonString str(lock, getArgumentsValues[i]);
        PyDict_SetItemString(getArguments.GetPyObject(), getArgumentsKeys[i], str.Release());
      }

      PyDict_SetItemString(kw.GetPyObject(), "get", getArguments.Release());
    }
    
    PythonObject result(lock, PyObject_Call(incomingHttpRequestFilter_,
                                            args.GetPyObject(), kw.GetPyObject()));

    std::string traceback;
    if (lock.HasErrorOccurred(traceback))
    {
      OrthancPlugins::LogError("Error in the Python incoming-http-request filter, "
                               "traceback:\n" + traceback);
      return -1;
    }
    else
    {
      if (PyBool_Check(result.GetPyObject()))
      {
        return (PyObject_IsTrue(result.GetPyObject()) ? 1 /* allowed */ : 0 /* forbidden */);
      }
      else
      {
        OrthancPlugins::LogError("The Python incoming-http-request filter has not returned a Boolean");
        return -1;
      }
    }
  }
  catch (OrthancPlugins::PluginException& e)
  {
    OrthancPlugins::LogError("Exception in the Python incoming-http-request filter: " +
                             std::string(e.What(OrthancPlugins::GetGlobalContext())));
    return e.GetErrorCode();
  }
}

   
PyObject* RegisterIncomingHttpRequestFilter(PyObject* module, PyObject* args)
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

  if (incomingHttpRequestFilter_ != NULL)
  {
    PyErr_SetString(PyExc_RuntimeError, "Can only register one Python incoming-http-request filter");
    return NULL;
  }
  
  OrthancPlugins::LogInfo("Registering a Python incoming-http-request filter");

  OrthancPluginRegisterIncomingHttpRequestFilter2(
    OrthancPlugins::GetGlobalContext(), IncomingHttpRequestFilter);

  incomingHttpRequestFilter_ = callback;
  Py_XINCREF(incomingHttpRequestFilter_);
  
  Py_INCREF(Py_None);
  return Py_None;
}


void FinalizeIncomingHttpRequestFilter()
{
  PythonLock lock;
        
  if (incomingHttpRequestFilter_ != NULL)
  {
    Py_XDECREF(incomingHttpRequestFilter_);
  }
}
