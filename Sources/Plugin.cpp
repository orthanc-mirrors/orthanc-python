/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2023 Osimis S.A., Belgium
 * Copyright (C) 2024-2024 Orthanc Team SRL, Belgium
 * Copyright (C) 2021-2024 Sebastien Jodogne, ICTEAM UCLouvain, Belgium
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


// http://edcjones.tripod.com/refcount.html
// https://docs.python.org/3/extending/extending.html

// https://www.codevate.com/blog/7-concurrency-with-embedded-python-in-a-multi-threaded-c-application
// https://fr.slideshare.net/YiLungTsai/embed-python


#include "DicomScpCallbacks.h"
#include "IncomingHttpRequestFilter.h"
#include "OnChangeCallback.h"
#include "OnStoredInstanceCallback.h"
#include "IncomingInstanceFilter.h"
#include "ReceivedInstanceCallback.h"
#include "StorageArea.h"
#include "StorageCommitmentScpCallback.h"

#include "RestCallbacks.h"
#include "PythonModule.h"

#include "Autogenerated/sdk.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

// The "dl_iterate_phdr()" function (to walk through shared libraries)
// is not available on Microsoft Windows and Apple OS X
#if defined(_WIN32)
#  define HAS_DL_ITERATE  0
#elif defined(__APPLE__) && defined(__MACH__)
#  define HAS_DL_ITERATE  0
#else
#  define HAS_DL_ITERATE  1
#endif


#include "PythonString.h"

PyObject* LookupDictionary(PyObject* module, PyObject* args)
{
  const char* name = NULL;
  
  if (!PyArg_ParseTuple(args, "s", &name))
  {
    PyErr_SetString(PyExc_TypeError, "Please provide a string containing the name of the DICOM tag of interest");
    return NULL;
  }
  else
  {
    OrthancPluginDictionaryEntry entry;
    
    OrthancPluginErrorCode code = OrthancPluginLookupDictionary(OrthancPlugins::GetGlobalContext(), &entry, name);
    if (code == OrthancPluginErrorCode_Success)
    {
      /**
       * "PyGILState_Ensure()" can be invoked several times from the
       * same thread, so no problem in creating a PythonLock even if
       * the GIL is already locked.
       **/
      PythonLock lock;
      
      PythonObject kw(lock, PyDict_New());

      {
        PythonObject tmp(lock, PyLong_FromUnsignedLong(entry.group));
        PyDict_SetItemString(kw.GetPyObject(), "Group", tmp.GetPyObject());
      }

      {
        PythonObject tmp(lock, PyLong_FromUnsignedLong(entry.element));
        PyDict_SetItemString(kw.GetPyObject(), "Element", tmp.GetPyObject());
      }

      {
        PythonObject tmp(lock, PyLong_FromUnsignedLong(entry.vr));
        PyDict_SetItemString(kw.GetPyObject(), "ValueRepresentation", tmp.GetPyObject());
      }

      {
        PythonObject tmp(lock, PyLong_FromUnsignedLong(entry.minMultiplicity));
        PyDict_SetItemString(kw.GetPyObject(), "MinMultiplicity", tmp.GetPyObject());
      }

      {
        PythonObject tmp(lock, PyLong_FromUnsignedLong(entry.maxMultiplicity));
        PyDict_SetItemString(kw.GetPyObject(), "MaxMultiplicity", tmp.GetPyObject());
      }
      
      return kw.Release();
    }
    else
    {
      std::string message = "Unknown DICOM tag: " + std::string(name);
      PyErr_SetString(PyExc_TypeError, message.c_str());
      return NULL;
    }
  }
}


