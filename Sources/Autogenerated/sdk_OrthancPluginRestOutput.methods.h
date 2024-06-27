// Actual implementation of the methods
static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginAnswerBuffer(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginAnswerBuffer() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  Py_buffer arg0;
  const char* arg2 = NULL;

  if (!PyArg_ParseTuple(args, "s*s", &arg0, &arg2))
  {
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
  PythonLock::LogCall("Calling method OrthancPluginCompressAndAnswerPngImage() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
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
  PythonLock::LogCall("Calling method OrthancPluginRedirect() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
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
  PythonLock::LogCall("Calling method OrthancPluginSendHttpStatusCode() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned short arg0 = 0;

  if (!PyArg_ParseTuple(args, "H", &arg0))
  {
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
  PythonLock::LogCall("Calling method OrthancPluginSendUnauthorized() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
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
  PythonLock::LogCall("Calling method OrthancPluginSendMethodNotAllowed() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
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
  PythonLock::LogCall("Calling method OrthancPluginSetCookie() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
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
  PythonLock::LogCall("Calling method OrthancPluginSetHttpHeader() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
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
  PythonLock::LogCall("Calling method OrthancPluginStartMultipartAnswer() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
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
    PythonLock::RaiseException(code);
    return NULL;
  }
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendMultipartItem(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSendMultipartItem() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "s*", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPluginErrorCode code = OrthancPluginSendMultipartItem(OrthancPlugins::GetGlobalContext(), self->object_, arg0.buf, arg0.len);
  PyBuffer_Release(&arg0);

  if (code == OrthancPluginErrorCode_Success)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    PythonLock::RaiseException(code);
    return NULL;
  }
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginSendHttpStatus(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSendHttpStatus() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned short arg0 = 0;
  Py_buffer arg1;

  if (!PyArg_ParseTuple(args, "Hs*", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginSendHttpStatus(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1.buf, arg1.len);
  PyBuffer_Release(&arg1);

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject *sdk_OrthancPluginRestOutput_OrthancPluginCompressAndAnswerJpegImage(
  sdk_OrthancPluginRestOutput_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginCompressAndAnswerJpegImage() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
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
  PythonLock::LogCall("Calling method OrthancPluginSetHttpErrorDetails() on object of class OrthancPluginRestOutput");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  unsigned char arg1 = 0;

  if (!PyArg_ParseTuple(args, "sb", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  OrthancPluginSetHttpErrorDetails(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  

  Py_INCREF(Py_None);
  return Py_None;
}

