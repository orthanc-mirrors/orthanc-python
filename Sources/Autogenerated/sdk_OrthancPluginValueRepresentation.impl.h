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


typedef struct 
{
  PyObject_HEAD
} sdk_OrthancPluginValueRepresentation_Object;


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginValueRepresentation_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.ValueRepresentation",    /* tp_name */
  sizeof(sdk_OrthancPluginValueRepresentation_Object), /* tp_basicsize */
};


void RegisterOrthancPluginValueRepresentationEnumeration(PyObject* module)
{
  sdk_OrthancPluginValueRepresentation_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginValueRepresentation_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginValueRepresentation_Type.tp_doc = "Generated from C enumeration OrthancPluginOrthancPluginValueRepresentation";  

  sdk_OrthancPluginValueRepresentation_Type.tp_dict = PyDict_New();
  
  if (PyType_Ready(&sdk_OrthancPluginValueRepresentation_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python enumeration: OrthancPluginValueRepresentation");
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
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "AE", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "AS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(3);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "AT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(4);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "CS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(5);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "DA", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(6);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "DS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(7);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "DT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(8);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "FD", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(9);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "FL", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(10);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "IS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(11);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "LO", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(12);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "LT", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(13);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "OB", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(14);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "OF", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(15);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "OW", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(16);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "PN", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(17);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "SH", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(18);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "SL", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(19);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "SQ", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(20);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "SS", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(21);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "ST", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(22);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "TM", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(23);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "UI", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(24);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "UL", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(25);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "UN", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(26);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "US", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(27);
    PyDict_SetItemString(sdk_OrthancPluginValueRepresentation_Type.tp_dict, "UT", tmp);
    Py_DECREF(tmp);
  }


  Py_INCREF(&sdk_OrthancPluginValueRepresentation_Type);
  if (PyModule_AddObject(module, "ValueRepresentation", (PyObject *)&sdk_OrthancPluginValueRepresentation_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python enumeration: OrthancPluginValueRepresentation");
    Py_DECREF(&sdk_OrthancPluginValueRepresentation_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}
