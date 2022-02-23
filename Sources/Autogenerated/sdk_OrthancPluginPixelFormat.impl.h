/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2022 Osimis S.A., Belgium
 * Copyright (C) 2021-2022 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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
} sdk_OrthancPluginPixelFormat_Object;


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginPixelFormat_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.PixelFormat",    /* tp_name */
  sizeof(sdk_OrthancPluginPixelFormat_Object), /* tp_basicsize */
};


void RegisterOrthancPluginPixelFormatEnumeration(PyObject* module)
{
  sdk_OrthancPluginPixelFormat_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginPixelFormat_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginPixelFormat_Type.tp_doc = "Generated from C enumeration OrthancPluginOrthancPluginPixelFormat";  

  sdk_OrthancPluginPixelFormat_Type.tp_dict = PyDict_New();
  
  if (PyType_Ready(&sdk_OrthancPluginPixelFormat_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python enumeration: OrthancPluginPixelFormat");
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
  
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "GRAYSCALE8", PyLong_FromLong(1));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "GRAYSCALE16", PyLong_FromLong(2));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "SIGNED_GRAYSCALE16", PyLong_FromLong(3));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "RGB24", PyLong_FromLong(4));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "RGBA32", PyLong_FromLong(5));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "UNKNOWN", PyLong_FromLong(6));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "RGB48", PyLong_FromLong(7));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "GRAYSCALE32", PyLong_FromLong(8));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "FLOAT32", PyLong_FromLong(9));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "BGRA32", PyLong_FromLong(10));
  PyDict_SetItemString(sdk_OrthancPluginPixelFormat_Type.tp_dict, "GRAYSCALE64", PyLong_FromLong(11));

  Py_INCREF(&sdk_OrthancPluginPixelFormat_Type);
  if (PyModule_AddObject(module, "PixelFormat", (PyObject *)&sdk_OrthancPluginPixelFormat_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python enumeration: OrthancPluginPixelFormat");
    Py_DECREF(&sdk_OrthancPluginPixelFormat_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}
