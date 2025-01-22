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


typedef struct 
{
  PyObject_HEAD
} sdk_OrthancPluginErrorCode_Object;


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginErrorCode_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.ErrorCode",    /* tp_name */
  sizeof(sdk_OrthancPluginErrorCode_Object), /* tp_basicsize */
};


void RegisterOrthancPluginErrorCodeEnumeration(PyObject* module)
{
  sdk_OrthancPluginErrorCode_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginErrorCode_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginErrorCode_Type.tp_doc = "Generated from C enumeration OrthancPluginOrthancPluginErrorCode";  

  sdk_OrthancPluginErrorCode_Type.tp_dict = PyDict_New();
  
  if (PyType_Ready(&sdk_OrthancPluginErrorCode_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python enumeration: OrthancPluginErrorCode");
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
    PyObject* tmp = PyLong_FromLong(-1);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INTERNAL_ERROR", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(0);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SUCCESS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "PLUGIN", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NOT_IMPLEMENTED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(3);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "PARAMETER_OUT_OF_RANGE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(4);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NOT_ENOUGH_MEMORY", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(5);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_PARAMETER_TYPE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(6);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_SEQUENCE_OF_CALLS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(7);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INEXISTENT_ITEM", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(8);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_REQUEST", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(9);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NETWORK_PROTOCOL", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(10);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SYSTEM_COMMAND", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(11);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(12);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "URI_SYNTAX", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(13);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INEXISTENT_FILE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(14);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_WRITE_FILE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(15);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_FILE_FORMAT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(16);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "TIMEOUT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(17);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNKNOWN_RESOURCE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(18);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INCOMPATIBLE_DATABASE_VERSION", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(19);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "FULL_STORAGE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(20);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CORRUPTED_FILE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(21);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INEXISTENT_TAG", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(22);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "READ_ONLY", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(23);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INCOMPATIBLE_IMAGE_FORMAT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(24);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INCOMPATIBLE_IMAGE_SIZE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(25);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SHARED_LIBRARY", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(26);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNKNOWN_PLUGIN_SERVICE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(27);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNKNOWN_DICOM_TAG", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(28);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_JSON", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(29);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNAUTHORIZED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(30);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_FONT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(31);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_PLUGIN", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(32);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "STORAGE_AREA_PLUGIN", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(33);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "EMPTY_REQUEST", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(34);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NOT_ACCEPTABLE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(35);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NULL_POINTER", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(36);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_UNAVAILABLE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(37);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANCELED_JOB", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(38);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_GEOMETRY", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(39);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SSL_INITIALIZATION", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(40);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DISCONTINUED_ABI", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(41);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_RANGE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(42);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_CANNOT_SERIALIZE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(43);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "REVISION", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(44);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "MAIN_DICOM_TAGS_MULTIPLY_DEFINED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(45);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "FORBIDDEN_ACCESS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(46);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DUPLICATE_RESOURCE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(47);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INCOMPATIBLE_CONFIGURATIONS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1000);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_NOT_OPENED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1001);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_ALREADY_OPENED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1002);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_CANNOT_OPEN", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1003);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_STATEMENT_ALREADY_USED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1004);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_EXECUTE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1005);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_ROLLBACK_WITHOUT_TRANSACTION", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1006);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_COMMIT_WITHOUT_TRANSACTION", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1007);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_REGISTER_FUNCTION", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1008);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_FLUSH", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1009);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_CANNOT_RUN", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1010);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_CANNOT_STEP", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1011);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_BIND_OUT_OF_RANGE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1012);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_PREPARE_STATEMENT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1013);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_TRANSACTION_ALREADY_STARTED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1014);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_TRANSACTION_COMMIT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1015);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_TRANSACTION_BEGIN", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2000);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DIRECTORY_OVER_FILE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2001);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "FILE_STORAGE_CANNOT_WRITE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2002);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DIRECTORY_EXPECTED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2003);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "HTTP_PORT_IN_USE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2004);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DICOM_PORT_IN_USE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2005);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_HTTP_STATUS_IN_REST", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2006);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "REGULAR_FILE_EXPECTED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2007);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "PATH_TO_EXECUTABLE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2008);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "MAKE_DIRECTORY", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2009);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_APPLICATION_ENTITY_TITLE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2010);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_CFIND_HANDLER", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2011);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_CMOVE_HANDLER", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2012);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_CSTORE_HANDLER", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2013);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_APPLICATION_ENTITY_FILTER", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2014);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_SOP_CLASS_OR_INSTANCE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2015);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_PRESENTATION_CONTEXT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2016);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DICOM_FIND_UNAVAILABLE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2017);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DICOM_MOVE_UNAVAILABLE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2018);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_STORE_INSTANCE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2019);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_NOT_STRING", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2020);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_OVERRIDE_TAG", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2021);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_USE_CONTENT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2022);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_NO_PAYLOAD", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2023);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_USE_DATA_URI_SCHEME", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2024);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_BAD_PARENT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2025);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_PARENT_IS_INSTANCE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2026);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_PARENT_ENCODING", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2027);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNKNOWN_MODALITY", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2028);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_JOB_ORDERING", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2029);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "JSON_TO_LUA_TABLE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2030);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_CREATE_LUA", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2031);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_EXECUTE_LUA", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2032);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "LUA_ALREADY_EXECUTED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2033);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "LUA_BAD_OUTPUT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2034);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NOT_LUA_PREDICATE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2035);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "LUA_RETURNS_NO_STRING", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2036);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "STORAGE_AREA_ALREADY_REGISTERED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2037);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_BACKEND_ALREADY_REGISTERED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2038);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_NOT_INITIALIZED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2039);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SSL_DISABLED", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2040);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_ORDER_SLICES", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2041);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_WORKLIST_HANDLER", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2042);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "ALREADY_EXISTING_TAG", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2043);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_STORAGE_COMMITMENT_HANDLER", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2044);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_CGET_HANDLER", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2045);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DICOM_GET_UNAVAILABLE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(3000);
    PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNSUPPORTED_MEDIA_TYPE", tmp);
    Py_DECREF(tmp);
  }


  Py_INCREF(&sdk_OrthancPluginErrorCode_Type);
  if (PyModule_AddObject(module, "ErrorCode", (PyObject *)&sdk_OrthancPluginErrorCode_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python enumeration: OrthancPluginErrorCode");
    Py_DECREF(&sdk_OrthancPluginErrorCode_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}
