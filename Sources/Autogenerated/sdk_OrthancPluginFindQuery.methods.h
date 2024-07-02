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
static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQuerySize(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetFindQuerySize() on object of class OrthancPluginFindQuery");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetFindQuerySize(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryTagName(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetFindQueryTagName() on object of class OrthancPluginFindQuery");

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

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetFindQueryTagName(OrthancPlugins::GetGlobalContext(), self->object_, arg0));
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

static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryValue(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetFindQueryValue() on object of class OrthancPluginFindQuery");

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

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetFindQueryValue(OrthancPlugins::GetGlobalContext(), self->object_, arg0));
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

