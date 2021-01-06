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


#pragma once

#include "PythonObject.h"

#include <Compatibility.h>  // For std::unique_ptr

// A Python string is always valid, or an exception was thrown on its creation
class PythonString : public boost::noncopyable
{
private:
  std::unique_ptr<PythonObject>  string_;

  void SanityCheck();

public:
  PythonString(PythonLock& lock,
               const std::string& utf8);

  PythonString(PythonLock& lock,
               const char* utf8);

  PyObject* GetPyObject() const
  {
    return string_->GetPyObject();
  }

  PyObject* Release()
  {
    return string_->Release();
  }
};
