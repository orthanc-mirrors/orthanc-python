/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2024 Osimis S.A., Belgium
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


// Forward declaration of the autogenerated methods
static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeersCount(
  sdk_OrthancPluginPeers_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerName(
  sdk_OrthancPluginPeers_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerUrl(
  sdk_OrthancPluginPeers_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerUserProperty(
  sdk_OrthancPluginPeers_Object* self, PyObject *args);
// End of forward declarations


// Forward declaration of the custom methods
// End of forward declarations


static PyMethodDef sdk_OrthancPluginPeers_Methods[] = {
  { "GetPeersCount",
    (PyCFunction) sdk_OrthancPluginPeers_OrthancPluginGetPeersCount, METH_VARARGS,
    "Generated from C function OrthancPluginGetPeersCount()" },
  { "GetPeerName",
    (PyCFunction) sdk_OrthancPluginPeers_OrthancPluginGetPeerName, METH_VARARGS,
    "Generated from C function OrthancPluginGetPeerName()" },
  { "GetPeerUrl",
    (PyCFunction) sdk_OrthancPluginPeers_OrthancPluginGetPeerUrl, METH_VARARGS,
    "Generated from C function OrthancPluginGetPeerUrl()" },
  { "GetPeerUserProperty",
    (PyCFunction) sdk_OrthancPluginPeers_OrthancPluginGetPeerUserProperty, METH_VARARGS,
    "Generated from C function OrthancPluginGetPeerUserProperty()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginPeers_Constructor(
  sdk_OrthancPluginPeers_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginPeers");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginPeers*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginPeers_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.Peers",    /* tp_name */
  sizeof(sdk_OrthancPluginPeers_Object), /* tp_basicsize */
};


static void sdk_OrthancPluginPeers_Destructor(PyObject *self)
{
  PythonLock::LogCall("Destroying Python object of class OrthancPluginPeers");

  sdk_OrthancPluginPeers_Object& tmp = *((sdk_OrthancPluginPeers_Object*) self);
  
  if (tmp.object_ != NULL &&
      !tmp.borrowed_)
  {
    OrthancPluginFreePeers(OrthancPlugins::GetGlobalContext(), tmp.object_);
    tmp.object_ = NULL;
  }
  
  Py_TYPE(self)->tp_free((PyObject *)self);
}


static void RegisterOrthancPluginPeersClass(PyObject* module)
{
  sdk_OrthancPluginPeers_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginPeers_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginPeers_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginPeers";
  sdk_OrthancPluginPeers_Type.tp_methods = sdk_OrthancPluginPeers_Methods;
  sdk_OrthancPluginPeers_Type.tp_init = (initproc) sdk_OrthancPluginPeers_Constructor;

  /**
   * "tp_dealloc is called when the reference count of the object goes
   * down to zero. This is where you destroy the object and its
   * members. It should then free the memory occupied by the object by
   * calling tp_free."
   * https://stackoverflow.com/a/24863227/881731
   **/
  sdk_OrthancPluginPeers_Type.tp_dealloc = sdk_OrthancPluginPeers_Destructor;
  
  if (PyType_Ready(&sdk_OrthancPluginPeers_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginPeers");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginPeers_Type);
  if (PyModule_AddObject(module, "Peers", (PyObject *)&sdk_OrthancPluginPeers_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginPeers");
    Py_DECREF(&sdk_OrthancPluginPeers_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyTypeObject* GetOrthancPluginPeersType()
{
  return &sdk_OrthancPluginPeers_Type;
}
