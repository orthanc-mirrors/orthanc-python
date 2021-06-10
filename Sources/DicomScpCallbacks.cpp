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


#include "DicomScpCallbacks.h"

#include "../Resources/Orthanc/Plugins/OrthancPluginCppWrapper.h"
#include "Autogenerated/sdk.h"
#include "ICallbackRegistration.h"
#include "PythonString.h"


static PyObject* findScpCallback_ = NULL;
static PyObject* moveScpCallback_ = NULL;


static PyObject *GetFindQueryTag(sdk_OrthancPluginFindQuery_Object* self,
                                 PyObject *args,
                                 bool isGroup)
{
  unsigned long index;
  uint16_t group, element;
  
  if (self->object_ == NULL)
  {
    PyErr_SetString(PyExc_ValueError, "Invalid object");
    return NULL;
  }
  else if (!PyArg_ParseTuple(args, "k", &index))
  {
    PyErr_SetString(PyExc_TypeError, "Index is missing");
    return NULL;
  }
  else if (OrthancPluginGetFindQueryTag(OrthancPlugins::GetGlobalContext(), &group, &element, self->object_, index) !=
           OrthancPluginErrorCode_Success)
  {
    PyErr_SetString(PyExc_ValueError, "Index is out of range");
    return NULL;
  }
  else if (isGroup)
  {
    return PyLong_FromUnsignedLong(group);
  }
  else
  {
    return PyLong_FromUnsignedLong(element);
  }
}



// Check out "CUSTOM_METHODS" in "../CodeAnalysis/ParseOrthancSDK.py"
PyObject *GetFindQueryTagGroup(sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  return GetFindQueryTag(self, args, true);
}


PyObject *GetFindQueryTagElement(sdk_OrthancPluginFindQuery_Object* self, PyObject *args)
{
  return GetFindQueryTag(self, args, false);
}


static OrthancPluginErrorCode FindCallback(OrthancPluginFindAnswers *answers,
                                           const OrthancPluginFindQuery *query,
                                           const char *issuerAet,
                                           const char *calledAet)
{
  try
  {
    PythonLock lock;

    PyObject *pAnswers, *pQuery;
    
    {
      PythonObject args(lock, PyTuple_New(2));
      PyTuple_SetItem(args.GetPyObject(), 0, PyLong_FromSsize_t((intptr_t) answers));
      PyTuple_SetItem(args.GetPyObject(), 1, PyBool_FromLong(true /* borrowed, don't destruct */));
      pAnswers = PyObject_CallObject((PyObject *) GetOrthancPluginFindAnswersType(), args.GetPyObject());
    }
    
    {
      PythonObject args(lock, PyTuple_New(2));
      PyTuple_SetItem(args.GetPyObject(), 0, PyLong_FromSsize_t((intptr_t) query));
      PyTuple_SetItem(args.GetPyObject(), 1, PyBool_FromLong(true /* borrowed, don't destruct */));
      pQuery = PyObject_CallObject((PyObject *) GetOrthancPluginFindQueryType(), args.GetPyObject());
    }
    
    PythonString pIssuerAet(lock, issuerAet);
    PythonString pCalledAet(lock, calledAet);

    {
      PythonObject args(lock, PyTuple_New(4));
      PyTuple_SetItem(args.GetPyObject(), 0, pAnswers);
      PyTuple_SetItem(args.GetPyObject(), 1, pQuery);
      PyTuple_SetItem(args.GetPyObject(), 2, pIssuerAet.Release());
      PyTuple_SetItem(args.GetPyObject(), 3, pCalledAet.Release());

      assert(findScpCallback_ != NULL);
      PythonObject result(lock, PyObject_CallObject(findScpCallback_, args.GetPyObject()));
    }

    return lock.CheckCallbackSuccess("Python C-FIND SCP callback");
  }
  catch (OrthancPlugins::PluginException& e)
  {
    return e.GetErrorCode();
  }
}



class IMoveDriver : public boost::noncopyable
{
public:
  virtual ~IMoveDriver()
  {
  }

