// Actual implementation of the methods
static PyObject *sdk_OrthancPluginWorklistAnswers_OrthancPluginWorklistAddAnswer(
  sdk_OrthancPluginWorklistAnswers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginWorklistAddAnswer() on object of class OrthancPluginWorklistAnswers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  PyObject* arg0 = NULL;
  Py_buffer arg1;

  if (!PyArg_ParseTuple(args, "Os*", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  if (arg0 != Py_None && Py_TYPE(arg0) != GetOrthancPluginWorklistQueryType())
  {
    PyErr_SetString(PyExc_TypeError, "Invalid orthanc.OrthancPluginWorklistQuery object");
    return NULL;
  }

  OrthancPluginErrorCode code = OrthancPluginWorklistAddAnswer(OrthancPlugins::GetGlobalContext(), self->object_, arg0 == Py_None ? NULL : reinterpret_cast<sdk_OrthancPluginWorklistQuery_Object*>(arg0)->object_, arg1.buf, arg1.len);
  PyBuffer_Release(&arg1);

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

static PyObject *sdk_OrthancPluginWorklistAnswers_OrthancPluginWorklistMarkIncomplete(
  sdk_OrthancPluginWorklistAnswers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginWorklistMarkIncomplete() on object of class OrthancPluginWorklistAnswers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPluginErrorCode code = OrthancPluginWorklistMarkIncomplete(OrthancPlugins::GetGlobalContext(), self->object_);
  

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

