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
  OrthancPluginStorageArea* object_;
  bool borrowed_;
} sdk_OrthancPluginStorageArea_Object;



// Forward declaration of the methods
static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaCreate(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRead(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRemove(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginReconstructMainDicomTags(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args);


static PyMethodDef sdk_OrthancPluginStorageArea_Methods[] = {
  { "StorageAreaCreate",
    (PyCFunction) sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaCreate, METH_VARARGS,
    "Generated from C function OrthancPluginStorageAreaCreate()" },
  { "StorageAreaRead",
    (PyCFunction) sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRead, METH_VARARGS,
    "Generated from C function OrthancPluginStorageAreaRead()" },
  { "StorageAreaRemove",
    (PyCFunction) sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRemove, METH_VARARGS,
    "Generated from C function OrthancPluginStorageAreaRemove()" },
  { "ReconstructMainDicomTags",
    (PyCFunction) sdk_OrthancPluginStorageArea_OrthancPluginReconstructMainDicomTags, METH_VARARGS,
    "Generated from C function OrthancPluginReconstructMainDicomTags()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginStorageArea_Constructor(
  sdk_OrthancPluginStorageArea_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginStorageArea");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginStorageArea*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginStorageArea_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.StorageArea",    /* tp_name */
  sizeof(sdk_OrthancPluginStorageArea_Object), /* tp_basicsize */
};




// Actual implementation of the methods
static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaCreate(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaCreate() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  Py_buffer arg1;
  unsigned long long arg2 = 0;
  long int arg3 = 0;

  if (!PyArg_ParseTuple(args, "ss*Kl", &arg0, &arg1, &arg2, &arg3))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (4 arguments expected)");
    return NULL;
  }
  OrthancPluginErrorCode code = OrthancPluginStorageAreaCreate(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1.buf, arg2, static_cast<OrthancPluginContentType>(arg3));
  PyBuffer_Release(&arg1);

  if (code == OrthancPluginErrorCode_Success)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    //PythonLock::RaiseException(module, code);
    PyErr_SetString(PyExc_ValueError, "Internal error");
    return NULL;
  }
}

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRead(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaRead() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  long int arg1 = 0;

  if (!PyArg_ParseTuple(args, "sl", &arg0, &arg1))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code = OrthancPluginStorageAreaRead(OrthancPlugins::GetGlobalContext(), *buffer, self->object_, arg0, static_cast<OrthancPluginContentType>(arg1));
  
  if (code == OrthancPluginErrorCode_Success)
  {
    return PyBytes_FromStringAndSize(buffer.GetData(), buffer.GetSize());
  }
  else
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_InternalError);
    PyErr_SetString(PyExc_ValueError, "Internal error");
    return NULL;  
  }
}

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRemove(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaRemove() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  long int arg1 = 0;

  if (!PyArg_ParseTuple(args, "sl", &arg0, &arg1))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginErrorCode code = OrthancPluginStorageAreaRemove(OrthancPlugins::GetGlobalContext(), self->object_, arg0, static_cast<OrthancPluginContentType>(arg1));
  

  if (code == OrthancPluginErrorCode_Success)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    //PythonLock::RaiseException(module, code);
    PyErr_SetString(PyExc_ValueError, "Internal error");
    return NULL;
  }
}

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginReconstructMainDicomTags(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginReconstructMainDicomTags() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;

  if (!PyArg_ParseTuple(args, "l", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPluginErrorCode code = OrthancPluginReconstructMainDicomTags(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginResourceType>(arg0));
  

  if (code == OrthancPluginErrorCode_Success)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    //PythonLock::RaiseException(module, code);
    PyErr_SetString(PyExc_ValueError, "Internal error");
    return NULL;
  }
}



static void RegisterOrthancPluginStorageAreaClass(PyObject* module)
{
  sdk_OrthancPluginStorageArea_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginStorageArea_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginStorageArea_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginStorageArea";
  sdk_OrthancPluginStorageArea_Type.tp_methods = sdk_OrthancPluginStorageArea_Methods;
  sdk_OrthancPluginStorageArea_Type.tp_init = (initproc) sdk_OrthancPluginStorageArea_Constructor;

  
  if (PyType_Ready(&sdk_OrthancPluginStorageArea_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginStorageArea");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginStorageArea_Type);
  if (PyModule_AddObject(module, "StorageArea", (PyObject *)&sdk_OrthancPluginStorageArea_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginStorageArea");
    Py_DECREF(&sdk_OrthancPluginStorageArea_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyObject* GetOrthancPluginStorageAreaType()
{
  return (PyObject*) &sdk_OrthancPluginStorageArea_Type;
}
