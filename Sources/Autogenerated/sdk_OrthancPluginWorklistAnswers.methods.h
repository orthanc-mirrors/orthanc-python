// Actual implementation of the methods
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

