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
  OrthancPluginJob* object_;
  bool borrowed_;
} sdk_OrthancPluginJob_Object;



// Forward declaration of the methods
static PyObject *sdk_OrthancPluginJob_OrthancPluginSubmitJob(
  sdk_OrthancPluginJob_Object* self, PyObject *args);


static PyMethodDef sdk_OrthancPluginJob_Methods[] = {
  { "SubmitJob",
    (PyCFunction) sdk_OrthancPluginJob_OrthancPluginSubmitJob, METH_VARARGS,
    "Generated from C function OrthancPluginSubmitJob()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginJob_Constructor(
  sdk_OrthancPluginJob_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginJob");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginJob*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginJob_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.Job",    /* tp_name */
  sizeof(sdk_OrthancPluginJob_Object), /* tp_basicsize */
};


static void sdk_OrthancPluginJob_Destructor(PyObject *self)
{
  PythonLock::LogCall("Destroying Python object of class OrthancPluginJob");

  sdk_OrthancPluginJob_Object& tmp = *((sdk_OrthancPluginJob_Object*) self);
  
  if (tmp.object_ != NULL &&
      !tmp.borrowed_)
  {
    OrthancPluginFreeJob(OrthancPlugins::GetGlobalContext(), tmp.object_);
    tmp.object_ = NULL;
  }
  
  Py_TYPE(self)->tp_free((PyObject *)self);
}


// Actual implementation of the methods
static PyObject *sdk_OrthancPluginJob_OrthancPluginSubmitJob(
  sdk_OrthancPluginJob_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSubmitJob() on object of class OrthancPluginJob");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  int arg0 = 0;

  if (!PyArg_ParseTuple(args, "i", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginSubmitJob(OrthancPlugins::GetGlobalContext(), self->object_, arg0));
  
  if (s.GetContent() == NULL)
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_InternalError);
    PyErr_SetString(PyExc_ValueError, "Internal error");
    return NULL;
  }
  else
  {
    return PyUnicode_FromString(s.GetContent());
  }
}



static void RegisterOrthancPluginJobClass(PyObject* module)
{
  sdk_OrthancPluginJob_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginJob_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginJob_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginJob";
  sdk_OrthancPluginJob_Type.tp_methods = sdk_OrthancPluginJob_Methods;
  sdk_OrthancPluginJob_Type.tp_init = (initproc) sdk_OrthancPluginJob_Constructor;

  /**
   * "tp_dealloc is called when the reference count of the object goes
   * down to zero. This is where you destroy the object and its
   * members. It should then free the memory occupied by the object by
   * calling tp_free."
   * https://stackoverflow.com/a/24863227/881731
   **/
  sdk_OrthancPluginJob_Type.tp_dealloc = sdk_OrthancPluginJob_Destructor;
  
  if (PyType_Ready(&sdk_OrthancPluginJob_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginJob");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginJob_Type);
  if (PyModule_AddObject(module, "Job", (PyObject *)&sdk_OrthancPluginJob_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginJob");
    Py_DECREF(&sdk_OrthancPluginJob_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyObject* GetOrthancPluginJobType()
{
  return (PyObject*) &sdk_OrthancPluginJob_Type;
}
