// Actual implementation of the methods
static PyObject *sdk_OrthancPluginWorklistQuery_OrthancPluginWorklistIsMatch(
  sdk_OrthancPluginWorklistQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginWorklistIsMatch() on object of class OrthancPluginWorklistQuery");

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
    value = OrthancPluginWorklistIsMatch(OrthancPlugins::GetGlobalContext(), self->object_, arg0.buf, arg0.len);
  }
  PyBuffer_Release(&arg0);
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginWorklistQuery_OrthancPluginWorklistGetDicomQuery(
  sdk_OrthancPluginWorklistQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginWorklistGetDicomQuery() on object of class OrthancPluginWorklistQuery");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginWorklistGetDicomQuery(OrthancPlugins::GetGlobalContext(), *buffer, self->object_);
  }
  
  if (code == OrthancPluginErrorCode_Success)
  {
    return PyBytes_FromStringAndSize(buffer.GetData(), buffer.GetSize());
  }
  else
  {
    PythonLock::RaiseException(code);
    return NULL;  
  }
}

