/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2022 Osimis S.A., Belgium
 * Copyright (C) 2021-2022 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/


// Forward declaration of the autogenerated methods
static PyObject *sdk_OrthancPluginImage_OrthancPluginGetImagePixelFormat(
  sdk_OrthancPluginImage_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginImage_OrthancPluginGetImageWidth(
  sdk_OrthancPluginImage_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginImage_OrthancPluginGetImageHeight(
  sdk_OrthancPluginImage_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginImage_OrthancPluginGetImagePitch(
  sdk_OrthancPluginImage_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginImage_OrthancPluginConvertPixelFormat(
  sdk_OrthancPluginImage_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginImage_OrthancPluginDrawText(
  sdk_OrthancPluginImage_Object* self, PyObject *args);
// End of forward declarations


// Forward declaration of the custom methods
extern PyObject *GetImageBuffer(
  sdk_OrthancPluginImage_Object* self, PyObject *args);
// End of forward declarations


static PyMethodDef sdk_OrthancPluginImage_Methods[] = {
  { "GetImagePixelFormat",
    (PyCFunction) sdk_OrthancPluginImage_OrthancPluginGetImagePixelFormat, METH_VARARGS,
    "Generated from C function OrthancPluginGetImagePixelFormat()" },
  { "GetImageWidth",
    (PyCFunction) sdk_OrthancPluginImage_OrthancPluginGetImageWidth, METH_VARARGS,
    "Generated from C function OrthancPluginGetImageWidth()" },
  { "GetImageHeight",
    (PyCFunction) sdk_OrthancPluginImage_OrthancPluginGetImageHeight, METH_VARARGS,
    "Generated from C function OrthancPluginGetImageHeight()" },
  { "GetImagePitch",
    (PyCFunction) sdk_OrthancPluginImage_OrthancPluginGetImagePitch, METH_VARARGS,
    "Generated from C function OrthancPluginGetImagePitch()" },
  { "ConvertPixelFormat",
    (PyCFunction) sdk_OrthancPluginImage_OrthancPluginConvertPixelFormat, METH_VARARGS,
    "Generated from C function OrthancPluginConvertPixelFormat()" },
  { "DrawText",
    (PyCFunction) sdk_OrthancPluginImage_OrthancPluginDrawText, METH_VARARGS,
    "Generated from C function OrthancPluginDrawText()" },
  { "GetImageBuffer",
    (PyCFunction) GetImageBuffer, METH_VARARGS,
    "Generated from C function OrthancPluginGetImageBuffer()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginImage_Constructor(
  sdk_OrthancPluginImage_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginImage");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginImage*>(static_cast<intptr_t>(object));
    self->borrowed_ = borrowed;
    return 0;
  }
  else
  {
    PyErr_SetString(PyExc_ValueError, "Expected a pair (pointer, borrowed) in the constructor");
    return -1;
  }
}


/**
 * Static global structure => the fields that are beyond the last
 * initialized field are set to zero.
 * https://stackoverflow.com/a/11152199/881731
 **/
static PyTypeObject sdk_OrthancPluginImage_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.Image",    /* tp_name */
  sizeof(sdk_OrthancPluginImage_Object), /* tp_basicsize */
};


static void sdk_OrthancPluginImage_Destructor(PyObject *self)
{
  PythonLock::LogCall("Destroying Python object of class OrthancPluginImage");

  sdk_OrthancPluginImage_Object& tmp = *((sdk_OrthancPluginImage_Object*) self);
  
  if (tmp.object_ != NULL &&
      !tmp.borrowed_)
  {
    OrthancPluginFreeImage(OrthancPlugins::GetGlobalContext(), tmp.object_);
    tmp.object_ = NULL;
  }
  
  Py_TYPE(self)->tp_free((PyObject *)self);
}


static void RegisterOrthancPluginImageClass(PyObject* module)
{
  sdk_OrthancPluginImage_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginImage_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginImage_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginImage";
  sdk_OrthancPluginImage_Type.tp_methods = sdk_OrthancPluginImage_Methods;
  sdk_OrthancPluginImage_Type.tp_init = (initproc) sdk_OrthancPluginImage_Constructor;

  /**
   * "tp_dealloc is called when the reference count of the object goes
   * down to zero. This is where you destroy the object and its
   * members. It should then free the memory occupied by the object by
   * calling tp_free."
   * https://stackoverflow.com/a/24863227/881731
   **/
  sdk_OrthancPluginImage_Type.tp_dealloc = sdk_OrthancPluginImage_Destructor;
  
  if (PyType_Ready(&sdk_OrthancPluginImage_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginImage");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginImage_Type);
  if (PyModule_AddObject(module, "Image", (PyObject *)&sdk_OrthancPluginImage_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginImage");
    Py_DECREF(&sdk_OrthancPluginImage_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyTypeObject* GetOrthancPluginImageType()
{
  return &sdk_OrthancPluginImage_Type;
}
