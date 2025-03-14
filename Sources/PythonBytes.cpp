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


#include "PythonBytes.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"


void PythonBytes::SanityCheck()
{
  if (!bytes_->IsValid())
  {
    ORTHANC_PLUGINS_LOG_ERROR("Cannot create Python bytes");
    ORTHANC_PLUGINS_THROW_EXCEPTION(InternalError);
  }
}


PythonBytes::PythonBytes(PythonLock& lock,
                         const void* data,
                         size_t size)
{
  if (data == NULL &&
      size != 0)
  {
    ORTHANC_PLUGINS_THROW_EXCEPTION(NullPointer);
  }
  else
  {
    PyObject* obj = PyBytes_FromStringAndSize(reinterpret_cast<const char*>(data), size);
    bytes_.reset(new PythonObject(lock, obj));
    SanityCheck();
  }
}
