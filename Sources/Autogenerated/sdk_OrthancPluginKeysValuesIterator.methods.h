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
static PyObject *sdk_OrthancPluginKeysValuesIterator_OrthancPluginKeysValuesIteratorGetKey(
  sdk_OrthancPluginKeysValuesIterator_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginKeysValuesIteratorGetKey() on object of class OrthancPluginKeysValuesIterator");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginKeysValuesIteratorGetKey(OrthancPlugins::GetGlobalContext(), self->object_);
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

static PyObject *sdk_OrthancPluginKeysValuesIterator_OrthancPluginKeysValuesIteratorGetValue(
  sdk_OrthancPluginKeysValuesIterator_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginKeysValuesIteratorGetValue() on object of class OrthancPluginKeysValuesIterator");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginKeysValuesIteratorGetValue(OrthancPlugins::GetGlobalContext(), *buffer, self->object_);
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

