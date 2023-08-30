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
static PyObject *sdk_OrthancPluginFindAnswers_OrthancPluginFindAddAnswer(
  sdk_OrthancPluginFindAnswers_Object* self, PyObject *args);
static PyObject *sdk_OrthancPluginFindAnswers_OrthancPluginFindMarkIncomplete(
  sdk_OrthancPluginFindAnswers_Object* self, PyObject *args);
// End of forward declarations


// Forward declaration of the custom methods
// End of forward declarations


static PyMethodDef sdk_OrthancPluginFindAnswers_Methods[] = {
  { "FindAddAnswer",
    (PyCFunction) sdk_OrthancPluginFindAnswers_OrthancPluginFindAddAnswer, METH_VARARGS,
    "Generated from C function OrthancPluginFindAddAnswer()" },
  { "FindMarkIncomplete",
    (PyCFunction) sdk_OrthancPluginFindAnswers_OrthancPluginFindMarkIncomplete, METH_VARARGS,
    "Generated from C function OrthancPluginFindMarkIncomplete()" },
  { NULL }  /* Sentinel */
};


static int sdk_OrthancPluginFindAnswers_Constructor(
  sdk_OrthancPluginFindAnswers_Object *self, PyObject *args, PyObject *kwds)
{
  PythonLock::LogCall("Creating Python object of class OrthancPluginFindAnswers");

  self->object_ = NULL;
  self->borrowed_ = false;
  
  long long object = 0;
  unsigned char borrowed = false;
  
  if (PyArg_ParseTuple(args, "Lb", &object, &borrowed))
  {
    self->object_ = reinterpret_cast<OrthancPluginFindAnswers*>(static_cast<intptr_t>(object));
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
static PyTypeObject sdk_OrthancPluginFindAnswers_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "orthanc.FindAnswers",    /* tp_name */
  sizeof(sdk_OrthancPluginFindAnswers_Object), /* tp_basicsize */
};




static void RegisterOrthancPluginFindAnswersClass(PyObject* module)
{
  sdk_OrthancPluginFindAnswers_Type.tp_new = PyType_GenericNew;
  sdk_OrthancPluginFindAnswers_Type.tp_flags = Py_TPFLAGS_DEFAULT;
  sdk_OrthancPluginFindAnswers_Type.tp_doc = "Generated from Orthanc C class: OrthancPluginFindAnswers";
  sdk_OrthancPluginFindAnswers_Type.tp_methods = sdk_OrthancPluginFindAnswers_Methods;
  sdk_OrthancPluginFindAnswers_Type.tp_init = (initproc) sdk_OrthancPluginFindAnswers_Constructor;

  
  if (PyType_Ready(&sdk_OrthancPluginFindAnswers_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginFindAnswers");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  Py_INCREF(&sdk_OrthancPluginFindAnswers_Type);
  if (PyModule_AddObject(module, "FindAnswers", (PyObject *)&sdk_OrthancPluginFindAnswers_Type) < 0)
  {
    OrthancPlugins::LogError("Cannot register Python class: OrthancPluginFindAnswers");
    Py_DECREF(&sdk_OrthancPluginFindAnswers_Type);
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PyTypeObject* GetOrthancPluginFindAnswersType()
{
  return &sdk_OrthancPluginFindAnswers_Type;
}
