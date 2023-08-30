// Actual implementation of the methods
static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeersCount(
  sdk_OrthancPluginPeers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetPeersCount() on object of class OrthancPluginPeers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }


  long value = OrthancPluginGetPeersCount(OrthancPlugins::GetGlobalContext(), self->object_);
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerName(
  sdk_OrthancPluginPeers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetPeerName() on object of class OrthancPluginPeers");

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
  const char* s = OrthancPluginGetPeerName(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  
  if (s == NULL)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    return PyUnicode_FromString(s);
  }
}

static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerUrl(
  sdk_OrthancPluginPeers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetPeerUrl() on object of class OrthancPluginPeers");

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
  const char* s = OrthancPluginGetPeerUrl(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  
  if (s == NULL)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    return PyUnicode_FromString(s);
  }
}

static PyObject *sdk_OrthancPluginPeers_OrthancPluginGetPeerUserProperty(
  sdk_OrthancPluginPeers_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetPeerUserProperty() on object of class OrthancPluginPeers");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  unsigned long arg0 = 0;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ks", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }
  const char* s = OrthancPluginGetPeerUserProperty(OrthancPlugins::GetGlobalContext(), self->object_, arg0, arg1);
  
  if (s == NULL)
  {
    Py_INCREF(Py_None);
    return Py_None;
  }
  else
  {
    return PyUnicode_FromString(s);
  }
}

