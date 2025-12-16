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


#include "PythonHeaderWrapper.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"
#include "PythonString.h"

#include "StorageArea3.h"

#include <sdk.h>
#include <limits>


#if ORTHANC_PLUGINS_VERSION_IS_ABOVE(1, 9, 0)

static PyObject*  createCallback2_ = NULL;
static PyObject*  readCallback2_ = NULL;
static PyObject*  removeCallback2_ = NULL;


static OrthancPluginErrorCode RunCallback(PythonLock& lock,
                                          PyObject* callback,
                                          const PythonObject& args,
                                          const std::string& name)
{
  PythonObject result(lock, PyObject_CallObject(callback, args.GetPyObject()));

  std::string traceback;
  if (lock.HasErrorOccurred(traceback))
  {
    ORTHANC_PLUGINS_LOG_ERROR("Error in the Python " + name + " callback, traceback:\n" + traceback);
    return OrthancPluginErrorCode_Plugin;
  }
  else
  {
    return OrthancPluginErrorCode_Success;
  }
}


// "callable_protocol_args" : "uuid: str, content_type: ContentType, compression_type: CompressionType, content: bytes, dicom_instance: DicomInstance",
// "callable_protocol_return" : "Tuple" // error code + custom data

static OrthancPluginErrorCode StorageCreate2(OrthancPluginMemoryBuffer* customData,
                                             const char* uuid,
                                             const void* content,
                                             uint64_t size,
                                             OrthancPluginContentType type,
                                             OrthancPluginCompressionType compressionType,
                                             const OrthancPluginDicomInstance* dicomInstance)
{
  try
  {
    if (createCallback2_ == NULL)
    {
      throw OrthancPlugins::PluginException(OrthancPluginErrorCode_InternalError);
    }
    
    PythonLock lock;

    PythonObject args(lock, PyTuple_New(5));
    PyObject* pDicomInstance;

    {
      PythonObject argsDicomInstance(lock, PyTuple_New(2));
      PyTuple_SetItem(argsDicomInstance.GetPyObject(), 0, PyLong_FromSsize_t((intptr_t) dicomInstance));
      PyTuple_SetItem(argsDicomInstance.GetPyObject(), 1, PyBool_FromLong(true /* borrowed, don't destruct */));
      pDicomInstance = PyObject_CallObject((PyObject*) GetOrthancPluginDicomInstanceType(), argsDicomInstance.GetPyObject());
    }


    PythonString str(lock, uuid);
    PyTuple_SetItem(args.GetPyObject(), 0, str.Release());
    PyTuple_SetItem(args.GetPyObject(), 1, PyLong_FromLong(type));
    PyTuple_SetItem(args.GetPyObject(), 2, PyLong_FromLong(compressionType));
    PyTuple_SetItem(args.GetPyObject(), 3, PyBytes_FromStringAndSize(reinterpret_cast<const char*>(content), size));
    PyTuple_SetItem(args.GetPyObject(), 4, pDicomInstance);

    PythonObject result(lock, PyObject_CallObject(createCallback2_, args.GetPyObject()));
    
    std::string traceback;
    if (lock.HasErrorOccurred(traceback))
    {
      ORTHANC_PLUGINS_LOG_ERROR("Error in the Python StorageCreate2 callback, traceback:\n" + traceback);
      return OrthancPluginErrorCode_Plugin;
    }
    else if (!PyTuple_Check(result.GetPyObject()) || PyTuple_Size(result.GetPyObject()) != 2)
    {
      ORTHANC_PLUGINS_LOG_ERROR("The Python StorageCreate2 callback has not returned a tuple as expected");
      return OrthancPluginErrorCode_Plugin;
    }
    else
    {
      PyObject* pyReturnCode = PyTuple_GET_ITEM(result.GetPyObject(), 0);
      PyObject* pyTargetBuffer = PyTuple_GET_ITEM(result.GetPyObject(), 1);

      if (!PyLong_Check(pyReturnCode))
      {
        ORTHANC_PLUGINS_LOG_ERROR("The Python StorageCreate2 callback has not returned an int as the first element of the return tuple");
        return OrthancPluginErrorCode_Plugin;
      }
      else if (!PyBytes_Check(pyTargetBuffer) && !Py_IsNone(pyTargetBuffer))
      {
        ORTHANC_PLUGINS_LOG_ERROR("The Python StorageCreate2 callback has not returned a byte array as the second element of the return tuple");
        return OrthancPluginErrorCode_Plugin;
      }

      OrthancPluginErrorCode returnCode = static_cast<OrthancPluginErrorCode>(PyLong_AsLong(pyReturnCode));

      if (returnCode == OrthancPluginErrorCode_Success)
      {
        if (Py_IsNone(pyTargetBuffer)) // no custom-data, return directly
        {
          customData = NULL;
          return returnCode;
        }

        char* pythonBuffer = NULL;
        Py_ssize_t pythonSize = 0;
        if (PyBytes_AsStringAndSize(pyTargetBuffer, &pythonBuffer, &pythonSize) == 1)
        {
          ORTHANC_PLUGINS_LOG_ERROR("Cannot access the byte buffer returned by the Python StorageCreate2 callback");
          return OrthancPluginErrorCode_Plugin;
        }
        else if (pythonSize > 0)
        {
          if (pythonSize > std::numeric_limits<uint32_t>::max())
          {
            ORTHANC_PLUGINS_LOG_ERROR("StorageCreate2 python callback: The returned custom data array size (" + boost::lexical_cast<std::string>(pythonSize) + " bytes) is too large");
            return OrthancPluginErrorCode_Plugin;
          }

          // The StorageCreate2 must allocate its customData buffer; it will be freed by Orthanc
          OrthancPluginErrorCode retAlloc = OrthancPluginCreateMemoryBuffer(OrthancPlugins::GetGlobalContext(),
                                                                            customData, static_cast<uint32_t>(pythonSize));

          if (retAlloc != OrthancPluginErrorCode_Success)
          {
            ORTHANC_PLUGINS_LOG_ERROR("StorageCreate2 python callback: Failed to allocate customData buffer: " + boost::lexical_cast<std::string>(retAlloc) + ")");
            return OrthancPluginErrorCode_Plugin;
          }

          memcpy(customData->data, reinterpret_cast<void*>(pythonBuffer), customData->size);
          return OrthancPluginErrorCode_Success;
        }
      }
      else
      {
        ORTHANC_PLUGINS_LOG_ERROR("The Python StorageCreate2 callback returned  " + boost::lexical_cast<std::string>(returnCode));
        return returnCode;
      }
    }
  }
  catch (OrthancPlugins::PluginException& e)
  {
    return e.GetErrorCode();
  }

  return OrthancPluginErrorCode_Plugin;
}