PyObject* CreateDicom(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")
  const char* json = NULL;
  PyObject* pixelData = NULL;
  long int flags = 0;
  
  if (!PyArg_ParseTuple(args, "sOl", &json, &pixelData, &flags))
  {
    PyErr_SetString(PyExc_TypeError, "Please provide a JSON string, an orthanc.Image object, and a set of orthanc.CreateDicomFlags");
    return NULL;
  }
  else
  {
    OrthancPluginImage* image = NULL;
    
    if (pixelData == Py_None)
    {
      // No pixel data
    }
    else if (Py_TYPE(pixelData) == GetOrthancPluginImageType())
    {
      image = reinterpret_cast<sdk_OrthancPluginImage_Object*>(pixelData)->object_;
    }
    else
    {
      PyErr_SetString(PyExc_TypeError, "Second parameter is not a valid orthanc.Image object");
      return NULL;
    }

    OrthancPlugins::MemoryBuffer buffer;
    OrthancPluginErrorCode code = OrthancPluginCreateDicom(OrthancPlugins::GetGlobalContext(), *buffer, json, image,
                                                           static_cast<OrthancPluginCreateDicomFlags>(flags));
  
    if (code == OrthancPluginErrorCode_Success)
    {
      return PyBytes_FromStringAndSize(buffer.GetData(), buffer.GetSize());
    }
    else
    {
      PyErr_SetString(PyExc_ValueError, "Cannot create the DICOM instance");
      return NULL;  
    }
  }
}


PyObject* GetInstanceData(sdk_OrthancPluginDicomInstance_Object* self, PyObject *args)
{
  // The GIL is locked at this point (no need to create "PythonLock")

  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }
  else
  {
    OrthancPluginDicomInstance* instance = reinterpret_cast<sdk_OrthancPluginDicomInstance_Object*>(self)->object_;

    const void* data = OrthancPluginGetInstanceData(OrthancPlugins::GetGlobalContext(), instance);
    size_t size = OrthancPluginGetInstanceSize(OrthancPlugins::GetGlobalContext(), instance);

    if (data == NULL &&
        size != 0)
    {
      PyErr_SetString(PyExc_ValueError, "Accessing an invalid orthanc.DicomInstance object");
      return NULL;  
    }
    else
    {
      return PyBytes_FromStringAndSize(reinterpret_cast<const char*>(data), size);
    }
  }
}


/**
 * Contrarily to "OrthancPluginGetImageBuffer()" that provides a
 * read-write pointer, the method "orthanc.Image.GetImageBuffer()"
 * returns a copy of the image buffer. Use "CreateImageFromBuffer()"
 * to create an image from a Python buffer.
 **/
PyObject* GetImageBuffer(sdk_OrthancPluginImage_Object* self, PyObject *args)
{
  // The GIL is locked at this point (no need to create "PythonLock")
  
  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }
  else
  {
    OrthancPluginImage* image = reinterpret_cast<sdk_OrthancPluginImage_Object*>(self)->object_;

    const void* buffer = OrthancPluginGetImageBuffer(OrthancPlugins::GetGlobalContext(), image);
    size_t size = (OrthancPluginGetImagePitch(OrthancPlugins::GetGlobalContext(), image) *
                   OrthancPluginGetImageHeight(OrthancPlugins::GetGlobalContext(), image));

    if (buffer == NULL &&
        size != 0)
    {
      PyErr_SetString(PyExc_ValueError, "Accessing an invalid orthanc.Image object");
      return NULL;  
    }
    else
    {
      return PyBytes_FromStringAndSize(reinterpret_cast<const char*>(buffer), size);
    }
  }
}


/**
 * This function is the Python alternative for function
 * "OrthancPluginCreateImageAccessor()". Indeed, it is not possible to
 * share a memory buffer between Orthanc and Python, so we have to
 * create a copy of the image.
 **/
