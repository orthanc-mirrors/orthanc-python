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
static PyObject *sdk_OrthancPluginFindAnswers_OrthancPluginFindAddAnswer(
  sdk_OrthancPluginFindAnswers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginFindAddAnswer() on object of class OrthancPluginFindAnswers");

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
    code = OrthancPluginFindAddAnswer(OrthancPlugins::GetGlobalContext(), self->object_, (arg0.len > 0 ? arg0.buf : NULL), (arg0.len > 0 ? arg0.len : 0));
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

static PyObject *sdk_OrthancPluginFindAnswers_OrthancPluginFindMarkIncomplete(
  sdk_OrthancPluginFindAnswers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginFindMarkIncomplete() on object of class OrthancPluginFindAnswers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginFindMarkIncomplete(OrthancPlugins::GetGlobalContext(), self->object_);
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

