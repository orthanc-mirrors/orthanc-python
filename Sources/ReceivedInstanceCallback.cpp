/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2021 Osimis S.A., Belgium
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


#include "ReceivedInstanceCallback.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"
#include "ICallbackRegistration.h"
#include "PythonString.h"

#include <Compatibility.h>  // For std::unique_ptr<>

static PyObject*   receivedInstanceCallback_ = NULL;


static OrthancPluginReceivedInstanceCallbackResult ReceivedInstanceCallback(
    const void* receivedDicomBuffer,
    uint64_t receivedDicomBufferSize,
    void** modifiedDicomBuffer,
    uint64_t* modifiedDicomBufferSize)
{
  try
  {
    PythonLock lock;

    PythonObject args(lock, PyTuple_New(1));

    PyTuple_SetItem(args.GetPyObject(), 0, PyBytes_FromStringAndSize(reinterpret_cast<const char*>(receivedDicomBuffer), receivedDicomBufferSize));

    PythonObject result(lock, PyObject_CallObject(receivedInstanceCallback_, args.GetPyObject()));

    std::string traceback;
    if (lock.HasErrorOccurred(traceback))
    {
      OrthancPlugins::LogError("Error in the Python received instance callback, traceback:\n" + traceback);
      return OrthancPluginReceivedInstanceCallbackResult_KeepAsIs;
    }
    else if (!PyTuple_Check(result.GetPyObject()) || PyTuple_Size(result.GetPyObject()) != 2)
    {
      OrthancPlugins::LogError("The Python received instance callback has not returned a tuple as expected");
      return OrthancPluginReceivedInstanceCallbackResult_KeepAsIs;
    }
    else
    {
      PyObject* returnCode = PyTuple_GET_ITEM(result.GetPyObject(), 0);
      PyObject* modifiedDicom = PyTuple_GET_ITEM(result.GetPyObject(), 1);

      if (!PyLong_Check(returnCode))
      {
        OrthancPlugins::LogError("The Python received instance callback has not returned an int as the first element of the return tuple");
        return OrthancPluginReceivedInstanceCallbackResult_KeepAsIs;
      }

      OrthancPluginReceivedInstanceCallbackResult resultCode = static_cast<OrthancPluginReceivedInstanceCallbackResult>(PyLong_AsLong(returnCode));

      if (resultCode == OrthancPluginReceivedInstanceCallbackResult_KeepAsIs ||
        resultCode == OrthancPluginReceivedInstanceCallbackResult_Discard)
      {
        return resultCode;
      }

      char* pythonBuffer = NULL;
      Py_ssize_t pythonSize = 0;
      if (PyBytes_AsStringAndSize(modifiedDicom, &pythonBuffer, &pythonSize) == 1)
      {
        OrthancPlugins::LogError("Cannot access the byte buffer returned by the Python received instance callback");
        return OrthancPluginReceivedInstanceCallbackResult_KeepAsIs;
      }
      else
      {
        if (pythonSize == 0)
        {
          *modifiedDicomBuffer = NULL;
          *modifiedDicomBufferSize = 0;
          return OrthancPluginReceivedInstanceCallbackResult_KeepAsIs;
        }
        else
        {
          *modifiedDicomBuffer = malloc(pythonSize);
          *modifiedDicomBufferSize = pythonSize;
          if (*modifiedDicomBuffer == NULL)
          {
            OrthancPlugins::LogError("Cannot allocate memory in the Python received instance callback");
            return OrthancPluginReceivedInstanceCallbackResult_KeepAsIs;
          }

          memcpy(*modifiedDicomBuffer, pythonBuffer, pythonSize);
          return OrthancPluginReceivedInstanceCallbackResult_Modified;
        }
      }
    }
  }
  catch (OrthancPlugins::PluginException& e)
  {
    OrthancPlugins::LogError("Error in the Python received instance callback: " + std::string(e.What(OrthancPlugins::GetGlobalContext())));
  }

  return OrthancPluginReceivedInstanceCallbackResult_KeepAsIs;
}

   
PyObject* RegisterReceivedInstanceCallback(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")

  class Registration : public ICallbackRegistration
  {
  public:
    virtual void Register() ORTHANC_OVERRIDE
    {
      OrthancPluginRegisterReceivedInstanceCallback(
        OrthancPlugins::GetGlobalContext(), ReceivedInstanceCallback);
    }
  };

  Registration registration;
  return ICallbackRegistration::Apply(
    registration, args, receivedInstanceCallback_, "Python received instance callback");
}


void FinalizeReceivedInstanceCallback()
{
  ICallbackRegistration::Unregister(receivedInstanceCallback_);
}
