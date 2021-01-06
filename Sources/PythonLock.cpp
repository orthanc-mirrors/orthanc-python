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


#include "PythonLock.h"

#include "PythonFunction.h"
#include "PythonModule.h"
#include "PythonString.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"

#include <Compatibility.h>  // For std::unique_ptr<>

#include <boost/thread/mutex.hpp>

static boost::mutex   mutex_;
static PyThreadState* interpreterState_ = NULL;
static PythonLock::ModuleFunctionsInstaller moduleFunctions_ = NULL;
static PythonLock::ModuleClassesInstaller  moduleClasses_ = NULL;
static std::string  moduleName_;
static std::string  exceptionName_;
static bool verbose_ = false;


struct module_state 
{
  PyObject *exceptionClass_ = NULL;
};

#if PY_MAJOR_VERSION >= 3
#  define GETSTATE(module) ((struct module_state*) PyModule_GetState(module))
#else
#  define GETSTATE(module) (&_state)
static struct module_state _state;
#endif


PythonLock::PythonLock() :
  gstate_(PyGILState_Ensure())
{
  //OrthancPlugins::LogInfo("Python lock (GIL) acquired");
}


PythonLock::~PythonLock()
{
  PyGILState_Release(gstate_);
  //OrthancPlugins::LogInfo("Python lock (GIL) released");
}


void PythonLock::ExecuteCommand(const std::string& s)
{
  if (PyRun_SimpleString(s.c_str()) != 0)
  {
    OrthancPlugins::LogError("Error while executing a Python command");
    ORTHANC_PLUGINS_THROW_EXCEPTION(Plugin);
  }
}


void PythonLock::ExecuteFile(const std::string& path)
{
  OrthancPlugins::MemoryBuffer buffer;
  buffer.ReadFile(path);
    
  std::string script;
  buffer.ToString(script);

  ExecuteCommand(script);
}


bool PythonLock::HasErrorOccurred(std::string& target)
{
  if (PyErr_Occurred())
  {
    PyObject *exceptionType = NULL;
    PyObject *exceptionValue = NULL;
    PyObject *traceback = NULL;
    PyErr_Fetch(&exceptionType, &exceptionValue, &traceback);

    if (exceptionType == NULL)
    {
      return false;
    }

    PyErr_NormalizeException(&exceptionType, &exceptionValue, &traceback);

#if PY_MAJOR_VERSION >= 3
    if (traceback != NULL) 
    {
      PyException_SetTraceback(exceptionValue, traceback);
    }
#endif

    if (exceptionType != NULL)
    {
      PythonObject temp(*this, PyObject_Str(exceptionType));
      std::string s;
      if (temp.ToUtf8String(s))
      {
        target += s + "\n";
      }
    }

    if (exceptionValue != NULL)
    {
      PythonObject temp(*this, PyObject_Str(exceptionValue));
      std::string s;
      if (temp.ToUtf8String(s))
      {
        target += s + "\n";
      }
    }

    {
      PythonModule module(*this, "traceback");
      PythonFunction f(*this, module, "format_tb");

      if (traceback != NULL && 
          f.IsValid())
      {
        PythonObject args(*this, PyTuple_New(1));
        PyTuple_SetItem(args.GetPyObject(), 0, traceback);

        std::unique_ptr<PythonObject> value(f.CallUnchecked(args.GetPyObject()));

        if (value->IsValid())
        {
          Py_ssize_t len = PyList_Size(value->GetPyObject());
          for (Py_ssize_t i = 0; i < len; i++) 
          {
            PythonObject item(*this, PyList_GetItem(value->GetPyObject(), i), true /* borrowed */);
            std::string line;
            if (item.ToUtf8String(line))
            {
              target += "\n" + line;
            }
          }
        }
      }
    }


    /**
     * "This call takes away a reference to each object: you must own
     * a reference to each object before the call and after the call
     * you no longer own these references. (If you don't understand
     * this, don't use this function. I warned you.)"
     * => I don't use PyErr_Restore()
     **/
    
    //PyErr_Restore(exceptionType, exceptionValue, traceback);
    //PyErr_Clear();

    return true;
  }
  else
  {
    return false;
  }
}


