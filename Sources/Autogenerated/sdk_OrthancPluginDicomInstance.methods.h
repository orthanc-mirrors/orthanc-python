// Actual implementation of the methods
static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceRemoteAet(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceRemoteAet() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  const char* s = OrthancPluginGetInstanceRemoteAet(OrthancPlugins::GetGlobalContext(), self->object_);
  
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

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceSize(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceSize() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value = OrthancPluginGetInstanceSize(OrthancPlugins::GetGlobalContext(), self->object_);
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceJson(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceJson() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginGetInstanceJson(OrthancPlugins::GetGlobalContext(), self->object_));
  
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

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceSimplifiedJson(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceSimplifiedJson() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginGetInstanceSimplifiedJson(OrthancPlugins::GetGlobalContext(), self->object_));
  
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

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginHasInstanceMetadata(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginHasInstanceMetadata() on object of class OrthancPluginDicomInstance");

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

  long value = OrthancPluginHasInstanceMetadata(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceMetadata(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceMetadata() on object of class OrthancPluginDicomInstance");

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

  const char* s = OrthancPluginGetInstanceMetadata(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  
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

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceOrigin(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceOrigin() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPluginInstanceOrigin value = OrthancPluginGetInstanceOrigin(OrthancPlugins::GetGlobalContext(), self->object_);
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceTransferSyntaxUid(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceTransferSyntaxUid() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginGetInstanceTransferSyntaxUid(OrthancPlugins::GetGlobalContext(), self->object_));
  
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

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginHasInstancePixelData(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginHasInstancePixelData() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value = OrthancPluginHasInstancePixelData(OrthancPlugins::GetGlobalContext(), self->object_);
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceFramesCount(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceFramesCount() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  long value = OrthancPluginGetInstanceFramesCount(OrthancPlugins::GetGlobalContext(), self->object_);
  
  return PyLong_FromLong(value);
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceRawFrame(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceRawFrame() on object of class OrthancPluginDicomInstance");

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

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code = OrthancPluginGetInstanceRawFrame(OrthancPlugins::GetGlobalContext(), *buffer, self->object_, arg0);
  
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

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceDecodedFrame(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceDecodedFrame() on object of class OrthancPluginDicomInstance");

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

  // This is the case of a constructor
  OrthancPluginImage* obj = OrthancPluginGetInstanceDecodedFrame(OrthancPlugins::GetGlobalContext(), self->object_, arg0);
  
  if (obj == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;  
  }
  else
  {
    PyObject *argList = Py_BuildValue("Lb", obj, false /* not borrowed */);
    PyObject *python = PyObject_CallObject((PyObject *) &sdk_OrthancPluginImage_Type, argList);
    Py_DECREF(argList);
    return python;
  }
}

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginSerializeDicomInstance(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginSerializeDicomInstance() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }



  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code = OrthancPluginSerializeDicomInstance(OrthancPlugins::GetGlobalContext(), *buffer, self->object_);
  
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

static PyObject *sdk_OrthancPluginDicomInstance_OrthancPluginGetInstanceAdvancedJson(
  sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  PythonLock::LogCall("Calling method OrthancPluginGetInstanceAdvancedJson() on object of class OrthancPluginDicomInstance");

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }

  long int arg0 = 0;
  long int arg1 = 0;
  unsigned long arg2 = 0;

  if (!PyArg_ParseTuple(args, "llk", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  s.Assign(OrthancPluginGetInstanceAdvancedJson(OrthancPlugins::GetGlobalContext(), self->object_, static_cast<OrthancPluginDicomToJsonFormat>(arg0), static_cast<OrthancPluginDicomToJsonFlags>(arg1), arg2));
  
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

