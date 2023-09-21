// Actual implementation of the methods
static PyObject *sdk_OrthancPluginJob_OrthancPluginSubmitJob(
  sdk_OrthancPluginJob_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSubmitJob() on object of class OrthancPluginJob");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;

  if (!PyArg_ParseTuple(args, "l", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }
  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginSubmitJob(OrthancPlugins::GetGlobalContext(), self->object_, arg0));
  
  if (s.GetContent() == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;
  }
  else
  {
    return PyUnicode_FromString(s.GetContent());
  }
}