static void RegisterException(PyObject* module,
                              const std::string& name)
{
  struct module_state *state = GETSTATE(module);

  state->exceptionClass_ = PyErr_NewException(const_cast<char*>(name.c_str()), NULL, NULL);
  if (state->exceptionClass_ == NULL) 
  {
    Py_DECREF(module);
    OrthancPlugins::LogError("Cannot create the Python exception class");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

#if 1
  Py_XINCREF(state->exceptionClass_);
  if (PyModule_AddObject(module, "Exception", state->exceptionClass_) < 0)
  {
    Py_XDECREF(state->exceptionClass_);
    Py_CLEAR(state->exceptionClass_);
    OrthancPlugins::LogError("Cannot create the Python exception class");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
#else
  // Install the exception class
  PyObject* dict = PyModule_GetDict(module);
  PyDict_SetItemString(dict, "Exception", state->exceptionClass);
#endif
}



#if PY_MAJOR_VERSION >= 3

static int sdk_traverse(PyObject *module, visitproc visit, void *arg) 
{
  Py_VISIT(GETSTATE(module)->exceptionClass_);
  return 0;
}

static int sdk_clear(PyObject *module) 
{
  Py_CLEAR(GETSTATE(module)->exceptionClass_);
  return 0;
}

static struct PyModuleDef moduledef = 
{
  PyModuleDef_HEAD_INIT,
  NULL, /* m_name => TO BE FILLED */
  NULL,
  sizeof(struct module_state),
  NULL, /* m_methods => TO BE FILLED */
  NULL,
  sdk_traverse,
  sdk_clear,
  NULL
};


PyMODINIT_FUNC InitializeModule()
{
  if (moduleFunctions_ == NULL ||
      moduleClasses_ == NULL ||
      moduleName_.empty() ||
      exceptionName_.empty())
  {
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  moduledef.m_name = moduleName_.c_str();
  moduledef.m_methods = moduleFunctions_();
  
  PyObject *module = PyModule_Create(&moduledef);
  if (module == NULL)
  {
    OrthancPlugins::LogError("Cannot create a Python module");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  RegisterException(module, moduleName_ + "." + exceptionName_);
  moduleClasses_(module);

  return module;
}

#else

void InitializeModule()
{
  if (moduleFunctions_ == NULL ||
      moduleClasses_ == NULL ||
      moduleName_.empty() ||
      exceptionName_.empty())
  {
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  PyObject *module = Py_InitModule(moduleName_.c_str(), moduleFunctions_());
  if (module == NULL)
  {
    OrthancPlugins::LogError("Cannot create a Python module");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  RegisterException(module, moduleName_ + "." + exceptionName_);
  moduleClasses_(module);
}

#endif



void PythonLock::GlobalInitialize(const std::string& moduleName,
                                  const std::string& exceptionName,
                                  ModuleFunctionsInstaller moduleFunctions,
                                  ModuleClassesInstaller moduleClasses,
                                  bool verbose)
{
  boost::mutex::scoped_lock lock(mutex_);
  
  if (interpreterState_ != NULL)
  {
    OrthancPlugins::LogError("Cannot initialize twice the Python interpreter");
    ORTHANC_PLUGINS_THROW_EXCEPTION(BadSequenceOfCalls);
  }

  if (moduleClasses == NULL ||
      moduleFunctions == NULL)
  {
    ORTHANC_PLUGINS_THROW_EXCEPTION(NullPointer);
  }

  if (moduleName.empty() ||
      exceptionName.empty())
  {
    ORTHANC_PLUGINS_THROW_EXCEPTION(ParameterOutOfRange);
  }

  if (exceptionName.find('.') != std::string::npos)
  {
    OrthancPlugins::LogError("The name of the exception cannot contain \".\", found: " +
                             exceptionName);
    ORTHANC_PLUGINS_THROW_EXCEPTION(ParameterOutOfRange);
  }

  moduleClasses_ = moduleClasses;
  moduleFunctions_ = moduleFunctions;
  moduleName_ = moduleName;
  exceptionName_ = exceptionName;
  
  std::string executable;

  {
    OrthancPlugins::OrthancString str;
    str.Assign(OrthancPluginGetOrthancPath(OrthancPlugins::GetGlobalContext())); 
    str.ToString(executable);
  }
  
  OrthancPlugins::LogWarning("Program name: " + executable);

#if PY_MAJOR_VERSION == 2
  Py_SetProgramName(&executable[0]);  /* optional but recommended */
#else
  std::wstring wide(executable.begin(), executable.end());
  Py_SetProgramName(&wide[0]);  /* optional but recommended */
  Py_UnbufferedStdioFlag = 1;  // Write immediately to stdout after "sys.stdout.flush()" (only in Python 3.x)
#endif

  Py_InspectFlag = 1;   // Don't exit the Orthanc process on Python error

  verbose_ = verbose;
  if (verbose)
  {
    Py_VerboseFlag = 1;
  }

#if PY_MAJOR_VERSION >= 3
  PyImport_AppendInittab(moduleName_.c_str(), InitializeModule);
#endif

#if PY_VERSION_HEX < 0x03020000   /* 3.2.0 */
  /**
   * "Changed in version 3.2: This function cannot be called before
   * Py_Initialize() anymore."
   **/
  if (!PyEval_ThreadsInitialized())
  {
    PyEval_InitThreads();
  }
#endif

  Py_InitializeEx(0 /* Python is embedded, skip signal handlers */);

#if 0
#if PY_MAJOR_VERSION == 2
  std::cout << Py_GetPath() << std::endl;  
  std::cout << Py_GetProgramName() << std::endl;
  std::cout << Py_GetProgramFullPath() << std::endl;
#else
  std::wcout << Py_GetPath() << std::endl;
  std::wcout << Py_GetProgramName() << std::endl;
  std::wcout << Py_GetProgramFullPath() << std::endl;
#endif
#endif

#if (PY_VERSION_HEX >= 0x03020000 /* 3.2.0 */ &&        \
     PY_VERSION_HEX < 0x03070000 /* 3.7.0 */)
  /**
   * Changed in version 3.7: This function is now called by
   * Py_Initialize(), so you don't have to call it yourself anymore.
   **/
  if (!PyEval_ThreadsInitialized())
  {
    PyEval_InitThreads();
  }
#endif

  
#if PY_MAJOR_VERSION == 2
  InitializeModule();
#endif

  // https://fr.slideshare.net/YiLungTsai/embed-python => slide 26
  interpreterState_ = PyEval_SaveThread();
}


void PythonLock::AddSysPath(const std::string& path)
{
  /**
   * "It is recommended that applications embedding the Python
   * interpreter for purposes other than executing a single script
   * pass 0 as updatepath, and update sys.path themselves if
   * desired. See CVE-2008-5983."
   * => Set "sys.path.append()" to the directory of the configuration file by default
   **/

  PythonLock lock;
  
  /**
   * Initialization of "sys.path.append()" must be done before loading
   * any module.
   **/

  PyObject *sysPath = PySys_GetObject(const_cast<char*>("path"));
  if (sysPath == NULL)
  {
    OrthancPlugins::LogError("Cannot find sys.path");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }

  PythonString pyPath(lock, path);
  int result = PyList_Insert(sysPath, 0, pyPath.Release());
  
  if (result != 0)
  {
    OrthancPlugins::LogError("Cannot run sys.path.append()");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


void PythonLock::GlobalFinalize()
{
  boost::mutex::scoped_lock lock(mutex_);
  
  if (interpreterState_ != NULL)
  {
    PyEval_RestoreThread(interpreterState_);
    interpreterState_ = NULL;
  }
  
  Py_Finalize();
}


void PythonLock::RaiseException(PyObject* module,
                                OrthancPluginErrorCode code)
{
  if (code != OrthancPluginErrorCode_Success)
  {
    const char* message = OrthancPluginGetErrorDescription(OrthancPlugins::GetGlobalContext(), code);
    
    struct module_state *state = GETSTATE(module);
    if (state->exceptionClass_ == NULL)
    {
      OrthancPlugins::LogError("No Python exception has been registered");
    }
    else
    {
      PyErr_SetString(state->exceptionClass_, message);
    }
  }
}


void PythonLock::LogCall(const std::string& message)
{
  /**
   * For purity, this function should lock the global "mutex_", but
   * "verbose_" cannot change after the initial call to
   * "GlobalInitialize()".
   **/
  
  if (verbose_)
  {
    OrthancPlugins::LogInfo(message);
  }
}
