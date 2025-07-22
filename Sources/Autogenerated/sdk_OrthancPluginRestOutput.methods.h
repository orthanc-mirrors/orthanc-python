/**
 * SPDX-FileCopyrightText: 2020-2023 Osimis S.A., 2024-2025 Orthanc Team SRL, 2021-2025 Sebastien Jodogne, ICTEAM UCLouvain
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2023 Osimis S.A., Belgium
 * Copyright (C) 2024-2025 Orthanc Team SRL, Belgium
 * Copyright (C) 2021-2025 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginAnswerBuffer(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginAnswerBuffer() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  Py_buffer arg0;
  const char* arg2 = NULL;

  if (!PyArg_ParseTuple(args, "z*s", &arg0, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginAnswerBuffer(OrthancPlugins::GetGlobalContext(), self->object_, (arg0.len > 0 ? arg0.buf : NULL), (arg0.len > 0 ? arg0.len : 0), arg2);
  }
  PyBuffer_Release(&arg0);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerPngImage(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginCompressAndAnswerPngImage() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;
  unsigned long arg1 = 0;
  unsigned long arg2 = 0;
  unsigned long arg3 = 0;
  Py_buffer arg4;

  if (!PyArg_ParseTuple(args, "lkkkz*", &arg0, &arg1, &arg2, &arg3, &arg4))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (5 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginCompressAndAnswerPngImage(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginPixelFormat>(arg0), arg1, arg2, arg3, arg4.buf);
  }
  PyBuffer_Release(&arg4);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginRedirect(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginRedirect() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginRedirect(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatusCode(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSendHttpStatusCode() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned short arg0 = 0;

  if (!PyArg_ParseTuple(args, "H", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSendHttpStatusCode(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendUnauthorized(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSendUnauthorized() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSendUnauthorized(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendMethodNotAllowed(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSendMethodNotAllowed() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSendMethodNotAllowed(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetCookie(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSetCookie() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSetCookie(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetHttpHeader(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSetHttpHeader() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSetHttpHeader(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginStartMultipartAnswer(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStartMultipartAnswer() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginStartMultipartAnswer(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
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

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendMultipartItem(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSendMultipartItem() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "z*", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginSendMultipartItem(OrthancPlugins::GetGlobalContext(), self->object_, (arg0.len > 0 ? arg0.buf : NULL), (arg0.len > 0 ? arg0.len : 0));
  }
  PyBuffer_Release(&arg0);

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

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatus(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSendHttpStatus() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned short arg0 = 0;
  Py_buffer arg1;

  if (!PyArg_ParseTuple(args, "Hz*", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSendHttpStatus(OrthancPlugins::GetGlobalContext(), self->object_, arg0, (arg1.len > 0 ? arg1.buf : NULL), (arg1.len > 0 ? arg1.len : 0));
  }
  PyBuffer_Release(&arg1);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerJpegImage(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginCompressAndAnswerJpegImage() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;
  unsigned long arg1 = 0;
  unsigned long arg2 = 0;
  unsigned long arg3 = 0;
  Py_buffer arg4;
  unsigned char arg5 = 0;

  if (!PyArg_ParseTuple(args, "lkkkz*b", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (6 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginCompressAndAnswerJpegImage(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginPixelFormat>(arg0), arg1, arg2, arg3, arg4.buf, arg5);
  }
  PyBuffer_Release(&arg4);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetHttpErrorDetails(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSetHttpErrorDetails() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  unsigned char arg1 = 0;

  if (!PyArg_ParseTuple(args, "sb", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSetHttpErrorDetails(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginStartStreamAnswer(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStartStreamAnswer() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginStartStreamAnswer(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
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

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendStreamChunk(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSendStreamChunk() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "z*", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginSendStreamChunk(OrthancPlugins::GetGlobalContext(), self->object_, (arg0.len > 0 ? arg0.buf : NULL), (arg0.len > 0 ? arg0.len : 0));
  }
  PyBuffer_Release(&arg0);

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

