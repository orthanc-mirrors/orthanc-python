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
  OrthancPluginRestOutput* object_;
  bool borrowed_;
} sdk_OrthancPluginRestOutput_Object;



// Forward declaration of the methods
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginAnswerBuffer(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerPngImage(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginRedirect(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatusCode(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendUnauthorized(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendMethodNotAllowed(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetCookie(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetHttpHeader(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginStartMultipartAnswer(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendMultipartItem(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatus(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerJpegImage(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetHttpErrorDetails(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args);


static PyMethodDef sdk_OrthancPluginRestOutput_Methods[] = {
  { "AnswerBuffer",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginAnswerBuffer, METH_VARARGS,
    "Generated from C function OrthancPluginAnswerBuffer()" },
  { "CompressAndAnswerPngImage",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerPngImage, METH_VARARGS,
    "Generated from C function OrthancPluginCompressAndAnswerPngImage()" },
  { "Redirect",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginRedirect, METH_VARARGS,
    "Generated from C function OrthancPluginRedirect()" },
  { "SendHttpStatusCode",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatusCode, METH_VARARGS,
    "Generated from C function OrthancPluginSendHttpStatusCode()" },
  { "SendUnauthorized",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginSendUnauthorized, METH_VARARGS,
    "Generated from C function OrthancPluginSendUnauthorized()" },
  { "SendMethodNotAllowed",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginSendMethodNotAllowed, METH_VARARGS,
    "Generated from C function OrthancPluginSendMethodNotAllowed()" },
  { "SetCookie",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginSetCookie, METH_VARARGS,
    "Generated from C function OrthancPluginSetCookie()" },
  { "SetHttpHeader",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginSetHttpHeader, METH_VARARGS,
    "Generated from C function OrthancPluginSetHttpHeader()" },
  { "StartMultipartAnswer",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginStartMultipartAnswer, METH_VARARGS,
    "Generated from C function OrthancPluginStartMultipartAnswer()" },
  { "SendMultipartItem",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginSendMultipartItem, METH_VARARGS,
    "Generated from C function OrthancPluginSendMultipartItem()" },
  { "SendHttpStatus",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatus, METH_VARARGS,
    "Generated from C function OrthancPluginSendHttpStatus()" },
  { "CompressAndAnswerJpegImage",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerJpegImage, METH_VARARGS,
    "Generated from C function OrthancPluginCompressAndAnswerJpegImage()" },
  { "SetHttpErrorDetails",
    (PyCFunction) sdk_OrthancPluginRestOutput_OrthancPluginSetHttpErrorDetails, METH_VARARGS,
    "Generated from C function OrthancPluginSetHttpErrorDetails()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginRestOutput_Constructor(
  sdk_OrthancPluginRestOutput_Object *self, PyObject *args, PyObject *kwds)
{
  OrthancPlugins::LogInfo("Creating Python object of class OrthancPluginRestOutput");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginRestOutput*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginRestOutput_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.RestOutput",    /* tp_name */
  sizeof(sdk_OrthancPluginRestOutput_Object), /* tp_basicsize */
};




// Actual implementation of the methods
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginAnswerBuffer(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginAnswerBuffer() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  Py_buffer arg0;
  const char* arg2 = NULL;

  if (!PyArg_ParseTuple(args, "s*s", &arg0, &arg2))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginAnswerBuffer(OrthancPlugins::GetGlobalContext(), self->object_, arg0.buf, arg0.len, arg2);
  PyBuffer_Release(&arg0);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerPngImage(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginCompressAndAnswerPngImage() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;
  unsigned long arg1 = 0;
  unsigned long arg2 = 0;
  unsigned long arg3 = 0;
  Py_buffer arg4;

  if (!PyArg_ParseTuple(args, "lkkks*", &arg0, &arg1, &arg2, &arg3, &arg4))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (5 arguments expected)");
    return NULL;
  }
  OrthancPluginCompressAndAnswerPngImage(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginPixelFormat>(arg0), arg1, arg2, arg3, arg4.buf);
  PyBuffer_Release(&arg4);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginRedirect(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginRedirect() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPluginRedirect(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatusCode(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginSendHttpStatusCode() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned short arg0 = 0;

  if (!PyArg_ParseTuple(args, "H", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPluginSendHttpStatusCode(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendUnauthorized(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginSendUnauthorized() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPluginSendUnauthorized(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendMethodNotAllowed(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginSendMethodNotAllowed() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPluginSendMethodNotAllowed(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetCookie(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginSetCookie() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginSetCookie(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetHttpHeader(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginSetHttpHeader() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginSetHttpHeader(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginStartMultipartAnswer(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginStartMultipartAnswer() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginErrorCode code = OrthancPluginStartMultipartAnswer(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  

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

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendMultipartItem(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginSendMultipartItem() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  unsigned long arg1 = 0;

  if (!PyArg_ParseTuple(args, "sk", &arg0, &arg1))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginErrorCode code = OrthancPluginSendMultipartItem(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  

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

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatus(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginSendHttpStatus() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned short arg0 = 0;
  const char* arg1 = NULL;
  unsigned long arg2 = 0;

  if (!PyArg_ParseTuple(args, "Hsk", &arg0, &arg1, &arg2))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }
  OrthancPluginSendHttpStatus(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1, arg2);
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerJpegImage(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginCompressAndAnswerJpegImage() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;
  unsigned long arg1 = 0;
  unsigned long arg2 = 0;
  unsigned long arg3 = 0;
  Py_buffer arg4;
  unsigned char arg5 = 0;

  if (!PyArg_ParseTuple(args, "lkkks*b", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (6 arguments expected)");
    return NULL;
  }
  OrthancPluginCompressAndAnswerJpegImage(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginPixelFormat>(arg0), arg1, arg2, arg3, arg4.buf, arg5);
  PyBuffer_Release(&arg4);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSetHttpErrorDetails(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  OrthancPlugins::LogInfo("Calling method OrthancPluginSetHttpErrorDetails() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    // TODO: RAISE
    //PythonLock::RaiseException(module, OrthancPluginErrorCode_NullPointer);
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  unsigned char arg1 = 0;

  if (!PyArg_ParseTuple(args, "sb", &arg0, &arg1))
  {
    // TODO => RAISE : https://stackoverflow.com/questions/60832317
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginSetHttpErrorDetails(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  

  Py_INCREF(Py_None);
  return Py_None;
}



static void RegisterOrthancPluginRestOutputClass(PyObject* module)
{
  sdk_OrthancPluginRestOutput_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginRestOutput_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginRestOutput_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginRestOutput";
  sdk_OrthancPluginRestOutput_Type.tp_methods = sdk_OrthancPluginRestOutput_Methods;
  sdk_OrthancPluginRestOutput_Type.tp_init = (initproc) sdk_OrthancPluginRestOutput_Constructor;

  
  if (PyType_Ready(&sdk_OrthancPluginRestOutput_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginRestOutput");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginRestOutput_Type);
  if (PyModule_AddObject(module, "RestOutput", (PyObject *)&sdk_OrthancPluginRestOutput_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginRestOutput");
    Py_DECREF(&sdk_OrthancPluginRestOutput_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyObject* GetOrthancPluginRestOutputType()
{
  return (PyObject*) &sdk_OrthancPluginRestOutput_Type;
}
