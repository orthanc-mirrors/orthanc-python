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


// Forward declaration of the autogenerated methods
static PyObject *sdk_OrthancPluginWorklistQuery_OrthancPluginWorklistIsMatch(
  sdk_OrthancPluginWorklistQuery_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginWorklistQuery_OrthancPluginWorklistGetDicomQuery(
  sdk_OrthancPluginWorklistQuery_Object* self, PyObject *args);
// End of forward declarations


// Forward declaration of the custom methods
// End of forward declarations


static PyMethodDef sdk_OrthancPluginWorklistQuery_Methods[] = {
  { "WorklistIsMatch",
    (PyCFunction) sdk_OrthancPluginWorklistQuery_OrthancPluginWorklistIsMatch, METH_VARARGS,
    "Generated from C function OrthancPluginWorklistIsMatch()" },
  { "WorklistGetDicomQuery",
    (PyCFunction) sdk_OrthancPluginWorklistQuery_OrthancPluginWorklistGetDicomQuery, METH_VARARGS,
    "Generated from C function OrthancPluginWorklistGetDicomQuery()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginWorklistQuery_Constructor(
  sdk_OrthancPluginWorklistQuery_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginWorklistQuery");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginWorklistQuery*>(static_cast<intptr_t>(object));
    self->borrowed_ = borrowed;
    return 0;
  }
  else
  {
    PyErr_SetString(PyExc_ValueError, "Expected a pair (pointer, borrowed) in the constructor");
    return -1;
  }
}


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginWorklistQuery_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.WorklistQuery",    /* tp_name */
  sizeof(sdk_OrthancPluginWorklistQuery_Object), /* tp_basicsize */
};




static void RegisterOrthancPluginWorklistQueryClass(PyObject* module)
{
  sdk_OrthancPluginWorklistQuery_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginWorklistQuery_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginWorklistQuery_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginWorklistQuery";
  sdk_OrthancPluginWorklistQuery_Type.tp_methods = sdk_OrthancPluginWorklistQuery_Methods;
  sdk_OrthancPluginWorklistQuery_Type.tp_init = (initproc) sdk_OrthancPluginWorklistQuery_Constructor;

  
  if (PyType_Ready(&sdk_OrthancPluginWorklistQuery_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python class: OrthancPluginWorklistQuery");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginWorklistQuery_Type);
  if (PyModule_AddObject(module, "WorklistQuery", (PyObject *)&sdk_OrthancPluginWorklistQuery_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python class: OrthancPluginWorklistQuery");
    Py_DECREF(&sdk_OrthancPluginWorklistQuery_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyTypeObject* GetOrthancPluginWorklistQueryType()
{
  return &sdk_OrthancPluginWorklistQuery_Type;
}
