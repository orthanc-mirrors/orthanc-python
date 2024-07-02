// Actual implementation of the methods
static PyObject *sdk_OrthancPluginFindMatcher_OrthancPluginFindMatcherIsMatch(
  sdk_OrthancPluginFindMatcher_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginFindMatcherIsMatch() on object of class OrthancPluginFindMatcher");

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

  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginFindMatcherIsMatch(OrthancPlugins::GetGlobalContext(), self->object_, arg0.buf, arg0.len);
  }
  PyBuffer_Release(&arg0);
  return PyLong_FromLong(value);
}

