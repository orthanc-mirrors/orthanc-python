/**
 * Python plugin for Orthanc
 * Copyright (C) 2020-2024 Osimis S.A., Belgium
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


#pragma once

#include "../PythonHeaderWrapper.h"

void RegisterOrthancSdk(PyObject* module);
PyMethodDef* GetOrthancSdkFunctions();

PyTypeObject* GetOrthancPluginDicomInstanceType();
PyTypeObject* GetOrthancPluginDicomWebNodeType();
PyTypeObject* GetOrthancPluginFindAnswersType();
PyTypeObject* GetOrthancPluginFindMatcherType();
PyTypeObject* GetOrthancPluginFindQueryType();
PyTypeObject* GetOrthancPluginImageType();
PyTypeObject* GetOrthancPluginJobType();
PyTypeObject* GetOrthancPluginPeersType();
PyTypeObject* GetOrthancPluginRestOutputType();
PyTypeObject* GetOrthancPluginServerChunkedRequestReaderType();
PyTypeObject* GetOrthancPluginStorageAreaType();
PyTypeObject* GetOrthancPluginWorklistAnswersType();
PyTypeObject* GetOrthancPluginWorklistQueryType();

#include <orthanc/OrthancCPlugin.h>

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginDicomInstance* object_;
  bool borrowed_;
} sdk_OrthancPluginDicomInstance_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginDicomWebNode* object_;
  bool borrowed_;
} sdk_OrthancPluginDicomWebNode_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginFindAnswers* object_;
  bool borrowed_;
} sdk_OrthancPluginFindAnswers_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginFindMatcher* object_;
  bool borrowed_;
} sdk_OrthancPluginFindMatcher_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginFindQuery* object_;
  bool borrowed_;
} sdk_OrthancPluginFindQuery_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginImage* object_;
  bool borrowed_;
} sdk_OrthancPluginImage_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginJob* object_;
  bool borrowed_;
} sdk_OrthancPluginJob_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginPeers* object_;
  bool borrowed_;
} sdk_OrthancPluginPeers_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginRestOutput* object_;
  bool borrowed_;
} sdk_OrthancPluginRestOutput_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginServerChunkedRequestReader* object_;
  bool borrowed_;
} sdk_OrthancPluginServerChunkedRequestReader_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginStorageArea* object_;
  bool borrowed_;
} sdk_OrthancPluginStorageArea_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginWorklistAnswers* object_;
  bool borrowed_;
} sdk_OrthancPluginWorklistAnswers_Object;

typedef struct
{
  PyObject_HEAD

  /* Type-specific fields go here. */
  OrthancPluginWorklistQuery* object_;
  bool borrowed_;
} sdk_OrthancPluginWorklistQuery_Object;

