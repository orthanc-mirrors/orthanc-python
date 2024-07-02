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
static PyObject *sdk_OrthancPluginWorklistQuery_OrthancPluginWorklistIsMatch(
  sdk_OrthancPluginWorklistQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginWorklistIsMatch() on object of class OrthancPluginWorklistQuery");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "s*", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginWorklistIsMatch(OrthancPlugins::GetGlobalContext(), self->object_, arg0.buf, arg0.len);
  }
  PyBuffer_Release(&arg0);
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginWorklistQuery_OrthancPluginWorklistGetDicomQuery(
  sdk_OrthancPluginWorklistQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginWorklistGetDicomQuery() on object of class OrthancPluginWorklistQuery");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginWorklistGetDicomQuery(OrthancPlugins::GetGlobalContext(), *buffer, self->object_);
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

