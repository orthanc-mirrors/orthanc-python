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

#include "PythonLock.h"

class PythonObject : public boost::noncopyable
{
private:
  PythonLock&  lock_;
  PyObject    *object_;
  bool         borrowed_;

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

  bool ToUtf8String(std::string& target);

  void Format(std::ostream& os);

  PyObject* Release();
};