PyObject* CreateImageFromBuffer(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")

  unsigned long format, width, height, sourcePitch;
  Py_buffer buffer;

  if (!PyArg_ParseTuple(args, "kkkks*", &format, &width, &height, &sourcePitch, &buffer))
  {
    PyErr_SetString(PyExc_TypeError, "5 arguments are needed: image.PixelFormat, width, height, pitch and memory buffer");
    return NULL;
  }
  else if (static_cast<Py_ssize_t>(sourcePitch * height) != buffer.len)
  {
    PyBuffer_Release(&buffer);

    PyErr_SetString(PyExc_TypeError, "The size of the memory buffer must match the product of height by pitch");
    return NULL;
  }
  else
  {
    OrthancPluginImage* image = OrthancPluginCreateImage(
      OrthancPlugins::GetGlobalContext(), static_cast<OrthancPluginPixelFormat>(format), width, height);

    if (image == NULL)
    {
      PyBuffer_Release(&buffer);

      PyErr_SetString(PyExc_ValueError, "Cannot create the image");
      return NULL;  
    }
    else
    {
      // Copy the image line by line
      unsigned long targetPitch = OrthancPluginGetImagePitch(OrthancPlugins::GetGlobalContext(), image);

      const uint8_t* sourcePixels = reinterpret_cast<const uint8_t*>(buffer.buf);
      uint8_t* targetPixels = reinterpret_cast<uint8_t*>(OrthancPluginGetImageBuffer(OrthancPlugins::GetGlobalContext(), image));

      unsigned long rowSize = std::min(sourcePitch, targetPitch);
      
      for (unsigned int y = 0; y < height; y++)
      {
        memcpy(targetPixels, sourcePixels, rowSize);
        targetPixels += targetPitch;
        sourcePixels += sourcePitch;
      }
             
      PyBuffer_Release(&buffer);

      {
        PyObject *argList = Py_BuildValue("Lb", image, false /* not borrowed */);
        PyObject *python = PyObject_CallObject((PyObject *) GetOrthancPluginImageType(), argList);
        Py_DECREF(argList);
        return python;
      }
    }
  }
}



static bool pythonEnabled_ = false;
static std::string userScriptName_;
static std::vector<PyMethodDef>  globalFunctions_;
static boost::thread displayMemoryUsageThread_;
static bool displayMemoryUsageStopping_ = false;


static void InstallClasses(PyObject* module)
{
  RegisterOrthancSdk(module);
}


static void SetupGlobalFunctions()
{
  if (!globalFunctions_.empty())
  {
    return;
//    ORTHANC_PLUGINS_THROW_EXCEPTION(BadSequenceOfCalls);
  }

  /**
   * Add all the manual global functions
   **/

  std::list<PyMethodDef> functions;

  {
    PyMethodDef f = { "RegisterRestCallback", RegisterRestCallback, METH_VARARGS, "" };
    functions.push_back(f);
  }

  {
    PyMethodDef f = { "RegisterOnChangeCallback", RegisterOnChangeCallback, METH_VARARGS, "" };
    functions.push_back(f);
  }

  {
    PyMethodDef f = { "RegisterOnStoredInstanceCallback", RegisterOnStoredInstanceCallback,
                      METH_VARARGS, "" };
    functions.push_back(f);
  }

  
  /**
   * New in release 3.0
   **/
  
  {
    PyMethodDef f = { "RegisterIncomingHttpRequestFilter", RegisterIncomingHttpRequestFilter, METH_VARARGS, "" };
    functions.push_back(f);
  }


  /**
   * New in release 3.2
   **/
  
  {
    PyMethodDef f = { "LookupDictionary", LookupDictionary, METH_VARARGS, "" };
    functions.push_back(f);
  }
  
  {
    PyMethodDef f = { "CreateDicom", CreateDicom, METH_VARARGS, "" };
    functions.push_back(f);
  }
  
  {
    PyMethodDef f = { "CreateImageFromBuffer", CreateImageFromBuffer, METH_VARARGS, "" };
    functions.push_back(f);
  }
  
  {
    PyMethodDef f = { "RegisterFindCallback", RegisterFindCallback, METH_VARARGS, "" };
    functions.push_back(f);
  }
  
  {
    PyMethodDef f = { "RegisterMoveCallback", RegisterMoveCallback, METH_VARARGS, "" };
    functions.push_back(f);
  }

  {
    PyMethodDef f = { "RegisterMoveCallback2", RegisterMoveCallback2, METH_VARARGS, "" };
    functions.push_back(f);
  }

  {
    PyMethodDef f = { "RegisterWorklistCallback", RegisterWorklistCallback, METH_VARARGS, "" };
    functions.push_back(f);
  }
  
  
  /**
   * New in release 3.3
   **/
  
  {
    PyMethodDef f = { "RegisterStorageArea", RegisterStorageArea, METH_VARARGS, "" };
    functions.push_back(f);
  }


  /**
   * New in release 3.5
   **/
  
  {
    PyMethodDef f = { "RegisterIncomingCStoreInstanceFilter", RegisterIncomingCStoreInstanceFilter, METH_VARARGS, "" };
    functions.push_back(f);
  }

  {
    PyMethodDef f = { "RegisterReceivedInstanceCallback", RegisterReceivedInstanceCallback, METH_VARARGS, "" };
    functions.push_back(f);
  }

  /**
   * New in release 4.1
   **/

  {
    PyMethodDef f = { "RegisterStorageCommitmentScpCallback", RegisterStorageCommitmentScpCallback, METH_VARARGS, "" };
    functions.push_back(f);
  }

  /**
   * Append all the global functions that were automatically generated
   **/
  
  const PyMethodDef* sdk = GetOrthancSdkFunctions();

  for (size_t i = 0; sdk[i].ml_name != NULL; i++)
  {
    functions.push_back(sdk[i]);
  }

  /**
   * Flatten the list of functions into the vector
   **/

  globalFunctions_.resize(functions.size());
  std::copy(functions.begin(), functions.end(), globalFunctions_.begin());

  PyMethodDef sentinel = { NULL };
  globalFunctions_.push_back(sentinel);
}

  
static PyMethodDef* GetGlobalFunctions()
{
  if (globalFunctions_.empty())
  {
    // "SetupGlobalFunctions()" should have been called
    ORTHANC_PLUGINS_THROW_EXCEPTION(BadSequenceOfCalls);
  }
  else
  {
    return &globalFunctions_[0];
  }
}



