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


#include "ICallbackRegistration.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"
#include "PythonLock.h"

PyObject *ICallbackRegistration::Apply(ICallbackRegistration& registration,
                                       PyObject* args,
                                       PyObject*& singletonCallback,
                                       const std::string& details)
{
  // https://docs.python.org/3/extending/extending.html#calling-python-functions-from-c
  PyObject* callback = NULL;

  if (!PyArg_ParseTuple(args, "O", &callback) ||
      callback == NULL)
  {
    const std::string message = "Expected a callback function to register one " + details;
    PyErr_SetString(PyExc_ValueError, message.c_str());
    return NULL;
  }
  else if (singletonCallback != NULL)
  {
    const std::string message = "Can only register one " + details;
    PyErr_SetString(PyExc_RuntimeError, message.c_str());
    return NULL;
  }
  else
  {
    OrthancPlugins::LogInfo("Registering one " + details);
    registration.Register();
    
    singletonCallback = callback;
    Py_XINCREF(singletonCallback);
  
    Py_INCREF(Py_None);
    return Py_None;
  }
}


PyObject *ICallbackRegistration::Apply2(ICallbackRegistration& registration,
                                        PyObject* args,
                                        PyObject*& singletonCallback1,
                                        PyObject*& singletonCallback2,
                                        const std::string& details)
{
  // https://docs.python.org/3/extending/extending.html#calling-python-functions-from-c
  PyObject* callback1 = NULL;
  PyObject* callback2 = NULL;

  if (!PyArg_ParseTuple(args, "OO", &callback1, &callback2) ||
      callback1 == NULL || callback2 == NULL)
  {
    const std::string message = "Expected two callback functions to register " + details;
    PyErr_SetString(PyExc_ValueError, message.c_str());
    return NULL;
  }
  else if (singletonCallback1 != NULL || singletonCallback2 != NULL)
  {
    const std::string message = "Can only register once for " + details;
    PyErr_SetString(PyExc_RuntimeError, message.c_str());
    return NULL;
  }
  else
  {
    OrthancPlugins::LogInfo("Registering callbacks " + details);
    registration.Register();

    singletonCallback1 = callback1;
    Py_XINCREF(singletonCallback1);

    singletonCallback2 = callback2;
    Py_XINCREF(singletonCallback2);

    Py_INCREF(Py_None);
    return Py_None;
  }
}


void ICallbackRegistration::Unregister(PyObject*& singletonCallback)
{
  PythonLock lock;
        
  if (singletonCallback != NULL)
  {
    Py_XDECREF(singletonCallback);
  }
}
