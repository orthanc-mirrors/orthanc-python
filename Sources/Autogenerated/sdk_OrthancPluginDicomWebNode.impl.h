/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2021 Osimis S.A., Belgium
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
  OrthancPluginDicomWebNode* object_;
  bool borrowed_;
} sdk_OrthancPluginDicomWebNode_Object;



// Forward declaration of the methods


static PyMethodDef sdk_OrthancPluginDicomWebNode_Methods[] = {
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginDicomWebNode_Constructor(
  sdk_OrthancPluginDicomWebNode_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginDicomWebNode");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginDicomWebNode*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginDicomWebNode_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.DicomWebNode",    /* tp_name */
  sizeof(sdk_OrthancPluginDicomWebNode_Object), /* tp_basicsize */
};




// Actual implementation of the methods


static void RegisterOrthancPluginDicomWebNodeClass(PyObject* module)
{
  sdk_OrthancPluginDicomWebNode_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginDicomWebNode_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginDicomWebNode_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginDicomWebNode";
  sdk_OrthancPluginDicomWebNode_Type.tp_methods = sdk_OrthancPluginDicomWebNode_Methods;
  sdk_OrthancPluginDicomWebNode_Type.tp_init = (initproc) sdk_OrthancPluginDicomWebNode_Constructor;

  
  if (PyType_Ready(&sdk_OrthancPluginDicomWebNode_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginDicomWebNode");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginDicomWebNode_Type);
  if (PyModule_AddObject(module, "DicomWebNode", (PyObject *)&sdk_OrthancPluginDicomWebNode_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginDicomWebNode");
    Py_DECREF(&sdk_OrthancPluginDicomWebNode_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyObject* GetOrthancPluginDicomWebNodeType()
{
  return (PyObject*) &sdk_OrthancPluginDicomWebNode_Type;
}
