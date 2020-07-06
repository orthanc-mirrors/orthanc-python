/**
 * Python plugin for Orthanc
 * Copyright (C) 2017-2020 Osimis S.A., Belgium
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


#include "PythonObject.h"


#include "PythonLock.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"


PythonObject::PythonObject(PythonLock& lock,
                           PyObject *object,
                           bool borrowed) :
  lock_(lock),
  object_(object),
  borrowed_(borrowed)
{
}


PythonObject::~PythonObject()
{
  if (!borrowed_ &&
      object_ != NULL)
  {
    Py_DECREF(object_);
  }
}


PyObject* PythonObject::GetPyObject() const
{
  if (object_ == NULL)
  {
    // "IsValid()" should have been called
    ORTHANC_PLUGINS_THROW_EXCEPTION(BadSequenceOfCalls);
  }
  else
  {
    return object_;
  }
}


PythonObject* PythonObject::GetAttribute(const std::string& name)
{
  return new PythonObject(lock_, PyObject_GetAttrString(GetPyObject(), name.c_str()));
}


bool PythonObject::ToUtf8String(std::string& target)
{
  PyObject* value = GetPyObject();  // Raises an exception if needed

  if (PyUnicode_Check(value))
  {
    PythonObject encoded(lock_, PyUnicode_AsEncodedString(value, "utf-8", "replace"));
    if (encoded.IsValid())
    {
      target = PyBytes_AS_STRING(encoded.GetPyObject());
      return true;
    }
    else
    {
      target.clear();
      return false;
    }
  }
#if PY_MAJOR_VERSION == 2
  else if (PyString_Check(value))
  {
    target = PyString_AS_STRING(value);
    return true;
  }
#endif
  else
  {
    target.clear();
    return false;
  }
}


void PythonObject::Format(std::ostream& os)
{
  std::string s;
  if (object_ == NULL)
  {
    os << "Can't format a NULL Python object" << std::endl;
  }
  else if (ToUtf8String(s))
  {
    os << s;
  }
  else
  {
    os << "Can't format this Python object" << std::endl;
  }
}


PyObject* PythonObject::Release()
{
  if (!borrowed_ &&
      object_ != NULL)
  {
    PyObject* value = object_;
    object_ = NULL;
    return value;
  }
  else
  {
    OrthancPlugins::LogError("Cannot release a NULL or borrowed reference");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}