#if HAS_DL_ITERATE == 1

#include <dlfcn.h>
#include <link.h>  // For dl_phdr_info

static int ForceImportCallback(struct dl_phdr_info *info, size_t size, void *data)
{ 
  /**
   * The following line solves the error: "ImportError:
   * /usr/lib/python2.7/dist-packages/PIL/_imaging.x86_64-linux-gnu.so:
   * undefined symbol: PyExc_SystemError"
   * https://stackoverflow.com/a/48517485/881731
   * 
   * dlopen("/usr/lib/x86_64-linux-gnu/libpython2.7.so", RTLD_NOW | RTLD_LAZY | RTLD_GLOBAL);
   * 
   * Another fix consists in using LD_PRELOAD as follows:
   * LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libpython2.7.so ~/Subversion/orthanc/i/Orthanc tutu.json
   **/
    
  std::string module(info->dlpi_name);

  if (module.find("python") != std::string::npos)
  {
    ORTHANC_PLUGINS_LOG_WARNING("Force global loading of Python shared library: " + module);
    dlopen(module.c_str(), RTLD_NOW | RTLD_LAZY | RTLD_GLOBAL);
  }
  
  return 0;
}

#endif


static void DisplayMemoryUsageThread()
{
  {
    PythonLock lock;
    lock.ExecuteCommand("import tracemalloc");
    lock.ExecuteCommand("tracemalloc.start()");
  }

  while (!displayMemoryUsageStopping_)
  {
    {
      PythonLock lock;
      lock.ExecuteCommand("print('Python memory usage: %0.03fMB' % "
                          "(tracemalloc.get_traced_memory() [0] / (1024.0 * 1024.0)))");
    }

    boost::this_thread::sleep(boost::posix_time::seconds(1));
  }
}


