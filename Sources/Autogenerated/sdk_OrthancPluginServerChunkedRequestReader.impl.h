/**
 * Python plugin for Orthanc
 * Copyright (C) 2017-2020 Osimis S.A., Belgium
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

  /* Type-specific fields go here. */
  OrthancPluginServerChunkedRequestReader* object_;
  bool borrowed_;
} sdk_OrthancPluginServerChunkedRequestReader_Object;



// Forward declaration of the methods


static PyMethodDef sdk_OrthancPluginServerChunkedRequestReader_Methods[] = {
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginServerChunkedRequestReader_Constructor(
  sdk_OrthancPluginServerChunkedRequestReader_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginServerChunkedRequestReader");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginServerChunkedRequestReader*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginServerChunkedRequestReader_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.ServerChunkedRequestReader",    /* tp_name */
  sizeof(sdk_OrthancPluginServerChunkedRequestReader_Object), /* tp_basicsize */
};




// Actual implementation of the methods


static void RegisterOrthancPluginServerChunkedRequestReaderClass(PyObject* module)
{
  sdk_OrthancPluginServerChunkedRequestReader_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginServerChunkedRequestReader_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginServerChunkedRequestReader_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginServerChunkedRequestReader";
  sdk_OrthancPluginServerChunkedRequestReader_Type.tp_methods = sdk_OrthancPluginServerChunkedRequestReader_Methods;
  sdk_OrthancPluginServerChunkedRequestReader_Type.tp_init = (initproc) sdk_OrthancPluginServerChunkedRequestReader_Constructor;

  
  if (PyType_Ready(&sdk_OrthancPluginServerChunkedRequestReader_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginServerChunkedRequestReader");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginServerChunkedRequestReader_Type);
  if (PyModule_AddObject(module, "ServerChunkedRequestReader", (PyObject *)&sdk_OrthancPluginServerChunkedRequestReader_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginServerChunkedRequestReader");
    Py_DECREF(&sdk_OrthancPluginServerChunkedRequestReader_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyObject* GetOrthancPluginServerChunkedRequestReaderType()
{
  return (PyObject*) &sdk_OrthancPluginServerChunkedRequestReader_Type;
}
