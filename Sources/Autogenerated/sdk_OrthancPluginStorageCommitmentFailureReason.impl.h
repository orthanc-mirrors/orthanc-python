/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2023 Osimis S.A., Belgium
 * Copyright (C) 2021-2023 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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


typedef struct 
{
  PyObject_HEAD
} sdk_OrthancPluginStorageCommitmentFailureReason_Object;


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginStorageCommitmentFailureReason_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.StorageCommitmentFailureReason",    /* tp_name */
  sizeof(sdk_OrthancPluginStorageCommitmentFailureReason_Object), /* tp_basicsize */
};


void RegisterOrthancPluginStorageCommitmentFailureReasonEnumeration(PyObject* module)
{
  sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_doc = "Generated from C enumeration OrthancPluginOrthancPluginStorageCommitmentFailureReason";  

  sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_dict = PyDict_New();
  
  if (PyType_Ready(&sdk_OrthancPluginStorageCommitmentFailureReason_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python enumeration: OrthancPluginStorageCommitmentFailureReason");
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
  
  PyDict_SetItemString(sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_dict, "SUCCESS", PyLong_FromLong(0));
  PyDict_SetItemString(sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_dict, "PROCESSING_FAILURE", PyLong_FromLong(1));
  PyDict_SetItemString(sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_dict, "NO_SUCH_OBJECT_INSTANCE", PyLong_FromLong(2));
  PyDict_SetItemString(sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_dict, "RESOURCE_LIMITATION", PyLong_FromLong(3));
  PyDict_SetItemString(sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_dict, "REFERENCED_SOPCLASS_NOT_SUPPORTED", PyLong_FromLong(4));
  PyDict_SetItemString(sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_dict, "CLASS_INSTANCE_CONFLICT", PyLong_FromLong(5));
  PyDict_SetItemString(sdk_OrthancPluginStorageCommitmentFailureReason_Type.tp_dict, "DUPLICATE_TRANSACTION_UID", PyLong_FromLong(6));

  Py_INCREF(&sdk_OrthancPluginStorageCommitmentFailureReason_Type);
  if (PyModule_AddObject(module, "StorageCommitmentFailureReason", (PyObject *)&sdk_OrthancPluginStorageCommitmentFailureReason_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python enumeration: OrthancPluginStorageCommitmentFailureReason");
    Py_DECREF(&sdk_OrthancPluginStorageCommitmentFailureReason_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}
