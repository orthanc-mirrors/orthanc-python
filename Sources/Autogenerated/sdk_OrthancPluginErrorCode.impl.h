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
    OrthancPlugins::LogError("Cannot register Python enumeration: OrthancPluginErrorCode");
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
  
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INTERNAL_ERROR", PyLong_FromLong(-1));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SUCCESS", PyLong_FromLong(0));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "PLUGIN", PyLong_FromLong(1));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NOT_IMPLEMENTED", PyLong_FromLong(2));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "PARAMETER_OUT_OF_RANGE", PyLong_FromLong(3));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NOT_ENOUGH_MEMORY", PyLong_FromLong(4));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_PARAMETER_TYPE", PyLong_FromLong(5));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_SEQUENCE_OF_CALLS", PyLong_FromLong(6));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INEXISTENT_ITEM", PyLong_FromLong(7));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_REQUEST", PyLong_FromLong(8));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NETWORK_PROTOCOL", PyLong_FromLong(9));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SYSTEM_COMMAND", PyLong_FromLong(10));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE", PyLong_FromLong(11));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "URI_SYNTAX", PyLong_FromLong(12));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INEXISTENT_FILE", PyLong_FromLong(13));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_WRITE_FILE", PyLong_FromLong(14));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_FILE_FORMAT", PyLong_FromLong(15));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "TIMEOUT", PyLong_FromLong(16));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNKNOWN_RESOURCE", PyLong_FromLong(17));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INCOMPATIBLE_DATABASE_VERSION", PyLong_FromLong(18));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "FULL_STORAGE", PyLong_FromLong(19));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CORRUPTED_FILE", PyLong_FromLong(20));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INEXISTENT_TAG", PyLong_FromLong(21));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "READ_ONLY", PyLong_FromLong(22));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INCOMPATIBLE_IMAGE_FORMAT", PyLong_FromLong(23));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "INCOMPATIBLE_IMAGE_SIZE", PyLong_FromLong(24));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SHARED_LIBRARY", PyLong_FromLong(25));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNKNOWN_PLUGIN_SERVICE", PyLong_FromLong(26));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNKNOWN_DICOM_TAG", PyLong_FromLong(27));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_JSON", PyLong_FromLong(28));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNAUTHORIZED", PyLong_FromLong(29));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_FONT", PyLong_FromLong(30));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_PLUGIN", PyLong_FromLong(31));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "STORAGE_AREA_PLUGIN", PyLong_FromLong(32));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "EMPTY_REQUEST", PyLong_FromLong(33));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NOT_ACCEPTABLE", PyLong_FromLong(34));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NULL_POINTER", PyLong_FromLong(35));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_UNAVAILABLE", PyLong_FromLong(36));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANCELED_JOB", PyLong_FromLong(37));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_GEOMETRY", PyLong_FromLong(38));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SSL_INITIALIZATION", PyLong_FromLong(39));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DISCONTINUED_ABI", PyLong_FromLong(40));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_RANGE", PyLong_FromLong(41));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_CANNOT_SERIALIZE", PyLong_FromLong(42));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "REVISION", PyLong_FromLong(43));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_NOT_OPENED", PyLong_FromLong(1000));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_ALREADY_OPENED", PyLong_FromLong(1001));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_CANNOT_OPEN", PyLong_FromLong(1002));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_STATEMENT_ALREADY_USED", PyLong_FromLong(1003));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_EXECUTE", PyLong_FromLong(1004));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_ROLLBACK_WITHOUT_TRANSACTION", PyLong_FromLong(1005));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_COMMIT_WITHOUT_TRANSACTION", PyLong_FromLong(1006));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_REGISTER_FUNCTION", PyLong_FromLong(1007));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_FLUSH", PyLong_FromLong(1008));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_CANNOT_RUN", PyLong_FromLong(1009));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_CANNOT_STEP", PyLong_FromLong(1010));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_BIND_OUT_OF_RANGE", PyLong_FromLong(1011));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_PREPARE_STATEMENT", PyLong_FromLong(1012));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_TRANSACTION_ALREADY_STARTED", PyLong_FromLong(1013));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_TRANSACTION_COMMIT", PyLong_FromLong(1014));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SQLITE_TRANSACTION_BEGIN", PyLong_FromLong(1015));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DIRECTORY_OVER_FILE", PyLong_FromLong(2000));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "FILE_STORAGE_CANNOT_WRITE", PyLong_FromLong(2001));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DIRECTORY_EXPECTED", PyLong_FromLong(2002));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "HTTP_PORT_IN_USE", PyLong_FromLong(2003));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DICOM_PORT_IN_USE", PyLong_FromLong(2004));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_HTTP_STATUS_IN_REST", PyLong_FromLong(2005));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "REGULAR_FILE_EXPECTED", PyLong_FromLong(2006));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "PATH_TO_EXECUTABLE", PyLong_FromLong(2007));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "MAKE_DIRECTORY", PyLong_FromLong(2008));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_APPLICATION_ENTITY_TITLE", PyLong_FromLong(2009));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_CFIND_HANDLER", PyLong_FromLong(2010));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_CMOVE_HANDLER", PyLong_FromLong(2011));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_CSTORE_HANDLER", PyLong_FromLong(2012));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_APPLICATION_ENTITY_FILTER", PyLong_FromLong(2013));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_SOP_CLASS_OR_INSTANCE", PyLong_FromLong(2014));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_PRESENTATION_CONTEXT", PyLong_FromLong(2015));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DICOM_FIND_UNAVAILABLE", PyLong_FromLong(2016));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DICOM_MOVE_UNAVAILABLE", PyLong_FromLong(2017));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_STORE_INSTANCE", PyLong_FromLong(2018));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_NOT_STRING", PyLong_FromLong(2019));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_OVERRIDE_TAG", PyLong_FromLong(2020));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_USE_CONTENT", PyLong_FromLong(2021));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_NO_PAYLOAD", PyLong_FromLong(2022));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_USE_DATA_URI_SCHEME", PyLong_FromLong(2023));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_BAD_PARENT", PyLong_FromLong(2024));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_PARENT_IS_INSTANCE", PyLong_FromLong(2025));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CREATE_DICOM_PARENT_ENCODING", PyLong_FromLong(2026));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNKNOWN_MODALITY", PyLong_FromLong(2027));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "BAD_JOB_ORDERING", PyLong_FromLong(2028));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "JSON_TO_LUA_TABLE", PyLong_FromLong(2029));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_CREATE_LUA", PyLong_FromLong(2030));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_EXECUTE_LUA", PyLong_FromLong(2031));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "LUA_ALREADY_EXECUTED", PyLong_FromLong(2032));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "LUA_BAD_OUTPUT", PyLong_FromLong(2033));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NOT_LUA_PREDICATE", PyLong_FromLong(2034));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "LUA_RETURNS_NO_STRING", PyLong_FromLong(2035));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "STORAGE_AREA_ALREADY_REGISTERED", PyLong_FromLong(2036));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_BACKEND_ALREADY_REGISTERED", PyLong_FromLong(2037));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "DATABASE_NOT_INITIALIZED", PyLong_FromLong(2038));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "SSL_DISABLED", PyLong_FromLong(2039));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "CANNOT_ORDER_SLICES", PyLong_FromLong(2040));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_WORKLIST_HANDLER", PyLong_FromLong(2041));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "ALREADY_EXISTING_TAG", PyLong_FromLong(2042));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_STORAGE_COMMITMENT_HANDLER", PyLong_FromLong(2043));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "NO_CGET_HANDLER", PyLong_FromLong(2044));
  PyDict_SetItemString(sdk_OrthancPluginErrorCode_Type.tp_dict, "UNSUPPORTED_MEDIA_TYPE", PyLong_FromLong(3000));

  Py_INCREF(&sdk_OrthancPluginErrorCode_Type);
  if (PyModule_AddObject(module, "ErrorCode", (PyObject *)&sdk_OrthancPluginErrorCode_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python enumeration: OrthancPluginErrorCode");
    Py_DECREF(&sdk_OrthancPluginErrorCode_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}
