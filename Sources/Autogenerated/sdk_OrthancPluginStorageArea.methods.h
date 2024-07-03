/**
 * SPDX-FileCopyrightText: 2020-2023 Osimis S.A., 2024-2024 Orthanc Team SRL, 2021-2024 Sebastien Jodogne, ICTEAM UCLouvain
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

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
static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaCreate(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaCreate() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  Py_buffer arg1;
  unsigned long long arg2 = 0;
  long int arg3 = 0;

  if (!PyArg_ParseTuple(args, "ss*Kl", &arg0, &arg1, &arg2, &arg3))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (4 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginStorageAreaCreate(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1.buf, arg2, static_cast<OrthancPluginContentType>(arg3));
  }
  PyBuffer_Release(&arg1);

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

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRead(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaRead() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  long int arg1 = 0;

  if (!PyArg_ParseTuple(args, "sl", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginStorageAreaRead(OrthancPlugins::GetGlobalContext(), *buffer, self->object_, arg0, static_cast<OrthancPluginContentType>(arg1));
  }
  
  if (code == OrthancPluginErrorCode_Success)
  {
    return PyBytes_FromStringAndSize(buffer.GetData(), buffer.GetSize());
  }
  else
  {
    PythonLock::RaiseException(code);
    return NULL;  
  }
}

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRemove(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaRemove() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  long int arg1 = 0;

  if (!PyArg_ParseTuple(args, "sl", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginStorageAreaRemove(OrthancPlugins::GetGlobalContext(), self->object_, arg0, static_cast<OrthancPluginContentType>(arg1));
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

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginReconstructMainDicomTags(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginReconstructMainDicomTags() on object of class OrthancPluginStorageArea");

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

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginReconstructMainDicomTags(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginResourceType>(arg0));
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

