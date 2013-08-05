

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Jun 20 11:25:56 2011
 */
/* Compiler settings for MTCShdrBackEnd.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MTCShdrBackEnd_i_h__
#define __MTCShdrBackEnd_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IComMTCBackEnd_FWD_DEFINED__
#define __IComMTCBackEnd_FWD_DEFINED__
typedef interface IComMTCBackEnd IComMTCBackEnd;
#endif 	/* __IComMTCBackEnd_FWD_DEFINED__ */


#ifndef __ComMTCShdrBackEnd_FWD_DEFINED__
#define __ComMTCShdrBackEnd_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComMTCShdrBackEnd ComMTCShdrBackEnd;
#else
typedef struct ComMTCShdrBackEnd ComMTCShdrBackEnd;
#endif /* __cplusplus */

#endif 	/* __ComMTCShdrBackEnd_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MTCShdrBackEnd_0000_0000 */
/* [local] */ 

typedef /* [public][public] */ 
enum __MIDL___MIDL_itf_MTCShdrBackEnd_0000_0000_0001
    {	SAMPLE	= 0,
	EVENT	= 1,
	CONDITION	= 2
    } 	STORETYPE;



extern RPC_IF_HANDLE __MIDL_itf_MTCShdrBackEnd_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MTCShdrBackEnd_0000_0000_v0_0_s_ifspec;

#ifndef __IComMTCBackEnd_INTERFACE_DEFINED__
#define __IComMTCBackEnd_INTERFACE_DEFINED__

/* interface IComMTCBackEnd */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IComMTCBackEnd;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("40BF8151-65BC-4019-B8F9-D16BB4802ED9")
    IComMTCBackEnd : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StoreValue( 
            /* [in] */ BSTR dataItemName,
            /* [in] */ BSTR value,
            /* [in] */ STORETYPE type,
            BSTR alarm_code,
            /* [in] */ BSTR alarm_native) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ BSTR domain,
            /* [in] */ LONG portnumber,
            /* [in] */ BSTR devicename) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Quit( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PowerOnConnection( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE PowerOffConnection( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StoreTagMap( 
            /* [in] */ BSTR csvNames) = 0;
 
		virtual /* [id] */ HRESULT STDMETHODCALLTYPE StoreTypeMap( 
            /* [in] */ BSTR csvNames, BSTR csvTypes) = 0;
       
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTagValues( 
            /* [retval][out] */ BSTR *values) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComMTCBackEndVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComMTCBackEnd * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComMTCBackEnd * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComMTCBackEnd * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComMTCBackEnd * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComMTCBackEnd * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComMTCBackEnd * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComMTCBackEnd * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StoreValue )( 
            IComMTCBackEnd * This,
            /* [in] */ BSTR dataItemName,
            /* [in] */ BSTR value,
            /* [in] */ STORETYPE type,
            BSTR alarm_code,
            /* [in] */ BSTR alarm_native);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IComMTCBackEnd * This,
            /* [in] */ BSTR domain,
            /* [in] */ LONG portnumber,
            /* [in] */ BSTR devicename);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Quit )( 
            IComMTCBackEnd * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PowerOnConnection )( 
            IComMTCBackEnd * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *PowerOffConnection )( 
            IComMTCBackEnd * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *StoreTagMap )( 
            IComMTCBackEnd * This,
            /* [in] */ BSTR map);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetTagValues )( 
            IComMTCBackEnd * This,
            /* [retval][out] */ BSTR *values);
        
        END_INTERFACE
    } IComMTCBackEndVtbl;

    interface IComMTCBackEnd
    {
        CONST_VTBL struct IComMTCBackEndVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComMTCBackEnd_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IComMTCBackEnd_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IComMTCBackEnd_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IComMTCBackEnd_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IComMTCBackEnd_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IComMTCBackEnd_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IComMTCBackEnd_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IComMTCBackEnd_StoreValue(This,dataItemName,value,type,alarm_code,alarm_native)	\
    ( (This)->lpVtbl -> StoreValue(This,dataItemName,value,type,alarm_code,alarm_native) ) 

#define IComMTCBackEnd_Init(This,domain,portnumber,devicename)	\
    ( (This)->lpVtbl -> Init(This,domain,portnumber,devicename) ) 

#define IComMTCBackEnd_Quit(This)	\
    ( (This)->lpVtbl -> Quit(This) ) 

#define IComMTCBackEnd_PowerOnConnection(This)	\
    ( (This)->lpVtbl -> PowerOnConnection(This) ) 

#define IComMTCBackEnd_PowerOffConnection(This)	\
    ( (This)->lpVtbl -> PowerOffConnection(This) ) 

#define IComMTCBackEnd_StoreTagMap(This,map)	\
    ( (This)->lpVtbl -> StoreTagMap(This,map) ) 

#define IComMTCBackEnd_GetTagValues(This,values)	\
    ( (This)->lpVtbl -> GetTagValues(This,values) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IComMTCBackEnd_INTERFACE_DEFINED__ */



#ifndef __MTCShdrBackEndLib_LIBRARY_DEFINED__
#define __MTCShdrBackEndLib_LIBRARY_DEFINED__

/* library MTCShdrBackEndLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MTCShdrBackEndLib;

EXTERN_C const CLSID CLSID_ComMTCShdrBackEnd;

#ifdef __cplusplus

class DECLSPEC_UUID("B2937A47-5FA7-4CCC-BB95-3629857BFC86")
ComMTCShdrBackEnd;
#endif
#endif /* __MTCShdrBackEndLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


