/**
 * SPDX-FileCopyrightText: 2020-2023 Osimis S.A., 2024-2024 Orthanc Team SRL, 2021-2024 Sebastien Jodogne, ICTEAM UCLouvain
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

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


// WARNING: Auto-generated file. Do not modify it by hand.


#include "sdk.h"

#include "../PythonLock.h"
#include "../PythonThreadsAllower.h"

#include "../../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"

#include "./sdk_OrthancPluginChangeType.impl.h"
#include "./sdk_OrthancPluginCompressionType.impl.h"
#include "./sdk_OrthancPluginConstraintType.impl.h"
#include "./sdk_OrthancPluginContentType.impl.h"
#include "./sdk_OrthancPluginCreateDicomFlags.impl.h"
#include "./sdk_OrthancPluginDicomToJsonFlags.impl.h"
#include "./sdk_OrthancPluginDicomToJsonFormat.impl.h"
#include "./sdk_OrthancPluginDicomWebBinaryMode.impl.h"
#include "./sdk_OrthancPluginErrorCode.impl.h"
#include "./sdk_OrthancPluginHttpMethod.impl.h"
#include "./sdk_OrthancPluginIdentifierConstraint.impl.h"
#include "./sdk_OrthancPluginImageFormat.impl.h"
#include "./sdk_OrthancPluginInstanceOrigin.impl.h"
#include "./sdk_OrthancPluginJobStepStatus.impl.h"
#include "./sdk_OrthancPluginJobStopReason.impl.h"
#include "./sdk_OrthancPluginLoadDicomInstanceMode.impl.h"
#include "./sdk_OrthancPluginLogCategory.impl.h"
#include "./sdk_OrthancPluginLogLevel.impl.h"
#include "./sdk_OrthancPluginMetricsType.impl.h"
#include "./sdk_OrthancPluginPixelFormat.impl.h"
#include "./sdk_OrthancPluginReceivedInstanceAction.impl.h"
#include "./sdk_OrthancPluginResourceType.impl.h"
#include "./sdk_OrthancPluginStorageCommitmentFailureReason.impl.h"
#include "./sdk_OrthancPluginValueRepresentation.impl.h"

#include "./sdk_OrthancPluginDicomInstance.impl.h"
#include "./sdk_OrthancPluginDicomWebNode.impl.h"
#include "./sdk_OrthancPluginFindAnswers.impl.h"
#include "./sdk_OrthancPluginFindMatcher.impl.h"
#include "./sdk_OrthancPluginFindQuery.impl.h"
#include "./sdk_OrthancPluginImage.impl.h"
#include "./sdk_OrthancPluginJob.impl.h"
#include "./sdk_OrthancPluginPeers.impl.h"
#include "./sdk_OrthancPluginRestOutput.impl.h"
#include "./sdk_OrthancPluginServerChunkedRequestReader.impl.h"
#include "./sdk_OrthancPluginStorageArea.impl.h"
#include "./sdk_OrthancPluginWebDavCollection.impl.h"
#include "./sdk_OrthancPluginWorklistAnswers.impl.h"
#include "./sdk_OrthancPluginWorklistQuery.impl.h"

#include "./sdk_GlobalFunctions.impl.h"

#include "./sdk_OrthancPluginDicomInstance.methods.h"
#include "./sdk_OrthancPluginDicomWebNode.methods.h"
#include "./sdk_OrthancPluginFindAnswers.methods.h"
#include "./sdk_OrthancPluginFindMatcher.methods.h"
#include "./sdk_OrthancPluginFindQuery.methods.h"
#include "./sdk_OrthancPluginImage.methods.h"
#include "./sdk_OrthancPluginJob.methods.h"
#include "./sdk_OrthancPluginPeers.methods.h"
#include "./sdk_OrthancPluginRestOutput.methods.h"
#include "./sdk_OrthancPluginServerChunkedRequestReader.methods.h"
#include "./sdk_OrthancPluginStorageArea.methods.h"
#include "./sdk_OrthancPluginWebDavCollection.methods.h"
#include "./sdk_OrthancPluginWorklistAnswers.methods.h"
#include "./sdk_OrthancPluginWorklistQuery.methods.h"

void RegisterOrthancSdk(PyObject* module)
{
  RegisterOrthancPluginChangeTypeEnumeration(module);
  RegisterOrthancPluginCompressionTypeEnumeration(module);
  RegisterOrthancPluginConstraintTypeEnumeration(module);
  RegisterOrthancPluginContentTypeEnumeration(module);
  RegisterOrthancPluginCreateDicomFlagsEnumeration(module);
  RegisterOrthancPluginDicomToJsonFlagsEnumeration(module);
  RegisterOrthancPluginDicomToJsonFormatEnumeration(module);
  RegisterOrthancPluginDicomWebBinaryModeEnumeration(module);
  RegisterOrthancPluginErrorCodeEnumeration(module);
  RegisterOrthancPluginHttpMethodEnumeration(module);
  RegisterOrthancPluginIdentifierConstraintEnumeration(module);
  RegisterOrthancPluginImageFormatEnumeration(module);
  RegisterOrthancPluginInstanceOriginEnumeration(module);
  RegisterOrthancPluginJobStepStatusEnumeration(module);
  RegisterOrthancPluginJobStopReasonEnumeration(module);
  RegisterOrthancPluginLoadDicomInstanceModeEnumeration(module);
  RegisterOrthancPluginLogCategoryEnumeration(module);
  RegisterOrthancPluginLogLevelEnumeration(module);
  RegisterOrthancPluginMetricsTypeEnumeration(module);
  RegisterOrthancPluginPixelFormatEnumeration(module);
  RegisterOrthancPluginReceivedInstanceActionEnumeration(module);
  RegisterOrthancPluginResourceTypeEnumeration(module);
  RegisterOrthancPluginStorageCommitmentFailureReasonEnumeration(module);
  RegisterOrthancPluginValueRepresentationEnumeration(module);

  RegisterOrthancPluginDicomInstanceClass(module);
  RegisterOrthancPluginDicomWebNodeClass(module);
  RegisterOrthancPluginFindAnswersClass(module);
  RegisterOrthancPluginFindMatcherClass(module);
  RegisterOrthancPluginFindQueryClass(module);
  RegisterOrthancPluginImageClass(module);
  RegisterOrthancPluginJobClass(module);
  RegisterOrthancPluginPeersClass(module);
  RegisterOrthancPluginRestOutputClass(module);
  RegisterOrthancPluginServerChunkedRequestReaderClass(module);
  RegisterOrthancPluginStorageAreaClass(module);
  RegisterOrthancPluginWebDavCollectionClass(module);
  RegisterOrthancPluginWorklistAnswersClass(module);
  RegisterOrthancPluginWorklistQueryClass(module);
}
