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


#pragma once

#include "PythonLock.h"

#include <json/value.h>

class PythonObject : public boost::noncopyable
{
private:
  PythonLock&  lock_;
  PyObject    *object_;
  bool         borrowed_;

  bool ToUtf8String(std::string& target,
                    PyObject* value);

  void ConvertToJson(Json::Value& target,
                     PyObject* source);
  
public:
  PythonObject(PythonLock& lock,
               PyObject *object,
               bool borrowed = false);

  ~PythonObject();

  bool IsValid() const
  {
    return object_ != NULL;
  }

  PyObject* GetPyObject() const;

  PythonObject* GetAttribute(const std::string& name);

  bool ToUtf8String(std::string& target)
  {
    return ToUtf8String(target, GetPyObject());
  }

  void Format(std::ostream& os);

  PyObject* Release();

  void ConvertToJson(Json::Value& target)
  {
    ConvertToJson(target, GetPyObject());
  }
};
