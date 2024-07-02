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
static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeersCount(
  sdk_OrthancPluginPeers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetPeersCount() on object of class OrthancPluginPeers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetPeersCount(OrthancPlugins::GetGlobalContext(), self->object_);
  }
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerName(
  sdk_OrthancPluginPeers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetPeerName() on object of class OrthancPluginPeers");

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

  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginGetPeerName(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
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

static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerUrl(
  sdk_OrthancPluginPeers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetPeerUrl() on object of class OrthancPluginPeers");

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

  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginGetPeerUrl(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
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

static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerUserProperty(
  sdk_OrthancPluginPeers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetPeerUserProperty() on object of class OrthancPluginPeers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ks", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginGetPeerUserProperty(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
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

