/**
 * SPDX-FileCopyrightText: 2020-2023 Osimis S.A., 2024-2025 Orthanc Team SRL, 2021-2025 Sebastien Jodogne, ICTEAM UCLouvain
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2023 Osimis S.A., Belgium
 * Copyright (C) 2024-2025 Orthanc Team SRL, Belgium
 * Copyright (C) 2021-2025 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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


// WARNING: Auto-generated file. Do not modify it by hand.


// Forward declaration of the custom global functions
extern PyObject *CreateImageFromBuffer(PyObject* module, PyObject *args);
extern PyObject *LookupDictionary(PyObject* module, PyObject *args);
extern PyObject *RegisterFindCallback(PyObject* module, PyObject *args);
extern PyObject *RegisterIncomingCStoreInstanceFilter(PyObject* module, PyObject *args);
extern PyObject *RegisterIncomingHttpRequestFilter(PyObject* module, PyObject *args);
extern PyObject *RegisterMoveCallback(PyObject* module, PyObject *args);
extern PyObject *RegisterMoveCallback2(PyObject* module, PyObject *args);
extern PyObject *RegisterOnChangeCallback(PyObject* module, PyObject *args);
extern PyObject *RegisterOnStoredInstanceCallback(PyObject* module, PyObject *args);
extern PyObject *RegisterReceivedInstanceCallback(PyObject* module, PyObject *args);
extern PyObject *RegisterRestCallback(PyObject* module, PyObject *args);
extern PyObject *RegisterStorageArea(PyObject* module, PyObject *args);
extern PyObject *RegisterStorageCommitmentScpCallback(PyObject* module, PyObject *args);
extern PyObject *RegisterWorklistCallback(PyObject* module, PyObject *args);
// End of forward declarations


static PyObject* sdk_OrthancPluginAutodetectMimeType(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginAutodetectMimeType()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginAutodetectMimeType(OrthancPlugins::GetGlobalContext(), arg0);
  }
  
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

static PyObject* sdk_OrthancPluginBufferCompression(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginBufferCompression()");

  Py_buffer arg0;
  long int arg2 = 0;
  unsigned char arg3 = 0;

  if (!PyArg_ParseTuple(args, "s*lb", &arg0, &arg2, &arg3))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginBufferCompression(OrthancPlugins::GetGlobalContext(), *buffer, arg0.buf, arg0.len, static_cast<OrthancPluginCompressionType>(arg2), arg3);
  }
  PyBuffer_Release(&arg0);
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

static PyObject* sdk_OrthancPluginCheckVersion(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCheckVersion()");



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginCheckVersion(OrthancPlugins::GetGlobalContext());
  }
  
  return PyLong_FromLong(value);
}

static PyObject* sdk_OrthancPluginCheckVersionAdvanced(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCheckVersionAdvanced()");

  long int arg0 = 0;
  long int arg1 = 0;
  long int arg2 = 0;

  if (!PyArg_ParseTuple(args, "lll", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginCheckVersionAdvanced(OrthancPlugins::GetGlobalContext(), arg0, arg1, arg2);
  }
  
  return PyLong_FromLong(value);
}

static PyObject* sdk_OrthancPluginCompressJpegImage(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCompressJpegImage()");

  long int arg0 = 0;
  unsigned long arg1 = 0;
  unsigned long arg2 = 0;
  unsigned long arg3 = 0;
  Py_buffer arg4;
  unsigned char arg5 = 0;

  if (!PyArg_ParseTuple(args, "lkkks*b", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (6 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginCompressJpegImage(OrthancPlugins::GetGlobalContext(), *buffer, static_cast<OrthancPluginPixelFormat>(arg0), arg1, arg2, arg3, arg4.buf, arg5);
  }
  PyBuffer_Release(&arg4);
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

static PyObject* sdk_OrthancPluginCompressPngImage(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCompressPngImage()");

  long int arg0 = 0;
  unsigned long arg1 = 0;
  unsigned long arg2 = 0;
  unsigned long arg3 = 0;
  Py_buffer arg4;

  if (!PyArg_ParseTuple(args, "lkkks*", &arg0, &arg1, &arg2, &arg3, &arg4))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (5 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginCompressPngImage(OrthancPlugins::GetGlobalContext(), *buffer, static_cast<OrthancPluginPixelFormat>(arg0), arg1, arg2, arg3, arg4.buf);
  }
  PyBuffer_Release(&arg4);
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

static PyObject* sdk_OrthancPluginComputeMd5(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginComputeMd5()");

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "s*", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginComputeMd5(OrthancPlugins::GetGlobalContext(), arg0.buf, arg0.len));
  }
  PyBuffer_Release(&arg0);
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

static PyObject* sdk_OrthancPluginComputeSha1(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginComputeSha1()");

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "s*", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginComputeSha1(OrthancPlugins::GetGlobalContext(), arg0.buf, arg0.len));
  }
  PyBuffer_Release(&arg0);
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

static PyObject* sdk_OrthancPluginCreateDicom(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCreateDicom()");

  const char* arg0 = NULL;
  PyObject* arg1 = NULL;
  long int arg2 = 0;

  if (!PyArg_ParseTuple(args, "sOl", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  if (arg1 != Py_None && Py_TYPE(arg1) != GetOrthancPluginImageType())
  {
    PyErr_SetString(PyExc_TypeError, "Invalid orthanc.OrthancPluginImage object");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginCreateDicom(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1 == Py_None ? NULL : reinterpret_cast<sdk_OrthancPluginImage_Object*>(arg1)->object_, static_cast<OrthancPluginCreateDicomFlags>(arg2));
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

static PyObject* sdk_OrthancPluginCreateDicom2(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCreateDicom2()");

  const char* arg0 = NULL;
  PyObject* arg1 = NULL;
  long int arg2 = 0;
  const char* arg3 = NULL;

  if (!PyArg_ParseTuple(args, "sOls", &arg0, &arg1, &arg2, &arg3))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (4 arguments expected)");
    return NULL;
  }

  if (arg1 != Py_None && Py_TYPE(arg1) != GetOrthancPluginImageType())
  {
    PyErr_SetString(PyExc_TypeError, "Invalid orthanc.OrthancPluginImage object");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginCreateDicom2(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1 == Py_None ? NULL : reinterpret_cast<sdk_OrthancPluginImage_Object*>(arg1)->object_, static_cast<OrthancPluginCreateDicomFlags>(arg2), arg3);
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

static PyObject* sdk_OrthancPluginCreateDicomInstance(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCreateDicomInstance()");

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "s*", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginDicomInstance* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginCreateDicomInstance(OrthancPlugins::GetGlobalContext(), arg0.buf, arg0.len);
  }
  PyBuffer_Release(&arg0);
  if (obj == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;  
  }
  else
  {
    PyObject *argList = Py_BuildValue("Lb", obj, false /* not borrowed */);
    PyObject *python = PyObject_CallObject((PyObject *) &sdk_OrthancPluginDicomInstance_Type, argList);
    Py_DECREF(argList);
    return python;
  }
}