// "callable_protocol_args" : "uuid: str, content_type: ContentType, range_start: int, size: int, custom_data: bytes",
// "callable_protocol_return" : "Tuple" ErrorCode, target

static OrthancPluginErrorCode StorageReadRange2(OrthancPluginMemoryBuffer64* target,
                                                const char* uuid,
                                                OrthancPluginContentType type,
                                                uint64_t rangeStart,
                                                const void* customData,
                                                uint32_t customDataSize)
{
  try
  {
    if (readCallback2_ == NULL)
    {
      throw OrthancPlugins::PluginException(OrthancPluginErrorCode_InternalError);
    }
    
    PythonLock lock;

    PythonObject args(lock, PyTuple_New(5));

    PythonString str(lock, uuid);
    PyTuple_SetItem(args.GetPyObject(), 0, str.Release());
    PyTuple_SetItem(args.GetPyObject(), 1, PyLong_FromLong(type));
    PyTuple_SetItem(args.GetPyObject(), 2, PyLong_FromLong(rangeStart));
    PyTuple_SetItem(args.GetPyObject(), 3, PyLong_FromLong(target->size));
    PyTuple_SetItem(args.GetPyObject(), 4, PyBytes_FromStringAndSize(reinterpret_cast<const char*>(customData), customDataSize));
    
    PythonObject result(lock, PyObject_CallObject(readCallback2_, args.GetPyObject()));
    
    std::string traceback;
    if (lock.HasErrorOccurred(traceback))
    {
      ORTHANC_PLUGINS_LOG_ERROR("Error in the Python StorageReadRange2 callback, traceback:\n" + traceback);
      return OrthancPluginErrorCode_Plugin;
    }
    else if (!PyTuple_Check(result.GetPyObject()) || PyTuple_Size(result.GetPyObject()) != 2)
    {
      ORTHANC_PLUGINS_LOG_ERROR("The Python StorageReadRange2 callback has not returned a tuple as expected");
      return OrthancPluginErrorCode_Plugin;
    }
    else
    {
      PyObject* pyReturnCode = PyTuple_GET_ITEM(result.GetPyObject(), 0);
      PyObject* pyTargetBuffer = PyTuple_GET_ITEM(result.GetPyObject(), 1);

      if (!PyLong_Check(pyReturnCode))
      {
        ORTHANC_PLUGINS_LOG_ERROR("The Python StorageReadRange2 callback has not returned an int as the first element of the return tuple");
        return OrthancPluginErrorCode_Plugin;
      }
      else if (!PyBytes_Check(pyTargetBuffer))
      {
        ORTHANC_PLUGINS_LOG_ERROR("The Python StorageReadRange2 callback has not returned a byte array as the second element of the return tuple");
        return OrthancPluginErrorCode_Plugin;
      }

      OrthancPluginErrorCode returnCode = static_cast<OrthancPluginErrorCode>(PyLong_AsLong(pyReturnCode));

      if (returnCode == OrthancPluginErrorCode_Success)
      {
        char* pythonBuffer = NULL;
        Py_ssize_t pythonSize = 0;
        if (PyBytes_AsStringAndSize(pyTargetBuffer, &pythonBuffer, &pythonSize) == 1)
        {
          ORTHANC_PLUGINS_LOG_ERROR("Cannot access the byte buffer returned by the Python StorageReadRange2 callback");
          return OrthancPluginErrorCode_Plugin;
        }
        else
        {
          // The StorageReadRange2 uses a target that has already been allocated by orthanc
          if (static_cast<uint64_t>(pythonSize) == target->size)
          {
            memcpy(target->data, reinterpret_cast<void*>(pythonBuffer), target->size);
            return OrthancPluginErrorCode_Success;
          }
          else
          {
            ORTHANC_PLUGINS_LOG_ERROR("The returned bytes array size (" + boost::lexical_cast<std::string>(pythonSize) + " bytes) is not equal to the requested size ( " + boost::lexical_cast<std::string>(target->size) + " bytes) in the Python StorageReadRange2 callback");
            return OrthancPluginErrorCode_Plugin;
          }
        }
      }
      else
      {
        ORTHANC_PLUGINS_LOG_ERROR("The Python StorageReadRange2 callback returned  " + boost::lexical_cast<std::string>(returnCode));
        return returnCode;
      }
    }
  }
  catch (OrthancPlugins::PluginException& e)
  {
    return e.GetErrorCode();
  }
}

