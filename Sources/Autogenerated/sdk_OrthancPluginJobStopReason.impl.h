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


typedef struct 
{
  PyObject_HEAD
} sdk_OrthancPluginJobStopReason_Object;


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginJobStopReason_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.JobStopReason",    /* tp_name */
  sizeof(sdk_OrthancPluginJobStopReason_Object), /* tp_basicsize */
};


void RegisterOrthancPluginJobStopReasonEnumeration(PyObject* module)
{
  sdk_OrthancPluginJobStopReason_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginJobStopReason_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginJobStopReason_Type.tp_doc = "Generated from C enumeration OrthancPluginOrthancPluginJobStopReason";  

  sdk_OrthancPluginJobStopReason_Type.tp_dict = PyDict_New();
  
  if (PyType_Ready(&sdk_OrthancPluginJobStopReason_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python enumeration: OrthancPluginJobStopReason");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  /**
   * Declare constants here (static members = class attributes)
   * https://stackoverflow.com/a/8017906/881731
   *
   * "Static and class methods can be defined in tp_methods by adding
   * METH_STATIC or METH_CLASS to the ml_flags field of the
   * PyMethodDef structure. This is equivalent to @staticmethod and
   * @classmethod decorators."
   *
   * "Class attributes can be added by setting the tp_dict to a
   * dictionary with these attributes before calling PyType_Ready()
   * (in your module initialization function)."
   **/
  
  {
    PyObject* tmp = PyLong_FromLong(1);
    PyDict_SetItemString(sdk_OrthancPluginJobStopReason_Type.tp_dict, "SUCCESS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2);
    PyDict_SetItemString(sdk_OrthancPluginJobStopReason_Type.tp_dict, "PAUSED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(3);
    PyDict_SetItemString(sdk_OrthancPluginJobStopReason_Type.tp_dict, "FAILURE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(4);
    PyDict_SetItemString(sdk_OrthancPluginJobStopReason_Type.tp_dict, "CANCELED", tmp);
    Py_DECREF(tmp);
  }


  Py_INCREF(&sdk_OrthancPluginJobStopReason_Type);
  if (PyModule_AddObject(module, "JobStopReason", (PyObject *)&sdk_OrthancPluginJobStopReason_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python enumeration: OrthancPluginJobStopReason");
    Py_DECREF(&sdk_OrthancPluginJobStopReason_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}
