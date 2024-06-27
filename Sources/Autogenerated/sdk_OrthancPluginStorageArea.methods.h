// Actual implementation of the methods
static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaCreate(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaCreate() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  Py_buffer arg1;
  unsigned long long arg2 = 0;
  long int arg3 = 0;

  if (!PyArg_ParseTuple(args, "ss*Kl", &arg0, &arg1, &arg2, &arg3))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (4 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code = OrthancPluginStorageAreaCreate(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1.buf, arg2, static_cast<OrthancPluginContentType>(arg3));
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

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRead(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaRead() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  long int arg1 = 0;

  if (!PyArg_ParseTuple(args, "sl", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code = OrthancPluginStorageAreaRead(OrthancPlugins::GetGlobalContext(), *buffer, self->object_, arg0, static_cast<OrthancPluginContentType>(arg1));
  
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

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginStorageAreaRemove(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginStorageAreaRemove() on object of class OrthancPluginStorageArea");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  const char* arg0 = NULL;
  long int arg1 = 0;

  if (!PyArg_ParseTuple(args, "sl", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code = OrthancPluginStorageAreaRemove(OrthancPlugins::GetGlobalContext(), self->object_, arg0, static_cast<OrthancPluginContentType>(arg1));
  

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

static PyObject *sdk_OrthancPluginStorageArea_OrthancPluginReconstructMainDicomTags(
  sdk_OrthancPluginStorageArea_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginReconstructMainDicomTags() on object of class OrthancPluginStorageArea");

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

  OrthancPluginErrorCode code = OrthancPluginReconstructMainDicomTags(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginResourceType>(arg0));
  

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