static PyObject* sdk_OrthancPluginCreateFindMatcher(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCreateFindMatcher()");

  Py_buffer arg0;

  if (!PyArg_ParseTuple(args, "s*", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginFindMatcher* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginCreateFindMatcher(OrthancPlugins::GetGlobalContext(), arg0.buf, arg0.len);
  }
  PyBuffer_Release(&arg0);
  if (obj == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;  
  }
  else
  {
    PyObject *argList = Py_BuildValue("Lb", obj, false /* not borrowed */);
    PyObject *python = PyObject_CallObject((PyObject *) &sdk_OrthancPluginFindMatcher_Type, argList);
    Py_DECREF(argList);
    return python;
  }
}

static PyObject* sdk_OrthancPluginCreateImage(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginCreateImage()");

  long int arg0 = 0;
  unsigned long arg1 = 0;
  unsigned long arg2 = 0;

  if (!PyArg_ParseTuple(args, "lkk", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginImage* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginCreateImage(OrthancPlugins::GetGlobalContext(), static_cast<OrthancPluginPixelFormat>(arg0), arg1, arg2);
  }
  
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

static PyObject* sdk_OrthancPluginDecodeDicomImage(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginDecodeDicomImage()");

  Py_buffer arg0;
  unsigned long arg2 = 0;

  if (!PyArg_ParseTuple(args, "s*k", &arg0, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginImage* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginDecodeDicomImage(OrthancPlugins::GetGlobalContext(), arg0.buf, arg0.len, arg2);
  }
  PyBuffer_Release(&arg0);
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

static PyObject* sdk_OrthancPluginDicomBufferToJson(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginDicomBufferToJson()");

  Py_buffer arg0;
  long int arg2 = 0;
  long int arg3 = 0;
  unsigned long arg4 = 0;

  if (!PyArg_ParseTuple(args, "s*llk", &arg0, &arg2, &arg3, &arg4))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (4 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginDicomBufferToJson(OrthancPlugins::GetGlobalContext(), arg0.buf, arg0.len, static_cast<OrthancPluginDicomToJsonFormat>(arg2), static_cast<OrthancPluginDicomToJsonFlags>(arg3), arg4));
  }
  PyBuffer_Release(&arg0);
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

static PyObject* sdk_OrthancPluginDicomInstanceToJson(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginDicomInstanceToJson()");

  const char* arg0 = NULL;
  long int arg1 = 0;
  long int arg2 = 0;
  unsigned long arg3 = 0;

  if (!PyArg_ParseTuple(args, "sllk", &arg0, &arg1, &arg2, &arg3))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (4 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginDicomInstanceToJson(OrthancPlugins::GetGlobalContext(), arg0, static_cast<OrthancPluginDicomToJsonFormat>(arg1), static_cast<OrthancPluginDicomToJsonFlags>(arg2), arg3));
  }
  
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

static PyObject* sdk_OrthancPluginExtendOrthancExplorer(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginExtendOrthancExplorer()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginExtendOrthancExplorer(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginExtendOrthancExplorer2(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginExtendOrthancExplorer2()");

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginExtendOrthancExplorer2(OrthancPlugins::GetGlobalContext(), arg0, arg1);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginGenerateRestApiAuthorizationToken(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGenerateRestApiAuthorizationToken()");



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGenerateRestApiAuthorizationToken(OrthancPlugins::GetGlobalContext()));
  }
  
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

static PyObject* sdk_OrthancPluginGenerateUuid(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGenerateUuid()");



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGenerateUuid(OrthancPlugins::GetGlobalContext()));
  }
  
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

static PyObject* sdk_OrthancPluginGetCommandLineArgument(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetCommandLineArgument()");

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetCommandLineArgument(OrthancPlugins::GetGlobalContext(), arg0));
  }
  
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

static PyObject* sdk_OrthancPluginGetCommandLineArgumentsCount(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetCommandLineArgumentsCount()");



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetCommandLineArgumentsCount(OrthancPlugins::GetGlobalContext());
  }
  
  return PyLong_FromLong(value);
}

static PyObject* sdk_OrthancPluginGetConfiguration(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetConfiguration()");



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetConfiguration(OrthancPlugins::GetGlobalContext()));
  }
  
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

static PyObject* sdk_OrthancPluginGetConfigurationPath(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetConfigurationPath()");



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetConfigurationPath(OrthancPlugins::GetGlobalContext()));
  }
  
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

static PyObject* sdk_OrthancPluginGetDatabaseServerIdentifier(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetDatabaseServerIdentifier()");



  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginGetDatabaseServerIdentifier(OrthancPlugins::GetGlobalContext());
  }
  
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

static PyObject* sdk_OrthancPluginGetDicomForInstance(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetDicomForInstance()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginGetDicomForInstance(OrthancPlugins::GetGlobalContext(), *buffer, arg0);
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

static PyObject* sdk_OrthancPluginGetErrorDescription(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetErrorDescription()");

  long int arg0 = 0;

  if (!PyArg_ParseTuple(args, "l", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginGetErrorDescription(OrthancPlugins::GetGlobalContext(), static_cast<OrthancPluginErrorCode>(arg0));
  }
  
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

static PyObject* sdk_OrthancPluginGetExpectedDatabaseVersion(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetExpectedDatabaseVersion()");



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetExpectedDatabaseVersion(OrthancPlugins::GetGlobalContext());
  }
  
  return PyLong_FromLong(value);
}

static PyObject* sdk_OrthancPluginGetFontName(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetFontName()");

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  const char* s;
  {
    PythonThreadsAllower allower;
    s = OrthancPluginGetFontName(OrthancPlugins::GetGlobalContext(), arg0);
  }
  
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

static PyObject* sdk_OrthancPluginGetFontSize(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetFontSize()");

  unsigned long arg0 = 0;

  if (!PyArg_ParseTuple(args, "k", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetFontSize(OrthancPlugins::GetGlobalContext(), arg0);
  }
  
  return PyLong_FromLong(value);
}

static PyObject* sdk_OrthancPluginGetFontsCount(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetFontsCount()");



  long value;
  {
    PythonThreadsAllower allower;
    value = OrthancPluginGetFontsCount(OrthancPlugins::GetGlobalContext());
  }
  
  return PyLong_FromLong(value);
}

static PyObject* sdk_OrthancPluginGetGlobalProperty(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetGlobalProperty()");

  long int arg0 = 0;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ls", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetGlobalProperty(OrthancPlugins::GetGlobalContext(), arg0, arg1));
  }
  
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

static PyObject* sdk_OrthancPluginGetOrthancDirectory(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetOrthancDirectory()");



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetOrthancDirectory(OrthancPlugins::GetGlobalContext()));
  }
  
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

static PyObject* sdk_OrthancPluginGetOrthancPath(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetOrthancPath()");



  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetOrthancPath(OrthancPlugins::GetGlobalContext()));
  }
  
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

static PyObject* sdk_OrthancPluginGetPeers(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetPeers()");



  // This is the case of a constructor
  OrthancPluginPeers* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginGetPeers(OrthancPlugins::GetGlobalContext());
  }
  
  if (obj == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;  
  }
  else
  {
    PyObject *argList = Py_BuildValue("Lb", obj, false /* not borrowed */);
    PyObject *python = PyObject_CallObject((PyObject *) &sdk_OrthancPluginPeers_Type, argList);
    Py_DECREF(argList);
    return python;
  }
}

static PyObject* sdk_OrthancPluginGetTagName(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginGetTagName()");

  unsigned short arg0 = 0;
  unsigned short arg1 = 0;
  const char* arg2 = NULL;

  if (!PyArg_ParseTuple(args, "HHs", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginGetTagName(OrthancPlugins::GetGlobalContext(), arg0, arg1, arg2));
  }
  
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

static PyObject* sdk_OrthancPluginHttpDelete(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginHttpDelete()");

  const char* arg0 = NULL;
  const char* arg1 = NULL;
  const char* arg2 = NULL;

  if (!PyArg_ParseTuple(args, "sss", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginHttpDelete(OrthancPlugins::GetGlobalContext(), arg0, arg1, arg2);
  }
  

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

static PyObject* sdk_OrthancPluginHttpGet(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginHttpGet()");

  const char* arg0 = NULL;
  const char* arg1 = NULL;
  const char* arg2 = NULL;

  if (!PyArg_ParseTuple(args, "sss", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginHttpGet(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1, arg2);
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

static PyObject* sdk_OrthancPluginHttpPost(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginHttpPost()");

  const char* arg0 = NULL;
  Py_buffer arg1;
  const char* arg3 = NULL;
  const char* arg4 = NULL;

  if (!PyArg_ParseTuple(args, "ss*ss", &arg0, &arg1, &arg3, &arg4))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (4 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginHttpPost(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1.buf, arg1.len, arg3, arg4);
  }
  PyBuffer_Release(&arg1);
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

static PyObject* sdk_OrthancPluginHttpPut(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginHttpPut()");

  const char* arg0 = NULL;
  Py_buffer arg1;
  const char* arg3 = NULL;
  const char* arg4 = NULL;

  if (!PyArg_ParseTuple(args, "ss*ss", &arg0, &arg1, &arg3, &arg4))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (4 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginHttpPut(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1.buf, arg1.len, arg3, arg4);
  }
  PyBuffer_Release(&arg1);
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

static PyObject* sdk_OrthancPluginLoadDicomInstance(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLoadDicomInstance()");

  const char* arg0 = NULL;
  long int arg1 = 0;

  if (!PyArg_ParseTuple(args, "sl", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginDicomInstance* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginLoadDicomInstance(OrthancPlugins::GetGlobalContext(), arg0, static_cast<OrthancPluginLoadDicomInstanceMode>(arg1));
  }
  
  if (obj == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;  
  }
  else
  {
    PyObject *argList = Py_BuildValue("Lb", obj, false /* not borrowed */);
    PyObject *python = PyObject_CallObject((PyObject *) &sdk_OrthancPluginDicomInstance_Type, argList);
    Py_DECREF(argList);
    return python;
  }
}

static PyObject* sdk_OrthancPluginLogError(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLogError()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginLogError(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginLogInfo(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLogInfo()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginLogInfo(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginLogMessage(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLogMessage()");

  const char* arg0 = NULL;
  const char* arg1 = NULL;
  const char* arg2 = NULL;
  unsigned long arg3 = 0;
  long int arg4 = 0;
  long int arg5 = 0;

  if (!PyArg_ParseTuple(args, "ssskll", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (6 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginLogMessage(OrthancPlugins::GetGlobalContext(), arg0, arg1, arg2, arg3, static_cast<OrthancPluginLogCategory>(arg4), static_cast<OrthancPluginLogLevel>(arg5));
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginLogWarning(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLogWarning()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginLogWarning(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginLookupInstance(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLookupInstance()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginLookupInstance(OrthancPlugins::GetGlobalContext(), arg0));
  }
  
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

static PyObject* sdk_OrthancPluginLookupPatient(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLookupPatient()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginLookupPatient(OrthancPlugins::GetGlobalContext(), arg0));
  }
  
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

static PyObject* sdk_OrthancPluginLookupSeries(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLookupSeries()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginLookupSeries(OrthancPlugins::GetGlobalContext(), arg0));
  }
  
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

static PyObject* sdk_OrthancPluginLookupStudy(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLookupStudy()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginLookupStudy(OrthancPlugins::GetGlobalContext(), arg0));
  }
  
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

static PyObject* sdk_OrthancPluginLookupStudyWithAccessionNumber(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginLookupStudyWithAccessionNumber()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::OrthancString s;
  {
    PythonThreadsAllower allower;
    s.Assign(OrthancPluginLookupStudyWithAccessionNumber(OrthancPlugins::GetGlobalContext(), arg0));
  }
  
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

static PyObject* sdk_OrthancPluginReadFile(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginReadFile()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginReadFile(OrthancPlugins::GetGlobalContext(), *buffer, arg0);
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

static PyObject* sdk_OrthancPluginRegisterDictionaryTag(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRegisterDictionaryTag()");

  unsigned short arg0 = 0;
  unsigned short arg1 = 0;
  long int arg2 = 0;
  const char* arg3 = NULL;
  unsigned long arg4 = 0;
  unsigned long arg5 = 0;

  if (!PyArg_ParseTuple(args, "HHlskk", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (6 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRegisterDictionaryTag(OrthancPlugins::GetGlobalContext(), arg0, arg1, static_cast<OrthancPluginValueRepresentation>(arg2), arg3, arg4, arg5);
  }
  

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

static PyObject* sdk_OrthancPluginRegisterErrorCode(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRegisterErrorCode()");

  long int arg0 = 0;
  unsigned short arg1 = 0;
  const char* arg2 = NULL;

  if (!PyArg_ParseTuple(args, "lHs", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRegisterErrorCode(OrthancPlugins::GetGlobalContext(), arg0, arg1, arg2);
  }
  

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

static PyObject* sdk_OrthancPluginRegisterPrivateDictionaryTag(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRegisterPrivateDictionaryTag()");

  unsigned short arg0 = 0;
  unsigned short arg1 = 0;
  long int arg2 = 0;
  const char* arg3 = NULL;
  unsigned long arg4 = 0;
  unsigned long arg5 = 0;
  const char* arg6 = NULL;

  if (!PyArg_ParseTuple(args, "HHlskks", &arg0, &arg1, &arg2, &arg3, &arg4, &arg5, &arg6))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (7 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRegisterPrivateDictionaryTag(OrthancPlugins::GetGlobalContext(), arg0, arg1, static_cast<OrthancPluginValueRepresentation>(arg2), arg3, arg4, arg5, arg6);
  }
  

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

static PyObject* sdk_OrthancPluginRestApiDelete(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRestApiDelete()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRestApiDelete(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

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

static PyObject* sdk_OrthancPluginRestApiDeleteAfterPlugins(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRestApiDeleteAfterPlugins()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRestApiDeleteAfterPlugins(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

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

static PyObject* sdk_OrthancPluginRestApiGet(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRestApiGet()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRestApiGet(OrthancPlugins::GetGlobalContext(), *buffer, arg0);
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

static PyObject* sdk_OrthancPluginRestApiGetAfterPlugins(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRestApiGetAfterPlugins()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRestApiGetAfterPlugins(OrthancPlugins::GetGlobalContext(), *buffer, arg0);
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

static PyObject* sdk_OrthancPluginRestApiPost(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRestApiPost()");

  const char* arg0 = NULL;
  Py_buffer arg1;

  if (!PyArg_ParseTuple(args, "ss*", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRestApiPost(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1.buf, arg1.len);
  }
  PyBuffer_Release(&arg1);
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

static PyObject* sdk_OrthancPluginRestApiPostAfterPlugins(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRestApiPostAfterPlugins()");

  const char* arg0 = NULL;
  Py_buffer arg1;

  if (!PyArg_ParseTuple(args, "ss*", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRestApiPostAfterPlugins(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1.buf, arg1.len);
  }
  PyBuffer_Release(&arg1);
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

static PyObject* sdk_OrthancPluginRestApiPut(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRestApiPut()");

  const char* arg0 = NULL;
  Py_buffer arg1;

  if (!PyArg_ParseTuple(args, "ss*", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRestApiPut(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1.buf, arg1.len);
  }
  PyBuffer_Release(&arg1);
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

static PyObject* sdk_OrthancPluginRestApiPutAfterPlugins(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginRestApiPutAfterPlugins()");

  const char* arg0 = NULL;
  Py_buffer arg1;

  if (!PyArg_ParseTuple(args, "ss*", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPlugins::MemoryBuffer buffer;
  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginRestApiPutAfterPlugins(OrthancPlugins::GetGlobalContext(), *buffer, arg0, arg1.buf, arg1.len);
  }
  PyBuffer_Release(&arg1);
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

static PyObject* sdk_OrthancPluginSetCurrentThreadName(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginSetCurrentThreadName()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginSetCurrentThreadName(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

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

static PyObject* sdk_OrthancPluginSetDescription(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginSetDescription()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSetDescription(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginSetDescription2(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginSetDescription2()");

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSetDescription2(OrthancPlugins::GetGlobalContext(), arg0, arg1);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginSetGlobalProperty(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginSetGlobalProperty()");

  long int arg0 = 0;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ls", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginSetGlobalProperty(OrthancPlugins::GetGlobalContext(), arg0, arg1);
  }
  

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

static PyObject* sdk_OrthancPluginSetMetricsValue(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginSetMetricsValue()");

  const char* arg0 = NULL;
  float arg1 = 0;
  long int arg2 = 0;

  if (!PyArg_ParseTuple(args, "sfl", &arg0, &arg1, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (3 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSetMetricsValue(OrthancPlugins::GetGlobalContext(), arg0, arg1, static_cast<OrthancPluginMetricsType>(arg2));
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginSetRootUri(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginSetRootUri()");

  const char* arg0 = NULL;

  if (!PyArg_ParseTuple(args, "s", &arg0))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (1 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSetRootUri(OrthancPlugins::GetGlobalContext(), arg0);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginSetRootUri2(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginSetRootUri2()");

  const char* arg0 = NULL;
  const char* arg1 = NULL;

  if (!PyArg_ParseTuple(args, "ss", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  {
    PythonThreadsAllower allower;
    OrthancPluginSetRootUri2(OrthancPlugins::GetGlobalContext(), arg0, arg1);
  }
  

  Py_INCREF(Py_None);
  return Py_None;
}

static PyObject* sdk_OrthancPluginTranscodeDicomInstance(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginTranscodeDicomInstance()");

  Py_buffer arg0;
  const char* arg2 = NULL;

  if (!PyArg_ParseTuple(args, "s*s", &arg0, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginDicomInstance* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginTranscodeDicomInstance(OrthancPlugins::GetGlobalContext(), arg0.buf, arg0.len, arg2);
  }
  PyBuffer_Release(&arg0);
  if (obj == NULL)
  {
    PythonLock::RaiseException(OrthancPluginErrorCode_InternalError);
    return NULL;  
  }
  else
  {
    PyObject *argList = Py_BuildValue("Lb", obj, false /* not borrowed */);
    PyObject *python = PyObject_CallObject((PyObject *) &sdk_OrthancPluginDicomInstance_Type, argList);
    Py_DECREF(argList);
    return python;
  }
}

static PyObject* sdk_OrthancPluginUncompressImage(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginUncompressImage()");

  Py_buffer arg0;
  long int arg2 = 0;

  if (!PyArg_ParseTuple(args, "s*l", &arg0, &arg2))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  // This is the case of a constructor
  OrthancPluginImage* obj;
  {
    PythonThreadsAllower allower;
    obj = OrthancPluginUncompressImage(OrthancPlugins::GetGlobalContext(), arg0.buf, arg0.len, static_cast<OrthancPluginImageFormat>(arg2));
  }
  PyBuffer_Release(&arg0);
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

static PyObject* sdk_OrthancPluginWriteFile(PyObject* module, PyObject* args)
{
  PythonLock::LogCall("Calling Python global function: OrthancPluginWriteFile()");

  const char* arg0 = NULL;
  Py_buffer arg1;

  if (!PyArg_ParseTuple(args, "ss*", &arg0, &arg1))
  {
    PyErr_SetString(PyExc_TypeError, "Bad types for the arguments (2 arguments expected)");
    return NULL;
  }

  OrthancPluginErrorCode code;
  {
    PythonThreadsAllower allower;
    code = OrthancPluginWriteFile(OrthancPlugins::GetGlobalContext(), arg0, arg1.buf, arg1.len);
  }
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


static PyMethodDef ORTHANC_SDK_FUNCTIONS[] = 
{
  { "AutodetectMimeType", sdk_OrthancPluginAutodetectMimeType, METH_VARARGS,
    "Generated from C function OrthancPluginAutodetectMimeType()" },
  { "BufferCompression", sdk_OrthancPluginBufferCompression, METH_VARARGS,
    "Generated from C function OrthancPluginBufferCompression()" },
  { "CheckVersion", sdk_OrthancPluginCheckVersion, METH_VARARGS,
    "Generated from C function OrthancPluginCheckVersion()" },
  { "CheckVersionAdvanced", sdk_OrthancPluginCheckVersionAdvanced, METH_VARARGS,
    "Generated from C function OrthancPluginCheckVersionAdvanced()" },
  { "CompressJpegImage", sdk_OrthancPluginCompressJpegImage, METH_VARARGS,
    "Generated from C function OrthancPluginCompressJpegImage()" },
  { "CompressPngImage", sdk_OrthancPluginCompressPngImage, METH_VARARGS,
    "Generated from C function OrthancPluginCompressPngImage()" },
  { "ComputeMd5", sdk_OrthancPluginComputeMd5, METH_VARARGS,
    "Generated from C function OrthancPluginComputeMd5()" },
  { "ComputeSha1", sdk_OrthancPluginComputeSha1, METH_VARARGS,
    "Generated from C function OrthancPluginComputeSha1()" },
  { "CreateDicom", sdk_OrthancPluginCreateDicom, METH_VARARGS,
    "Generated from C function OrthancPluginCreateDicom()" },
  { "CreateDicom2", sdk_OrthancPluginCreateDicom2, METH_VARARGS,
    "Generated from C function OrthancPluginCreateDicom2()" },
  { "CreateDicomInstance", sdk_OrthancPluginCreateDicomInstance, METH_VARARGS,
    "Generated from C function OrthancPluginCreateDicomInstance()" },
  { "CreateFindMatcher", sdk_OrthancPluginCreateFindMatcher, METH_VARARGS,
    "Generated from C function OrthancPluginCreateFindMatcher()" },
  { "CreateImage", sdk_OrthancPluginCreateImage, METH_VARARGS,
    "Generated from C function OrthancPluginCreateImage()" },
  { "DecodeDicomImage", sdk_OrthancPluginDecodeDicomImage, METH_VARARGS,
    "Generated from C function OrthancPluginDecodeDicomImage()" },
  { "DicomBufferToJson", sdk_OrthancPluginDicomBufferToJson, METH_VARARGS,
    "Generated from C function OrthancPluginDicomBufferToJson()" },
  { "DicomInstanceToJson", sdk_OrthancPluginDicomInstanceToJson, METH_VARARGS,
    "Generated from C function OrthancPluginDicomInstanceToJson()" },
  { "ExtendOrthancExplorer", sdk_OrthancPluginExtendOrthancExplorer, METH_VARARGS,
    "Generated from C function OrthancPluginExtendOrthancExplorer()" },
  { "ExtendOrthancExplorer2", sdk_OrthancPluginExtendOrthancExplorer2, METH_VARARGS,
    "Generated from C function OrthancPluginExtendOrthancExplorer2()" },
  { "GenerateRestApiAuthorizationToken", sdk_OrthancPluginGenerateRestApiAuthorizationToken, METH_VARARGS,
    "Generated from C function OrthancPluginGenerateRestApiAuthorizationToken()" },
  { "GenerateUuid", sdk_OrthancPluginGenerateUuid, METH_VARARGS,
    "Generated from C function OrthancPluginGenerateUuid()" },
  { "GetCommandLineArgument", sdk_OrthancPluginGetCommandLineArgument, METH_VARARGS,
    "Generated from C function OrthancPluginGetCommandLineArgument()" },
  { "GetCommandLineArgumentsCount", sdk_OrthancPluginGetCommandLineArgumentsCount, METH_VARARGS,
    "Generated from C function OrthancPluginGetCommandLineArgumentsCount()" },
  { "GetConfiguration", sdk_OrthancPluginGetConfiguration, METH_VARARGS,
    "Generated from C function OrthancPluginGetConfiguration()" },
  { "GetConfigurationPath", sdk_OrthancPluginGetConfigurationPath, METH_VARARGS,
    "Generated from C function OrthancPluginGetConfigurationPath()" },
  { "GetDatabaseServerIdentifier", sdk_OrthancPluginGetDatabaseServerIdentifier, METH_VARARGS,
    "Generated from C function OrthancPluginGetDatabaseServerIdentifier()" },
  { "GetDicomForInstance", sdk_OrthancPluginGetDicomForInstance, METH_VARARGS,
    "Generated from C function OrthancPluginGetDicomForInstance()" },
  { "GetErrorDescription", sdk_OrthancPluginGetErrorDescription, METH_VARARGS,
    "Generated from C function OrthancPluginGetErrorDescription()" },
  { "GetExpectedDatabaseVersion", sdk_OrthancPluginGetExpectedDatabaseVersion, METH_VARARGS,
    "Generated from C function OrthancPluginGetExpectedDatabaseVersion()" },
  { "GetFontName", sdk_OrthancPluginGetFontName, METH_VARARGS,
    "Generated from C function OrthancPluginGetFontName()" },
  { "GetFontSize", sdk_OrthancPluginGetFontSize, METH_VARARGS,
    "Generated from C function OrthancPluginGetFontSize()" },
  { "GetFontsCount", sdk_OrthancPluginGetFontsCount, METH_VARARGS,
    "Generated from C function OrthancPluginGetFontsCount()" },
  { "GetGlobalProperty", sdk_OrthancPluginGetGlobalProperty, METH_VARARGS,
    "Generated from C function OrthancPluginGetGlobalProperty()" },
  { "GetOrthancDirectory", sdk_OrthancPluginGetOrthancDirectory, METH_VARARGS,
    "Generated from C function OrthancPluginGetOrthancDirectory()" },
  { "GetOrthancPath", sdk_OrthancPluginGetOrthancPath, METH_VARARGS,
    "Generated from C function OrthancPluginGetOrthancPath()" },
  { "GetPeers", sdk_OrthancPluginGetPeers, METH_VARARGS,
    "Generated from C function OrthancPluginGetPeers()" },
  { "GetTagName", sdk_OrthancPluginGetTagName, METH_VARARGS,
    "Generated from C function OrthancPluginGetTagName()" },
  { "HttpDelete", sdk_OrthancPluginHttpDelete, METH_VARARGS,
    "Generated from C function OrthancPluginHttpDelete()" },
  { "HttpGet", sdk_OrthancPluginHttpGet, METH_VARARGS,
    "Generated from C function OrthancPluginHttpGet()" },
  { "HttpPost", sdk_OrthancPluginHttpPost, METH_VARARGS,
    "Generated from C function OrthancPluginHttpPost()" },
  { "HttpPut", sdk_OrthancPluginHttpPut, METH_VARARGS,
    "Generated from C function OrthancPluginHttpPut()" },
  { "LoadDicomInstance", sdk_OrthancPluginLoadDicomInstance, METH_VARARGS,
    "Generated from C function OrthancPluginLoadDicomInstance()" },
  { "LogError", sdk_OrthancPluginLogError, METH_VARARGS,
    "Generated from C function OrthancPluginLogError()" },
  { "LogInfo", sdk_OrthancPluginLogInfo, METH_VARARGS,
    "Generated from C function OrthancPluginLogInfo()" },
  { "LogMessage", sdk_OrthancPluginLogMessage, METH_VARARGS,
    "Generated from C function OrthancPluginLogMessage()" },
  { "LogWarning", sdk_OrthancPluginLogWarning, METH_VARARGS,
    "Generated from C function OrthancPluginLogWarning()" },
  { "LookupInstance", sdk_OrthancPluginLookupInstance, METH_VARARGS,
    "Generated from C function OrthancPluginLookupInstance()" },
  { "LookupPatient", sdk_OrthancPluginLookupPatient, METH_VARARGS,
    "Generated from C function OrthancPluginLookupPatient()" },
  { "LookupSeries", sdk_OrthancPluginLookupSeries, METH_VARARGS,
    "Generated from C function OrthancPluginLookupSeries()" },
  { "LookupStudy", sdk_OrthancPluginLookupStudy, METH_VARARGS,
    "Generated from C function OrthancPluginLookupStudy()" },
  { "LookupStudyWithAccessionNumber", sdk_OrthancPluginLookupStudyWithAccessionNumber, METH_VARARGS,
    "Generated from C function OrthancPluginLookupStudyWithAccessionNumber()" },
  { "ReadFile", sdk_OrthancPluginReadFile, METH_VARARGS,
    "Generated from C function OrthancPluginReadFile()" },
  { "RegisterDictionaryTag", sdk_OrthancPluginRegisterDictionaryTag, METH_VARARGS,
    "Generated from C function OrthancPluginRegisterDictionaryTag()" },
  { "RegisterErrorCode", sdk_OrthancPluginRegisterErrorCode, METH_VARARGS,
    "Generated from C function OrthancPluginRegisterErrorCode()" },
  { "RegisterPrivateDictionaryTag", sdk_OrthancPluginRegisterPrivateDictionaryTag, METH_VARARGS,
    "Generated from C function OrthancPluginRegisterPrivateDictionaryTag()" },
  { "RestApiDelete", sdk_OrthancPluginRestApiDelete, METH_VARARGS,
    "Generated from C function OrthancPluginRestApiDelete()" },
  { "RestApiDeleteAfterPlugins", sdk_OrthancPluginRestApiDeleteAfterPlugins, METH_VARARGS,
    "Generated from C function OrthancPluginRestApiDeleteAfterPlugins()" },
  { "RestApiGet", sdk_OrthancPluginRestApiGet, METH_VARARGS,
    "Generated from C function OrthancPluginRestApiGet()" },
  { "RestApiGetAfterPlugins", sdk_OrthancPluginRestApiGetAfterPlugins, METH_VARARGS,
    "Generated from C function OrthancPluginRestApiGetAfterPlugins()" },
  { "RestApiPost", sdk_OrthancPluginRestApiPost, METH_VARARGS,
    "Generated from C function OrthancPluginRestApiPost()" },
  { "RestApiPostAfterPlugins", sdk_OrthancPluginRestApiPostAfterPlugins, METH_VARARGS,
    "Generated from C function OrthancPluginRestApiPostAfterPlugins()" },
  { "RestApiPut", sdk_OrthancPluginRestApiPut, METH_VARARGS,
    "Generated from C function OrthancPluginRestApiPut()" },
  { "RestApiPutAfterPlugins", sdk_OrthancPluginRestApiPutAfterPlugins, METH_VARARGS,
    "Generated from C function OrthancPluginRestApiPutAfterPlugins()" },
  { "SetCurrentThreadName", sdk_OrthancPluginSetCurrentThreadName, METH_VARARGS,
    "Generated from C function OrthancPluginSetCurrentThreadName()" },
  { "SetDescription", sdk_OrthancPluginSetDescription, METH_VARARGS,
    "Generated from C function OrthancPluginSetDescription()" },
  { "SetDescription2", sdk_OrthancPluginSetDescription2, METH_VARARGS,
    "Generated from C function OrthancPluginSetDescription2()" },
  { "SetGlobalProperty", sdk_OrthancPluginSetGlobalProperty, METH_VARARGS,
    "Generated from C function OrthancPluginSetGlobalProperty()" },
  { "SetMetricsValue", sdk_OrthancPluginSetMetricsValue, METH_VARARGS,
    "Generated from C function OrthancPluginSetMetricsValue()" },
  { "SetRootUri", sdk_OrthancPluginSetRootUri, METH_VARARGS,
    "Generated from C function OrthancPluginSetRootUri()" },
  { "SetRootUri2", sdk_OrthancPluginSetRootUri2, METH_VARARGS,
    "Generated from C function OrthancPluginSetRootUri2()" },
  { "TranscodeDicomInstance", sdk_OrthancPluginTranscodeDicomInstance, METH_VARARGS,
    "Generated from C function OrthancPluginTranscodeDicomInstance()" },
  { "UncompressImage", sdk_OrthancPluginUncompressImage, METH_VARARGS,
    "Generated from C function OrthancPluginUncompressImage()" },
  { "WriteFile", sdk_OrthancPluginWriteFile, METH_VARARGS,
    "Generated from C function OrthancPluginWriteFile()" },
  { "CreateImageFromBuffer", CreateImageFromBuffer, METH_VARARGS,
    "Implemented in C++ function CreateImageFromBuffer()" },
  { "LookupDictionary", LookupDictionary, METH_VARARGS,
    "Implemented in C++ function LookupDictionary()" },
  { "RegisterFindCallback", RegisterFindCallback, METH_VARARGS,
    "Implemented in C++ function RegisterFindCallback()" },
  { "RegisterIncomingCStoreInstanceFilter", RegisterIncomingCStoreInstanceFilter, METH_VARARGS,
    "Implemented in C++ function RegisterIncomingCStoreInstanceFilter()" },
  { "RegisterIncomingHttpRequestFilter", RegisterIncomingHttpRequestFilter, METH_VARARGS,
    "Implemented in C++ function RegisterIncomingHttpRequestFilter()" },
  { "RegisterMoveCallback", RegisterMoveCallback, METH_VARARGS,
    "Implemented in C++ function RegisterMoveCallback()" },
  { "RegisterMoveCallback2", RegisterMoveCallback2, METH_VARARGS,
    "Implemented in C++ function RegisterMoveCallback2()" },
  { "RegisterOnChangeCallback", RegisterOnChangeCallback, METH_VARARGS,
    "Implemented in C++ function RegisterOnChangeCallback()" },
  { "RegisterOnStoredInstanceCallback", RegisterOnStoredInstanceCallback, METH_VARARGS,
    "Implemented in C++ function RegisterOnStoredInstanceCallback()" },
  { "RegisterReceivedInstanceCallback", RegisterReceivedInstanceCallback, METH_VARARGS,
    "Implemented in C++ function RegisterReceivedInstanceCallback()" },
  { "RegisterRestCallback", RegisterRestCallback, METH_VARARGS,
    "Implemented in C++ function RegisterRestCallback()" },
  { "RegisterStorageArea", RegisterStorageArea, METH_VARARGS,
    "Implemented in C++ function RegisterStorageArea()" },
  { "RegisterStorageCommitmentScpCallback", RegisterStorageCommitmentScpCallback, METH_VARARGS,
    "Implemented in C++ function RegisterStorageCommitmentScpCallback()" },
  { "RegisterWorklistCallback", RegisterWorklistCallback, METH_VARARGS,
    "Implemented in C++ function RegisterWorklistCallback()" },
  { NULL, NULL }
};


PyMethodDef* GetOrthancSdkFunctions()
{
  return ORTHANC_SDK_FUNCTIONS;
}
