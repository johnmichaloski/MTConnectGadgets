#pragma once

#include "MTConnectStreamsParser.h"
#include "boost/bind.hpp"

#ifndef __cplusplus
#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLAPP_H__
#error __FILE__ requires atlapp.h to be included first
#endif

#ifndef __ATLCTRLS_H__
#error __FILE__ requires atlctrls.h to be included first
#endif

#if (_WIN32_IE < 0x0500)
#error __FILE__ requires _WIN32_IE >= 0x0500
#endif

#define WM_STATUS_MSG WM_APP + 1


template< class T, class TBase = CWindow, class TWinTraits = CControlWinTraits >
class ATL_NO_VTABLE CModuleImpl : public CWindowImpl< T, TBase, TWinTraits >
{
public:
	bool m_bSunken;
	int m_iLineWidth;
	int m_iLineHeight;
	CRect room;
	CString strTitle;
	CString strStatus;
	CString strProgram;
	CString strPart;
	CFont m_fntStatusFont1;
	std::string _url;
	StreamDataDictionary _data;

	CModuleImpl(int _iLineWidth=1,int iLineHeight=1, bool _bSunken=true) : 
	m_bSunken(_bSunken),
		m_iLineWidth(_iLineWidth),
		m_iLineHeight(iLineHeight)
	{ 
		strStatus="Running";
		LOGFONT logFont = { 0 };
		logFont.lfCharSet = DEFAULT_CHARSET;
		logFont.lfHeight = 70;
		lstrcpy( logFont.lfFaceName, _T( "Arial" ) );
		//logFont.lfWeight = FW_BOLD;
		logFont.lfItalic = (BYTE)TRUE;
		m_fntStatusFont1.CreatePointFontIndirect( &logFont );
	};

	~CModuleImpl()
	{
		if(_url.size() > 0)
		{
			MTConnections.RemoveMTConnectDevice(_url);
		}
	}

	// Operations

	BOOL SubclassWindow(HWND hWnd)
	{
		ATLASSERT(m_hWnd == NULL);
		ATLASSERT(::IsWindow(hWnd));
		BOOL bRet = CWindowImpl< T, TBase, TWinTraits >::SubclassWindow(hWnd);
		return bRet;
	}

	// Implementation

	// Message map and handlers

