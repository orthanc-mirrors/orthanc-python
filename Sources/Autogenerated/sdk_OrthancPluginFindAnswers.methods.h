// Actual implementation of the methods
static PyObject *sdk_OrthancPluginFindAnswers_OrthancPluginFindAddAnswer(
  sdk_OrthancPluginFindAnswers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginFindAddAnswer() on object of class OrthancPluginFindAnswers");

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

  OrthancPluginErrorCode code = OrthancPluginFindAddAnswer(OrthancPlugins::GetGlobalContext(), self->object_, arg0.buf, arg0.len);
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

static PyObject *sdk_OrthancPluginFindAnswers_OrthancPluginFindMarkIncomplete(
  sdk_OrthancPluginFindAnswers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginFindMarkIncomplete() on object of class OrthancPluginFindAnswers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPluginErrorCode code = OrthancPluginFindMarkIncomplete(OrthancPlugins::GetGlobalContext(), self->object_);
  

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

