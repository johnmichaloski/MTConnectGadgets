/*
* Copyright (c) 2008, AMT – The Association For Manufacturing Technology (“AMT”)
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the AMT nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* DISCLAIMER OF WARRANTY. ALL MTCONNECT MATERIALS AND SPECIFICATIONS PROVIDED
* BY AMT, MTCONNECT OR ANY PARTICIPANT TO YOU OR ANY PARTY ARE PROVIDED "AS IS"
* AND WITHOUT ANY WARRANTY OF ANY KIND. AMT, MTCONNECT, AND EACH OF THEIR
* RESPECTIVE MEMBERS, OFFICERS, DIRECTORS, AFFILIATES, SPONSORS, AND AGENTS
* (COLLECTIVELY, THE "AMT PARTIES") AND PARTICIPANTS MAKE NO REPRESENTATION OR
* WARRANTY OF ANY KIND WHATSOEVER RELATING TO THESE MATERIALS, INCLUDING, WITHOUT
* LIMITATION, ANY EXPRESS OR IMPLIED WARRANTY OF NONINFRINGEMENT,
* MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. 

* LIMITATION OF LIABILITY. IN NO EVENT SHALL AMT, MTCONNECT, ANY OTHER AMT
* PARTY, OR ANY PARTICIPANT BE LIABLE FOR THE COST OF PROCURING SUBSTITUTE GOODS
* OR SERVICES, LOST PROFITS, LOSS OF USE, LOSS OF DATA OR ANY INCIDENTAL,
* CONSEQUENTIAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OR OTHER DIRECT DAMAGES,
* WHETHER UNDER CONTRACT, TORT, WARRANTY OR OTHERWISE, ARISING IN ANY WAY OUT OF
* THIS AGREEMENT, USE OR INABILITY TO USE MTCONNECT MATERIALS, WHETHER OR NOT
* SUCH PARTY HAD ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.
*/

#ifndef FAKE_ADAPTER_HPP
#define FAKE_ADAPTER_HPP

#include "adapter.hpp"
#include "device_datum.hpp"
#include "service.hpp"
#include "condition.hpp"
#include "atlcom.h"
#define IDC_SRCOBJ 1001
#if 0
static _ATL_FUNC_INFO OnStartExecutionInfo = {
         CC_STDCALL,   // Calling convention.
         VT_I4,        // Return type.
         1,            // Number of arguments.
         {VT_DISPATCH}       // Argument types.
      };

class CSinkObj : public IDispEventImpl<IDC_SRCOBJ, CSinkObj>
{

public:
	BEGIN_SINK_MAP(CSinkObj)
		 SINK_ENTRY_INFO(IDC_SRCOBJ, DIID__EventSink, 1 /*DISPID*/, OnStartExecution /*Event Handler*/, &OnStartExecutionInfo)
	END_SINK_MAP()

  // event handler for event defined in idl as
         // [id(1)] HRESULT Tick([in] long tckcnt);
         HRESULT __stdcall OnStartExecution(IDispatch * pIPartProgram)
         {
            ATLTRACE("CSinkObj::OnStartExecution\n");
            return S_OK;
         }
};
#endif

class FakeAdapter : public Adapter, public MTConnectService
{
protected:
  /* Define all the data values here */
  
  /* Events */
  Availability mAvailability; 
  Condition mSystem; 
  Sample mPos;
  Execution mExecution;
  
public:
  FakeAdapter(int aPort);
  ~FakeAdapter();
  
  virtual void initialize(int aArgc, const char *aArgv[]);
  virtual void start();
  virtual void stop();

  /* Instantiate Pure virtual method to get the data from the device. */

  virtual void gatherDeviceData();
  //CComPtr<IOPCSyncIO>		_pComIO;
  CComPtr<IDispatch> _appdispatch;
  CComPtr<IDispatch> _progdispatch;
 //CComPtr<CSinkObj> pSinkObj;
};

#endif