extern "C"
{
  ORTHANC_PLUGINS_API int32_t OrthancPluginInitialize(OrthancPluginContext* c)
  {
    OrthancPlugins::SetGlobalContext(c);
    ORTHANC_PLUGINS_LOG_WARNING("Python plugin is initializing");
    

    /* Check the version of the Orthanc core */
    if (OrthancPluginCheckVersion(c) == 0)
    {
      char info[1024];
      sprintf(info, "Your version of Orthanc (%s) must be above %d.%d.%d to run this plugin",
              c->orthancVersion,
              ORTHANC_PLUGINS_MINIMAL_MAJOR_NUMBER,
              ORTHANC_PLUGINS_MINIMAL_MINOR_NUMBER,
              ORTHANC_PLUGINS_MINIMAL_REVISION_NUMBER);
      OrthancPluginLogError(c, info);
      return -1;
    }
    
    OrthancPlugins::SetDescription(PLUGIN_NAME, "Run Python scripts as Orthanc plugins");
    
    try
    {
      /**
       * Detection of the user script
       **/

      OrthancPlugins::OrthancConfiguration globalConfig;

      OrthancPlugins::OrthancConfiguration pythonConfig;
      globalConfig.GetSection(pythonConfig, "Python");

      std::string script;
      if (!globalConfig.LookupStringValue(script, "PythonScript") &&
          !pythonConfig.LookupStringValue(script, "Path"))
      {
        pythonEnabled_ = false;
      
        ORTHANC_PLUGINS_LOG_WARNING("Options \"PythonScript\" and \"Python.Path\" are not provided: "
                                    "Python scripting is disabled");
      }
      else
      {
        pythonEnabled_ = true;
      
        /**
         * Installation of the user script
         **/

        const boost::filesystem::path path(script);
        if (!boost::iequals(path.extension().string(), ".py"))
        {
          ORTHANC_PLUGINS_LOG_ERROR("Python script must have the \".py\" file extension: " +
                                    path.string());
          return -1;
        }

        if (!boost::filesystem::is_regular_file(path))
        {
          ORTHANC_PLUGINS_LOG_ERROR("Inexistent directory for the Python script: " +
                                    path.string());
          return -1;
        }

        boost::filesystem::path userScriptDirectory = boost::filesystem::absolute(path).parent_path();

        {
          boost::filesystem::path module = path.filename().replace_extension("");
          userScriptName_ = module.string();
        }

        ORTHANC_PLUGINS_LOG_WARNING("Using Python script \"" + userScriptName_ +
                                    ".py\" from directory: " + userScriptDirectory.string());
    
    
        /**
         * Initialization of Python
         **/

        const bool isVerbose = (globalConfig.GetBooleanValue("PythonVerbose", false) ||
                                pythonConfig.GetBooleanValue("Verbose", false));

#if HAS_DL_ITERATE == 1
        dl_iterate_phdr(ForceImportCallback, NULL);
#endif

        SetupGlobalFunctions();
        PythonLock::GlobalInitialize("orthanc", "OrthancException", GetGlobalFunctions, InstallClasses, isVerbose);
        PythonLock::AddSysPath(userScriptDirectory.string());

        if (pythonConfig.GetBooleanValue("DisplayMemoryUsage", false))
        {
          displayMemoryUsageThread_ = boost::thread(DisplayMemoryUsageThread);
        }

      
        /**
         * Force loading the declarations in the user script
         **/

        PythonLock lock;

        {
          PythonModule module(lock, userScriptName_);
        }
      
        std::string traceback;
        if (lock.HasErrorOccurred(traceback))
        {
          ORTHANC_PLUGINS_LOG_ERROR("Error during the installation of the Python script, "
                                    "traceback:\n" + traceback);
          return -1;
        }
      }
    }
    catch (ORTHANC_PLUGINS_EXCEPTION_CLASS& e)
    {
      ORTHANC_PLUGINS_LOG_ERROR("Exception while starting the Python plugin: " +
                                std::string(e.What(c)));
      return -1;
    }
    
    return 0;
  }


  ORTHANC_PLUGINS_API void OrthancPluginFinalize()
  {
    ORTHANC_PLUGINS_LOG_WARNING("Python plugin is finalizing");

    if (pythonEnabled_)
    {
      FinalizeOnChangeCallback();
      FinalizeRestCallbacks();
      FinalizeOnStoredInstanceCallback();
      FinalizeIncomingHttpRequestFilter();
      FinalizeDicomScpCallbacks();

      displayMemoryUsageStopping_ = true;

      if (displayMemoryUsageThread_.joinable())
      {
        displayMemoryUsageThread_.join();
      }
      
      PythonLock::GlobalFinalize();
    }

    OrthancPlugins::ResetGlobalContext();
  }


  ORTHANC_PLUGINS_API const char* OrthancPluginGetName()
  {
    return PLUGIN_NAME;
  }


  ORTHANC_PLUGINS_API const char* OrthancPluginGetVersion()
  {
    return PLUGIN_VERSION;
  }
}