  virtual void Apply() = 0;
};

   
static void* CreateMoveCallback(OrthancPluginResourceType resourceType,
                                const char *patientId,
                                const char *accessionNumber,
                                const char *studyInstanceUid,
                                const char *seriesInstanceUid,
                                const char *sopInstanceUid,
                                const char *originatorAet,
                                const char *sourceAet,
                                const char *targetAet,
                                uint16_t originatorId)
{
  class Driver : public IMoveDriver
  {
  private:
    OrthancPluginResourceType  resourceType_;
    std::string                patientId_;
    std::string                accessionNumber_;
    std::string                studyInstanceUid_;
    std::string                seriesInstanceUid_;
    std::string                sopInstanceUid_;
    std::string                originatorAet_;
    std::string                sourceAet_;
    std::string                targetAet_;
    uint16_t                   originatorId_;
    
  public:
    Driver(OrthancPluginResourceType resourceType,
           const char *patientId,
           const char *accessionNumber,
           const char *studyInstanceUid,
           const char *seriesInstanceUid,
           const char *sopInstanceUid,
           const char *originatorAet,
           const char *sourceAet,
           const char *targetAet,
           uint16_t originatorId) :
      resourceType_(resourceType),
      originatorId_(originatorId)
    {
      if (patientId != NULL)
      {
        patientId_.assign(patientId);
      }

      if (accessionNumber != NULL)
      {
        accessionNumber_.assign(accessionNumber);
      }
      
      if (studyInstanceUid != NULL)
      {
        studyInstanceUid_.assign(studyInstanceUid);
      }

      if (seriesInstanceUid != NULL)
      {
        seriesInstanceUid_.assign(seriesInstanceUid);
      }

      if (sopInstanceUid != NULL)
      {
        sopInstanceUid_.assign(sopInstanceUid);
      }

      if (originatorAet != NULL)
      {
        originatorAet_.assign(originatorAet);
      }

      if (sourceAet != NULL)
      {
        sourceAet_.assign(sourceAet);
      }

      if (targetAet != NULL)
      {
        targetAet_.assign(targetAet);
      }
    }

    
    virtual void Apply() ORTHANC_OVERRIDE
    {
      PythonLock lock;

      PythonObject kw(lock, PyDict_New());

      std::string level;
      switch (resourceType_)
      {
        case OrthancPluginResourceType_Patient:
          level = "PATIENT";
          break;
          
        case OrthancPluginResourceType_Study:
          level = "STUDY";
          break;
          
        case OrthancPluginResourceType_Series:
          level = "SERIES";
          break;
          
        case OrthancPluginResourceType_Instance:
          level = "INSTANCE";
          break;

        default:
          throw OrthancPlugins::PluginException(OrthancPluginErrorCode_ParameterOutOfRange);
      }

      {
        PythonString tmp(lock, level);
        PyDict_SetItemString(kw.GetPyObject(), "Level", tmp.Release());
      }

      {
        PythonString tmp(lock, patientId_);
        PyDict_SetItemString(kw.GetPyObject(), "PatientID", tmp.Release());
      }

      {
        PythonString tmp(lock, accessionNumber_);
        PyDict_SetItemString(kw.GetPyObject(), "AccessionNumber", tmp.Release());
      }

      {
        PythonString tmp(lock, studyInstanceUid_);
        PyDict_SetItemString(kw.GetPyObject(), "StudyInstanceUID", tmp.Release());
      }

      {
        PythonString tmp(lock, seriesInstanceUid_);
        PyDict_SetItemString(kw.GetPyObject(), "SeriesInstanceUID", tmp.Release());
      }

      {
        PythonString tmp(lock, sopInstanceUid_);
        PyDict_SetItemString(kw.GetPyObject(), "SOPInstanceUID", tmp.Release());
      }

      {
        PythonString tmp(lock, originatorAet_);
        PyDict_SetItemString(kw.GetPyObject(), "OriginatorAET", tmp.Release());
      }

      {
        PythonString tmp(lock, sourceAet_);
        PyDict_SetItemString(kw.GetPyObject(), "SourceAET", tmp.Release());
      }

      {
        PythonString tmp(lock, targetAet_);
        PyDict_SetItemString(kw.GetPyObject(), "TargetAET", tmp.Release());
      }

      PyDict_SetItemString(kw.GetPyObject(), "OriginatorID", PyLong_FromUnsignedLong(originatorId_));

      PythonObject args(lock, PyTuple_New(0));

      assert(moveScpCallback_ != NULL);
      PythonObject result(lock, PyObject_Call(moveScpCallback_, args.GetPyObject(), kw.GetPyObject()));

      OrthancPluginErrorCode code = lock.CheckCallbackSuccess("Python C-MOVE SCP callback");
      if (code != OrthancPluginErrorCode_Success)
      {
        throw OrthancPlugins::PluginException(code);
      }
    }
  };
  
  try
  {
    return new Driver(resourceType, patientId, accessionNumber, studyInstanceUid,
                      seriesInstanceUid, sopInstanceUid, originatorAet, sourceAet,
                      targetAet, originatorId);
  }
  catch (OrthancPlugins::PluginException& e)
  {
    return NULL;
  }
}


static uint32_t GetMoveSize(void *moveDriver)
{
  assert(moveDriver != NULL);
  return 1;
}


OrthancPluginErrorCode ApplyMove(void *moveDriver)
{
  assert(moveDriver != NULL);
  
  try
  {
    reinterpret_cast<IMoveDriver*>(moveDriver)->Apply();
    return OrthancPluginErrorCode_Success;
  }
  catch (OrthancPlugins::PluginException& e)
  {
    return e.GetErrorCode();
  }
}

   
void FreeMove(void *moveDriver)
{
  assert(moveDriver != NULL);
  delete reinterpret_cast<IMoveDriver*>(moveDriver);
}

   
PyObject* RegisterFindCallback(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")

  class Registration : public ICallbackRegistration
  {
  public:
    virtual void Register() ORTHANC_OVERRIDE
    {
      OrthancPluginRegisterFindCallback(OrthancPlugins::GetGlobalContext(), FindCallback);
    }
  };

  Registration registration;
  return ICallbackRegistration::Apply(
    registration, args, findScpCallback_, "Python C-FIND SCP callback");
}


PyObject* RegisterMoveCallback(PyObject* module, PyObject* args)
{
  // The GIL is locked at this point (no need to create "PythonLock")

  class Registration : public ICallbackRegistration
  {
  public:
    virtual void Register() ORTHANC_OVERRIDE
    {
      OrthancPluginRegisterMoveCallback(
        OrthancPlugins::GetGlobalContext(), CreateMoveCallback, GetMoveSize, ApplyMove, FreeMove);
    }
  };

  Registration registration;
  return ICallbackRegistration::Apply(
    registration, args, moveScpCallback_, "Python C-MOVE SCP callback");
}


void FinalizeDicomScpCallbacks()
{
  ICallbackRegistration::Unregister(findScpCallback_);
  ICallbackRegistration::Unregister(moveScpCallback_);
}
