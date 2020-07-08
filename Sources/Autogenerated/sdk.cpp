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


#include "sdk.h"

#include "../PythonLock.h"

#include "../../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"

#include "./sdk_OrthancPluginInstanceOrigin.impl.h"
#include "./sdk_OrthancPluginJobStepStatus.impl.h"
#include "./sdk_OrthancPluginDicomWebBinaryMode.impl.h"
#include "./sdk_OrthancPluginHttpMethod.impl.h"
#include "./sdk_OrthancPluginResourceType.impl.h"
#include "./sdk_OrthancPluginConstraintType.impl.h"
#include "./sdk_OrthancPluginPixelFormat.impl.h"
#include "./sdk_OrthancPluginCompressionType.impl.h"
#include "./sdk_OrthancPluginJobStopReason.impl.h"
#include "./sdk_OrthancPluginIdentifierConstraint.impl.h"
#include "./sdk_OrthancPluginContentType.impl.h"
#include "./sdk_OrthancPluginStorageCommitmentFailureReason.impl.h"
#include "./sdk_OrthancPluginDicomToJsonFlags.impl.h"
#include "./sdk_OrthancPluginErrorCode.impl.h"
#include "./sdk_OrthancPluginCreateDicomFlags.impl.h"
#include "./sdk_OrthancPluginDicomToJsonFormat.impl.h"
#include "./sdk_OrthancPluginMetricsType.impl.h"
#include "./sdk_OrthancPluginValueRepresentation.impl.h"
#include "./sdk_OrthancPluginImageFormat.impl.h"
#include "./sdk_OrthancPluginChangeType.impl.h"

#include "./sdk_OrthancPluginRestOutput.impl.h"
#include "./sdk_OrthancPluginServerChunkedRequestReader.impl.h"
#include "./sdk_OrthancPluginImage.impl.h"
#include "./sdk_OrthancPluginJob.impl.h"
#include "./sdk_OrthancPluginWorklistQuery.impl.h"
#include "./sdk_OrthancPluginStorageArea.impl.h"
#include "./sdk_OrthancPluginFindMatcher.impl.h"
#include "./sdk_OrthancPluginDicomWebNode.impl.h"
#include "./sdk_OrthancPluginWorklistAnswers.impl.h"
#include "./sdk_OrthancPluginFindAnswers.impl.h"
#include "./sdk_OrthancPluginPeers.impl.h"
#include "./sdk_OrthancPluginDicomInstance.impl.h"
#include "./sdk_OrthancPluginFindQuery.impl.h"

#include "./sdk_GlobalFunctions.impl.h"

void RegisterOrthancSdk(PyObject* module)
{
  RegisterOrthancPluginInstanceOriginEnumeration(module);
  RegisterOrthancPluginJobStepStatusEnumeration(module);
  RegisterOrthancPluginDicomWebBinaryModeEnumeration(module);
  RegisterOrthancPluginHttpMethodEnumeration(module);
  RegisterOrthancPluginResourceTypeEnumeration(module);
  RegisterOrthancPluginConstraintTypeEnumeration(module);
  RegisterOrthancPluginPixelFormatEnumeration(module);
  RegisterOrthancPluginCompressionTypeEnumeration(module);
  RegisterOrthancPluginJobStopReasonEnumeration(module);
  RegisterOrthancPluginIdentifierConstraintEnumeration(module);
  RegisterOrthancPluginContentTypeEnumeration(module);
  RegisterOrthancPluginStorageCommitmentFailureReasonEnumeration(module);
  RegisterOrthancPluginDicomToJsonFlagsEnumeration(module);
  RegisterOrthancPluginErrorCodeEnumeration(module);
  RegisterOrthancPluginCreateDicomFlagsEnumeration(module);
  RegisterOrthancPluginDicomToJsonFormatEnumeration(module);
  RegisterOrthancPluginMetricsTypeEnumeration(module);
  RegisterOrthancPluginValueRepresentationEnumeration(module);
  RegisterOrthancPluginImageFormatEnumeration(module);
  RegisterOrthancPluginChangeTypeEnumeration(module);

  RegisterOrthancPluginRestOutputClass(module);
  RegisterOrthancPluginServerChunkedRequestReaderClass(module);
  RegisterOrthancPluginImageClass(module);
  RegisterOrthancPluginJobClass(module);
  RegisterOrthancPluginWorklistQueryClass(module);
  RegisterOrthancPluginStorageAreaClass(module);
  RegisterOrthancPluginFindMatcherClass(module);
  RegisterOrthancPluginDicomWebNodeClass(module);
  RegisterOrthancPluginWorklistAnswersClass(module);
  RegisterOrthancPluginFindAnswersClass(module);
  RegisterOrthancPluginPeersClass(module);
  RegisterOrthancPluginDicomInstanceClass(module);
  RegisterOrthancPluginFindQueryClass(module);
}
