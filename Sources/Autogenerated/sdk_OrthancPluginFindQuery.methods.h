// Actual implementation of the methods
static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQuerySize(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetFindQuerySize() on object of class OrthancPluginFindQuery");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value = OrthancPluginGetFindQuerySize(OrthancPlugins::GetGlobalContext(), self->object_);
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryTagName(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetFindQueryTagName() on object of class OrthancPluginFindQuery");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginGetFindQueryTagName(OrthancPlugins::GetGlobalContext(), self->object_, arg0));
  
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

static PyObject *sdk_OrthancPluginFindQuery_OrthancPluginGetFindQueryValue(
  sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetFindQueryValue() on object of class OrthancPluginFindQuery");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginGetFindQueryValue(OrthancPlugins::GetGlobalContext(), self->object_, arg0));
  
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

