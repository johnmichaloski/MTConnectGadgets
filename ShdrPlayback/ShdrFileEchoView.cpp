//
// ShdrFileEchoView.cpp : implementation of the CShdrFileEchoView class
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "stdafx.h"
#include "resource.h"

#include "ShdrFileEchoView.h"
#include "StdStringFcn.h"

static COleDateTime GetDateTime(std::string s)
{
	// parse 2012-02-03T17:31:51.0968Z 
	int Year, Month, Day, Hour, Minute, Second, Millisecond;
	if(sscanf(s.c_str(), "%d-%d-%dT%d:%d:%d.%d", &Year, &Month, &Day, &Hour, &Minute,&Second, &Millisecond)==7){}
		//12/2/2009 2:42:25 PM
	else if(sscanf(s.c_str(), "%d/%d/%4d%d:%d:%d", &Month, &Day, &Year,  &Hour, &Minute,&Second)==6){}
	else throw std::exception("Unrecognized date-time format\n");
	return COleDateTime( Year, Month, Day, Hour, Minute, Second ); 
}
void CShdrFileEchoView::EchoShdr(const TCHAR * msg)
{
	CString s;
	if(!IsWindow())
		return;
	CWindow wnd = GetDlgItem(IDC_ECHOEDIT);
	wnd.GetWindowText(s);
	CString m(msg);
	if(m[m.GetLength()-1]!='\n')
		m+="\r\n";
	else
		m.Replace("\n","\r\n");
	s=s+m;
	GetDlgItem(IDC_ECHOEDIT).SetWindowText(s);

}
CShdrFileEchoView::CShdrFileEchoView()
{
	_bRepeat=true;
	_dOverride=1.0;

	_backend = new CoComMTCShdrBackEnd();
	_backend->Init(_bstr_t("127.0.0.1"), 7878, _bstr_t(""));
	_backend->MyLogger().AddListener(boost::bind(&CShdrFileEchoView::EchoShdr, this,_1));

	_dict = _deviceparser.ReadDeviceDescription(ExeDirectory() + "devices.xml");
	std::string storemap,itemlist,typelist;
	int i=0;
	for(DataDictionary::iterator it = _dict.begin(); it!=_dict.end(); it++, i++)
	{
		if(i>0) itemlist+=",";
		if(i>0) typelist+=",";
		storemap+=(*it).first+"="+(*it).first+"\n";  // isomorphic: alias = name
		itemlist+=(*it).first;
		typelist+=_dict[(*it).second];
	}
	_backend->StoreTagMap(_bstr_t(storemap.c_str()));
	_backend->StoreTypeMap(_bstr_t(itemlist.c_str()),bstr_t(typelist.c_str()));
}

BOOL CShdrFileEchoView::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

LRESULT CShdrFileEchoView::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	DlgResize_Init();
	return TRUE;
}

void CShdrFileEchoView::Start() 
{
	if(GetNextTokens())
	{
		lasttime = GetDateTime(tokens[0]);
		SetTimer ( 1, 1000 );
		OutputTokens();

		localvalues=_backend->_values;
		std::string info=_backend->ShdrString(_backend->_values);;
		if(!info.empty())
			EchoShdr(info.c_str());
	}
	else
	{
		MessageBox("Problem reading file\n");
	}
}

int CShdrFileEchoView::GetNextTokens()
{
	bool bSetLastTime=false;
	tokens.clear();
	getline(in,_buffer);
	if(in.eof( ))
	{
		in.clear();					// forget we hit the end of file
		in.seekg(0, std::ios::beg); // move to the start of the file
		if(!_bRepeat)
			return 0;
		getline(in,_buffer);
		bSetLastTime=true;
	}

	tokens=Tokenize(_buffer, "|");
	if(bSetLastTime && tokens.size()>0)
		lasttime = GetDateTime(tokens[0]);
	for(int i=0; i< tokens.size(); i++) Trim(tokens[i]);
	return tokens.size();
}

void CShdrFileEchoView::OutputTokens()
{
	for(int i=1; i< tokens.size(); )
	{
		DataDictionary::iterator it=_dict.find(tokens[i]);
		if(it==_dict.end())
		{
			i+=2;
			continue;
		}
		std::string type= (*it).second;
		if(type == "sample" || type == "event")
		{
			_backend->StoreValue(_bstr_t(tokens[i].c_str()), _bstr_t(tokens[i+1].c_str()), type, _bstr_t(""), _bstr_t(""));
			i=i+2;
		}
		else
		{
			_backend->StoreValue(_bstr_t(tokens[i].c_str()), _bstr_t(tokens[i+1].c_str()), type, _bstr_t(tokens[i+2].c_str()), _bstr_t(tokens[i+3].c_str()));
			i=i+6;
		}
	}
}

LRESULT CShdrFileEchoView::OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	int delay;

	KillTimer ( 1);
	OutputTokens();
	std::string info = _backend->UpdatedShdrString(localvalues);
	if(!info.empty())
		EchoShdr(info.c_str());
	localvalues=_backend->_values;

	GetNextTokens();
	if(tokens.size() < 1)
	{ 
		// That's it all done for now. Have to start again.
		return 0;
	}
	intime = GetDateTime(tokens[0]);
	if(lasttime.m_dt == 0.0)
		lasttime=intime;

	diff= (intime-lasttime);
	::AtlTrace("Diff = %f\n", diff.GetTotalSeconds());
	delay = diff.GetTotalSeconds() * 1000;
	delay = delay * _dOverride ;
	if(delay<1) 
		delay=100;

	lasttime=intime;

	SetTimer(1,delay);

	return 0;
}


void CShdrFileEchoView::Close(void)
{
	KillTimer(1);
	::Sleep(1000);
	_backend->Quit();

}
