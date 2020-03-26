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


#pragma once

#include "../Resources/Orthanc/Core/Compatibility.h"
#include "PythonObject.h"

#include <memory>

class PythonModule : public boost::noncopyable
{
private:
  PythonLock&                    lock_;
  std::string                    name_;
  std::unique_ptr<PythonObject>  module_;

public:
  PythonModule(PythonLock& lock,
               const std::string& utf8Name);

  const std::string& GetName() const
  {
    return name_;
  }

  bool IsValid() const;

  PythonObject& GetObject() const;

  PyObject* GetPyObject() const;
};