// "callable_protocol_args" : "uuid: str, content_type: ContentType, custom_data: bytes",
// "callable_protocol_return" : "ErrorCode"

static OrthancPluginErrorCode StorageRemove2(const char* uuid,
                                             OrthancPluginContentType type,
                                             const void* customData,
                                             uint32_t customDataSize)
{
  try
  {
    if (removeCallback2_ == NULL)
    {
      throw OrthancPlugins::PluginException(OrthancPluginErrorCode_InternalError);
    }
    
    PythonLock lock;

    PythonObject args(lock, PyTuple_New(3));

    PythonString str(lock, uuid);
    PyTuple_SetItem(args.GetPyObject(), 0, str.Release());
    PyTuple_SetItem(args.GetPyObject(), 1, PyLong_FromLong(type));
    PyTuple_SetItem(args.GetPyObject(), 2, PyBytes_FromStringAndSize(reinterpret_cast<const char*>(customData), customDataSize));

    return RunCallback(lock, removeCallback2_, args, "StorageRemove2");
  }
  catch (OrthancPlugins::PluginException& e)
  {
    return e.GetErrorCode();
  }
}


PyObject* RegisterStorageArea3(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")

  PyObject* a = NULL;
  PyObject* b = NULL;
  PyObject* c = NULL;

  if (!PyArg_ParseTuple(args, "OOO", &a, &b, &c) ||
      a == NULL ||
      b == NULL ||
      c == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Expected three callback functions to register a custom storage area");
    return NULL;
  }
  else if (createCallback2_ != NULL ||
           readCallback2_ != NULL ||
           removeCallback2_ != NULL)
  {
    PyErr_SetString(PyExc_RuntimeError, "Cannot register twice a custom storage area");
    return NULL;
  }
  else
  {
    ORTHANC_PLUGINS_LOG_INFO("Registering a custom storage area in Python");

    OrthancPluginRegisterStorageArea3(OrthancPlugins::GetGlobalContext(),
                                      StorageCreate2, StorageReadRange2, StorageRemove2);
    
    createCallback2_ = a;
    Py_XINCREF(createCallback2_);
    
    readCallback2_ = b;
    Py_XINCREF(readCallback2_);
    
    removeCallback2_ = c;
    Py_XINCREF(removeCallback2_);
    
    Py_INCREF(Py_None);
    return Py_None;
  }
}


void FinalizeStorageArea3()
{
  PythonLock lock;
  
  if (createCallback2_ != NULL)
  {
    Py_XDECREF(createCallback2_);
  }
  
  if (readCallback2_ != NULL)
  {
    Py_XDECREF(readCallback2_);
  }
  
  if (removeCallback2_ != NULL)
  {
    Py_XDECREF(removeCallback2_);
  }
}

#endif