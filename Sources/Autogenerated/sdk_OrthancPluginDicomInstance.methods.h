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
static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceRemoteAet(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceRemoteAet() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginGetInstanceRemoteAet(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  if (s == NULL)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    return PyUnicode_FromString(s);
  }
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceSize(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceSize() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetInstanceSize(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceJson(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceJson() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetInstanceJson(OrthancPlugins::GetGlobalContext(), self->object_));
  }
  
  if (s.GetContent() == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;
  }
  else
  {
    return PyUnicode_FromString(s.GetContent());
  }
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceSimplifiedJson(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceSimplifiedJson() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetInstanceSimplifiedJson(OrthancPlugins::GetGlobalContext(), self->object_));
  }
  
  if (s.GetContent() == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;
  }
  else
  {
    return PyUnicode_FromString(s.GetContent());
  }
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginHasInstanceMetadata(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginHasInstanceMetadata() on object of class OrthancPluginDicomInstance");

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

  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginHasInstanceMetadata(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceMetadata(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceMetadata() on object of class OrthancPluginDicomInstance");

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

  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginGetInstanceMetadata(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  }
  
  if (s == NULL)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    return PyUnicode_FromString(s);
  }
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceOrigin(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceOrigin() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPluginInstanceOrigin value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetInstanceOrigin(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceTransferSyntaxUid(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceTransferSyntaxUid() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetInstanceTransferSyntaxUid(OrthancPlugins::GetGlobalContext(), self->object_));
  }
  
  if (s.GetContent() == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;
  }
  else
  {
    return PyUnicode_FromString(s.GetContent());
  }
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginHasInstancePixelData(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginHasInstancePixelData() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginHasInstancePixelData(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceFramesCount(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceFramesCount() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetInstanceFramesCount(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceRawFrame(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceRawFrame() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginGetInstanceRawFrame(OrthancPlugins::GetGlobalContext(), *buffer, self->object_, arg0);
  }
  
  if (code == OrthancPluginErrorCode_Success)
  {
    return PyBytes_FromStringAndSize(reinterpret_cast<const char*>(buffer.GetData()), buffer.GetSize());
  }
  else
  {
    PythonLock::RaiseException(code);
    return NULL;  
  }
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceDecodedFrame(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceDecodedFrame() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginImage* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginGetInstanceDecodedFrame(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
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

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginSerializeDicomInstance(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSerializeDicomInstance() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginSerializeDicomInstance(OrthancPlugins::GetGlobalContext(), *buffer, self->object_);
  }
  
  if (code == OrthancPluginErrorCode_Success)
  {
    return PyBytes_FromStringAndSize(reinterpret_cast<const char*>(buffer.GetData()), buffer.GetSize());
  }
  else
  {
    PythonLock::RaiseException(code);
    return NULL;  
  }
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceAdvancedJson(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceAdvancedJson() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;
  long int arg1 = 0;
  unsigned long arg2 = 0;

  if (!PyArg_ParseTuple(args, "llk", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetInstanceAdvancedJson(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginDicomToJsonFormat>(arg0), static_cast<OrthancPluginDicomToJsonFlags>(arg1), arg2));
  }
  
  if (s.GetContent() == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;
  }
  else
  {
    return PyUnicode_FromString(s.GetContent());
  }
}

