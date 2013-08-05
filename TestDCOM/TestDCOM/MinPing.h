#pragma once

#include "atlstr.h"
#include "comdef.h"
#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>

class CMiniPing
{
public:
	//ERROR_INSUFFICIENT_BUFFER The data area passed to a system call is too small. This error is returned if the ReplySize parameter indicates that the buffer pointed to by the ReplyBuffer parameter is too small. 

	//ERROR_INVALID_PARAMETER An invalid parameter was passed to the function. This error is returned if the IcmpHandle parameter contains an invalid handle. This error can also be returned if the ReplySize parameter specifies a value less than the size of an ICMP_ECHO_REPLY or ICMP_ECHO_REPLY32 structure.

	//ERROR_NOT_ENOUGH_MEMORY Not enough memory is available to complete the operation.

	//ERROR_NOT_SUPPORTED The request is not supported. This error is returned if no IPv4 stack is on the local computer.

	//IP_BUF_TOO_SMALL The size of the ReplyBuffer specified in the ReplySize parameter was too small. 
	//Use FormatMessage to obtain the message string for the returned error.


	CString ErrorFormatMessage(HRESULT dwLastErr )
	{
		TCHAR * pTemp;
		CString errmsg(L"");
		int nLen = ::FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL, 
			dwLastErr,
			MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
			(LPTSTR) &pTemp, 
			1, 
			NULL );

#ifdef UNICODE
		errmsg=(BSTR) pTemp;
#else
		errmsg=(char *) pTemp;
#endif

		::LocalFree( pTemp );

		return errmsg;
	}


	//http://www.geekpage.jp/en/programming/iphlpapi/send-icmp.php
	//Please note that IcmpSendEcho() can only be used with IPv4. When using ICMP with IPv6, please use Icmp6CreateFile() and Icmp6SendEcho2(). 
	CString Ping(CString host)
	{
		USES_CONVERSION;
		CString tmp;

		//convert the address into a long representation
		DWORD dwAddress = inet_addr(T2A(host));

		HANDLE hIcmp;
		char *SendData = "ICMP SEND DATA";
		LPVOID ReplyBuffer;
		DWORD dwRetVal;
		DWORD buflen;
		PICMP_ECHO_REPLY pIcmpEchoReply;

		hIcmp = IcmpCreateFile();
		if(hIcmp == INVALID_HANDLE_VALUE)
			return _T("IcmpCreateFile Failed");

		buflen = sizeof(ICMP_ECHO_REPLY) + strlen(SendData) + 1;
	
		ReplyBuffer = (VOID*) malloc(buflen);
		if (ReplyBuffer == NULL) 
			return _T("Fail");
		memset(ReplyBuffer, 0, buflen);

		pIcmpEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer;

		dwRetVal = IcmpSendEcho(hIcmp, 
			dwAddress,			//DestinationAddress
			SendData,			//RequestData
			strlen(SendData), //RequestSize
			NULL,		//RequestOptions
			ReplyBuffer,  //ReplyBuffer
			buflen,  //ReplySize
			1000);  // Timeout

		if (dwRetVal != 0) 
		{
			// Reply from 127.0.0.1: bytes=32 time<1ms TTL=128
			CString rtt;
			if (pIcmpEchoReply->RoundTripTime==0)
				rtt=_T("<1ms");
			else rtt.Format(_T("%d"), pIcmpEchoReply->RoundTripTime);

			tmp.AppendFormat(_T("Reply from %s: bytes=%d time=%s TTL=%d"), 
				(LPCTSTR) host,
				pIcmpEchoReply->DataSize,
				rtt,
				pIcmpEchoReply->Options.Ttl
				);
		} else 
		{
			int err = GetLastError();
			OutputDebugString( ErrorFormatMessage(err));
			tmp.AppendFormat(_T("Request timed out"));
			//if(pIcmpEchoReply->RoundTripTime > 1000)
			//	tmp.AppendFormat(_T("Request timed out"));
			//else
			//{
			//	tmp.AppendFormat(_T("Ping failed. "));
			//	tmp.AppendFormat(_T("Error: %ld\n"), GetLastError());
			//}

		}
		delete ReplyBuffer;
		return tmp;
	}
};


