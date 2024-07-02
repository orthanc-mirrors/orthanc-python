/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2023 Osimis S.A., Belgium
 * Copyright (C) 2024-2024 Orthanc Team SRL, Belgium
 * Copyright (C) 2021-2024 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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


// WARNING: Auto-generated file. Do not modify it by hand.


// Actual implementation of the methods
static PyObject *sdk_OrthancPluginImage_OrthancPluginGetImagePixelFormat(
  sdk_OrthancPluginImage_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetImagePixelFormat() on object of class OrthancPluginImage");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPluginPixelFormat value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetImagePixelFormat(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginImage_OrthancPluginGetImageWidth(
  sdk_OrthancPluginImage_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetImageWidth() on object of class OrthancPluginImage");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetImageWidth(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginImage_OrthancPluginGetImageHeight(
  sdk_OrthancPluginImage_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetImageHeight() on object of class OrthancPluginImage");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetImageHeight(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginImage_OrthancPluginGetImagePitch(
  sdk_OrthancPluginImage_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetImagePitch() on object of class OrthancPluginImage");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetImagePitch(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginImage_OrthancPluginConvertPixelFormat(
  sdk_OrthancPluginImage_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginConvertPixelFormat() on object of class OrthancPluginImage");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;

  if (!PyArg_ParseTuple(args, "l", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginImage* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginConvertPixelFormat(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginPixelFormat>(arg0));
  }
  
  if (obj == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;  
  }
  else
  {
    PyObject *argList = Py_BuildValue("Lb", obj, false /* not borrowed */);
    PyObject *python = PyObject_CallObject((PyObject *) &sdk_OrthancPluginImage_Type, argList);
    Py_DECREF(argList);
    return python;
  }
}

static PyObject *sdk_OrthancPluginImage_OrthancPluginDrawText(
  sdk_OrthancPluginImage_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginDrawText() on object of class OrthancPluginImage");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;
  const char* arg1 = NULL;
  long int arg2 = 0;
  long int arg3 = 0;
  unsigned char arg4 = 0;
  unsigned char arg5 = 0;
  unsigned char arg6 = 0;

  if (!PyArg_ParseTuple(args, "ksllbbb", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5, &arg6))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (7 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginDrawText(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
  }
  

  if (code == OrthancPluginErrorCode_Success)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    PythonLock::RaiseException(code);
    return NULL;
  }
}

