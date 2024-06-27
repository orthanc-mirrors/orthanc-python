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
} sdk_OrthancPluginImageFormat_Object;


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginImageFormat_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.ImageFormat",    /* tp_name */
  sizeof(sdk_OrthancPluginImageFormat_Object), /* tp_basicsize */
};


void RegisterOrthancPluginImageFormatEnumeration(PyObject* module)
{
  sdk_OrthancPluginImageFormat_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginImageFormat_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginImageFormat_Type.tp_doc = "Generated from C enumeration OrthancPluginOrthancPluginImageFormat";  

  sdk_OrthancPluginImageFormat_Type.tp_dict = PyDict_New();
  
  if (PyType_Ready(&sdk_OrthancPluginImageFormat_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python enumeration: OrthancPluginImageFormat");
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
    PyObject* tmp = PyLong_FromLong(0);
    PyDict_SetItemString(sdk_OrthancPluginImageFormat_Type.tp_dict, "PNG", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(1);
    PyDict_SetItemString(sdk_OrthancPluginImageFormat_Type.tp_dict, "JPEG", tmp);
    Py_DECREF(tmp);
  }

  {
    PyObject* tmp = PyLong_FromLong(2);
    PyDict_SetItemString(sdk_OrthancPluginImageFormat_Type.tp_dict, "DICOM", tmp);
    Py_DECREF(tmp);
  }


  Py_INCREF(&sdk_OrthancPluginImageFormat_Type);
  if (PyModule_AddObject(module, "ImageFormat", (PyObject *)&sdk_OrthancPluginImageFormat_Type) < 0)
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot register Python enumeration: OrthancPluginImageFormat");
    Py_DECREF(&sdk_OrthancPluginImageFormat_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}