	BEGIN_MSG_MAP(CBevelLineImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		MESSAGE_HANDLER(WM_STATUS_MSG, OnStatus)
	END_MSG_MAP()

	LRESULT OnStatus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CWindow wnd(this->m_hWnd);
		CDCHandle dc = wnd.GetDC();
		dc.SetBkMode( TRANSPARENT );
		StreamData streamdata =  _data["execution"];
		strStatus = streamdata.value.c_str();
		CRect rcText(room);
		CFontHandle fh = dc.SelectFont(m_fntStatusFont1);
		//dc.SetTextColor( m_rgbStaticText );
		if(!strStatus.IsEmpty())
			dc.DrawText( strStatus, strStatus.GetLength(), rcText, DT_CENTER| DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
		dc.SelectFont(fh);
		return 0;
	}
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 0;
	}
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(wParam != NULL)
		{
			pT->DoPaint((HDC)wParam);
		}
		else
		{
			CPaintDC dc(m_hWnd);
			pT->DoPaint(dc.m_hDC);
		}
		return 0;
	}

	// Fixme, add left, center, right, top, middle, bottom
	void SetCaption(CString _text) { this->strTitle=_text; }
	void SetDimensions(CRect rect) { this->room = rect; }
	void MTConnectUpdate(StreamDataDictionary data) 
	{ 
		if( data["execution"].value !=  _data["execution"].value)
			Invalidate();
		_data= data;
	}
	void RemoveMTConnection()
	{
		MTConnections.RemoveMTConnectDevice(_url);
	}
	void SetMTConnection(std::string url)
	{
		if(url.size() > 0)
			RemoveMTConnection(); // 
		_url=url;
		MTConnections.AddMTConnectDevice(url);
		MTConnections.AddNotification(url, boost::bind( &CModuleImpl::MTConnectUpdate, this, _1 ));
	}
	void GetFittingFont(CDCHandle dc, CFont _Font, CRect rect)
	{
		CSize size;
		dc.SelectFont( _Font);
		GetTextExtent(LPCTSTR lpszString, int nCount, &size)
		while(size.cy > 0 && size.cx > rect.Width() && size.cy > rect.Height())
		{
			LOGFONT logFont;
			_Font.GetLogFont(logFont)
			_Font= _Font.CreatePointFont(logFont.lfHeight-1, logFont.lfFaceName);
			dc.SelectFont( _Font);
			GetTextExtent(LPCTSTR lpszString, int nCount, &size)
		};
	}


	void Draw3dRect(CDCHandle dc, CRect r,  int width, COLORREF clrTopLeft, COLORREF clrBottomRight)
	{
		int x=r.left, y=r.top,  cx=r.Width(),  cy=r.Height();
		dc.FillSolidRect(x, y, cx - width, width, clrTopLeft);
		dc.FillSolidRect(x, y, width, cy - width, clrTopLeft);
		dc.FillSolidRect(x + cx, y, -width, cy, clrBottomRight);
		dc.FillSolidRect(x, y + cy, cx, -width, clrBottomRight);
	}

	void DrawGradientRect(CDCHandle dc, CRect rect,  COLORREF clr1, COLORREF clr2)
	{
		TRIVERTEX tv[2];
		tv[0].x=rect.left;
		tv[0].y=rect.top;
		tv[0].Red = (clr1&0xFF ) * 256;
		tv[0].Green =  ((clr1&0xFF00 )/ 0x100) * 256;
		tv[0].Blue = ((clr1&0xFF0000 )/ 0x10000) * 256;

		tv[1].x=rect.right;
		tv[1].y=rect.bottom;
		tv[1].Red = (clr2&0xFF ) * 256;
		tv[1].Green =  ((clr2&0xFF00 )/ 0x100) * 256;
		tv[1].Blue = ((clr2&0xFF0000 )/ 0x10000) * 256;

		GRADIENT_RECT gr = { 0, 1 };

		dc.GradientFill ( tv, 2, &gr, 1, GRADIENT_FILL_RECT_V );
	}

	void DoPaint(CDCHandle dc)
	{
		CRect r;
		//GetClientRect(&r); 
		DWORD hiCol = ::GetSysColor(!m_bSunken ? COLOR_GRADIENTACTIVECAPTION : COLOR_GRADIENTINACTIVECAPTION); 
		DWORD loCol = ::GetSysColor(m_bSunken ? COLOR_GRADIENTACTIVECAPTION : COLOR_GRADIENTINACTIVECAPTION); 

		r=this->room; // l,top,right,bottom       // ---------------

		Draw3dRect(dc,  r, 4, hiCol,loCol);
		r.DeflateRect( 4, 4 );
		//dc.FillSolidRect(r.left, r.top, r.Width(), r.Height(), RGB(0xFF,00,00));
		//DrawGradientRect( dc, r, RGB(0xCC,00,00), RGB(0xAA,00,00));

		CString strAvail =  _data.GetNamedValue("power").c_str();
		strStatus =  _data.GetNamedValue("execution").c_str();
		strProgram =  _data.GetNamedValue("program").c_str();
		if(!stricmp(strStatus, "UNAVAILABLE"))
		{
			DrawGradientRect( dc, r,RGB(235,85,95), RGB(219,68,68));  // reddish
			strStatus =  "Down";
			strProgram = "";

		}
		else if(!stricmp(strStatus, "EXECUTING")||
			!stricmp(strStatus, "ACTIVE"))
		{
			DrawGradientRect( dc, r, RGB(87,235,109), RGB(68,219,85));  // greenish
		}
		else if(!stricmp(strAvail, "OFF"))
		{
			DrawGradientRect( dc, r, RGB(235,85,95), RGB(219,68,68));  // reddish
		}
		else if(!stricmp(strStatus, "PAUSED")||
			!stricmp(strStatus, "STOPPED"))
		{
			DrawGradientRect( dc, r, RGB(230,235,89), RGB(217,210,71)); // yellowish
		}
		else // assume ready
		{
			DrawGradientRect( dc, r, RGB(0x00,0xdd,0xdd), RGB(0x00,0x88,0x88)); // blueish
		}


		//DrawGradientRect( dc, r, RGB(0xFF,0xFF,0xFF), RGB(0xFF,0xFF,0x88));
		//dc.Draw3dRect(&r,hiCol,loCol); 
		//r.DeflateRect( 2, 2 );		 			
		//dc.Draw3dRect(&r,hiCol,loCol); 

		//CSize size; 
		//dc.GetTextExtent(strText, strText.GetLength(),&size);


		CRect rcText(room);
		rcText.OffsetRect( 2, 2 );		 			
		dc.SetBkMode( TRANSPARENT );
		if(!strTitle.IsEmpty())
		dc.DrawText( strTitle, strTitle.GetLength(), rcText, DT_CENTER| DT_SINGLELINE | DT_NOPREFIX | DT_TOP);
		CFontHandle fh = dc.SelectFont(m_fntStatusFont1);
		//dc.SetTextColor( m_rgbStaticText );
		if(!strStatus.IsEmpty())
			dc.DrawText( strStatus, strStatus.GetLength(), rcText, DT_CENTER| DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER);
		if(!strProgram.IsEmpty())
			dc.DrawText( strProgram, strProgram.GetLength(), rcText, DT_CENTER| DT_SINGLELINE | DT_NOPREFIX | DT_BOTTOM);
		dc.SelectFont(fh);

	}
};

class CModuleWindow : public CModuleImpl<CModuleWindow>
{
public:
	DECLARE_WND_CLASS(_T("WTL_ModuleWindow"))
	CStatic * _static;
	UINT _cntrID;
	std::string _resourcename;
	UINT GetId() { return _cntrID; }
	std::string &ResourceName() { return _resourcename; }

	CModuleWindow(HWND hwnd, CString caption, CRect rect, int _iLineWidth=1,int iLineHeight=1, bool _bSunken=true)
		: CModuleImpl<CModuleWindow>(_iLineWidth, iLineHeight,  _bSunken)
	{
		static UINT cntrID = 2000;
		_cntrID=cntrID;
		_resourcename=caption;
		_static = new CStatic();
		_static->Create(hwnd, rect ,_T("TEST"), WS_CHILD|WS_VISIBLE|SS_NOTIFY, 0, cntrID++);
		// adjust dimensions to drawing will be inside this control
		rect.bottom=rect.Height(); rect.right=rect.Width(); rect.left=0; rect.top=0; 
		this->SetDimensions(rect);
		if(!caption.IsEmpty())
		this->SetCaption(caption);

		this->SubclassWindow(_static->m_hWnd);

	}
	~CModuleWindow() 
	{
		_static->DestroyWindow();
	}
};