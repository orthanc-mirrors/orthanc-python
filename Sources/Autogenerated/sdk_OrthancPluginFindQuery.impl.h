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
  OrthancPluginFindQuery* object_;
  bool borrowed_;
} sdk_OrthancPluginFindQuery_Object;



// Forward declaration of the methods
static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQuerySize(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryTagName(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryValue(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args);


static PyMethodDef sdk_OrthancPluginFindQuery_Methods[] = {
  { "GetFindQuerySize",
    (PyCFunction) sdk_OrthancPluginFindQuery_OrthancPluginGetFindQuerySize, METH_VARARGS,
    "Generated from C function OrthancPluginGetFindQuerySize()" },
  { "GetFindQueryTagName",
    (PyCFunction) sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryTagName, METH_VARARGS,
    "Generated from C function OrthancPluginGetFindQueryTagName()" },
  { "GetFindQueryValue",
    (PyCFunction) sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryValue, METH_VARARGS,
    "Generated from C function OrthancPluginGetFindQueryValue()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginFindQuery_Constructor(
  sdk_OrthancPluginFindQuery_Object *self, PyObject *args, PyObject *kwds)
{
  OrthancPlugins::LogInfo("Creating Python object of class OrthancPluginFindQuery");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginFindQuery*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginFindQuery_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.FindQuery",    /* tp_name */
  sizeof(sdk_OrthancPluginFindQuery_Object), /* tp_basicsize */
};




// Actual implementation of the methods
static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQuerySize(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginGetFindQuerySize() on object of class OrthancPluginFindQuery");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }


  long value = OrthancPluginGetFindQuerySize(OrthancPlugins::GetGlobalContext(), self->object_);
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryTagName(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginGetFindQueryTagName() on object of class OrthancPluginFindQuery");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginGetFindQueryTagName(OrthancPlugins::GetGlobalContext(), self->object_, arg0));
  
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

static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryValue(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginGetFindQueryValue() on object of class OrthancPluginFindQuery");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginGetFindQueryValue(OrthancPlugins::GetGlobalContext(), self->object_, arg0));
  
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



static void RegisterOrthancPluginFindQueryClass(PyObject* module)
{
  sdk_OrthancPluginFindQuery_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginFindQuery_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginFindQuery_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginFindQuery";
  sdk_OrthancPluginFindQuery_Type.tp_methods = sdk_OrthancPluginFindQuery_Methods;
  sdk_OrthancPluginFindQuery_Type.tp_init = (initproc) sdk_OrthancPluginFindQuery_Constructor;

  
  if (PyType_Ready(&sdk_OrthancPluginFindQuery_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginFindQuery");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginFindQuery_Type);
  if (PyModule_AddObject(module, "FindQuery", (PyObject *)&sdk_OrthancPluginFindQuery_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginFindQuery");
    Py_DECREF(&sdk_OrthancPluginFindQuery_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyObject* GetOrthancPluginFindQueryType()
{
  return (PyObject*) &sdk_OrthancPluginFindQuery_Type;
}
