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


#include "PythonFunction.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"
#include "PythonModule.h"


PythonObject* PythonFunction::CallUnchecked(PyObject* args)
{
  if (!IsValid())
  {
    ORTHANC_PLUGINS_THROW_EXCEPTION(BadSequenceOfCalls);
  }
  else
  {
    PyObject* obj = PyObject_CallObject(func_->GetPyObject(), args);
    return new PythonObject(lock_, obj);
  }
}


PythonFunction::PythonFunction(PythonLock& lock,
                               const PythonModule& module,
                               const std::string& name) :
  lock_(lock)
{
  if (module.IsValid() &&
      // This check is necessary in Python 2.7, otherwise garbage collector might crash
      PyObject_HasAttrString(module.GetPyObject(), name.c_str()))
  {
    func_.reset(module.GetObject().GetAttribute(name));
    
    if (func_.get() == NULL ||
        !func_->IsValid() ||
        !PyCallable_Check(func_->GetPyObject()))
    {
      func_.reset();  // Not such a function
      OrthancPlugins::LogWarning("Missing Python function: " + module.GetName() +
                                 "." + name + "()");
    }
  }
}


PythonObject* PythonFunction::Call()
{
  std::unique_ptr<PythonObject> result(CallUnchecked(NULL));

  std::string error;
  if (lock_.HasErrorOccurred(error))
  {
    OrthancPlugins::LogError("Python exception has occurred, traceback:\n" + error);
    ORTHANC_PLUGINS_THROW_EXCEPTION(Plugin);
  }
  else
  {
    return result.release();
  }
}


PythonObject* PythonFunction::Call(const PythonObject& args)
{
  std::unique_ptr<PythonObject> result(CallUnchecked(args.GetPyObject()));

  std::string error;
  if (lock_.HasErrorOccurred(error))
  {
    OrthancPlugins::LogError("Python exception has occurred, traceback:\n" + error);
    ORTHANC_PLUGINS_THROW_EXCEPTION(Plugin);
  }
  else
  {
    return result.release();
  }
}
