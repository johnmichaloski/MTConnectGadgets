// aboutdlg.cpp : implementation of the CAboutDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "atlstr.h"

#include "aboutdlg.h"

LRESULT CAboutDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow(GetParent());
	return TRUE;
}

LRESULT CAboutDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CSelectionDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	_cAllitems=GetDlgItem(IDC_LISTALL);
	_cSelectionsitems=GetDlgItem(IDC_SELECTEDLIST);

	for(int i=0; i< _allitems.size(); i++)
	{
		if(_allitems[i].size() < 1)
			continue;
			_cAllitems.AddString(_allitems[i].c_str());
	}
	for(int i=0; i< _selecteditems.size(); i++)
	{
		if(_selecteditems[i].size() < 1)
			continue;
		_cSelectionsitems.AddString(_selecteditems[i].c_str());
	}	
	return TRUE;
}

LRESULT CSelectionDlg::OnUpDownCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int n = _cSelectionsitems.GetCurSel();
	if(n<0)// no selection ..
		return 0;
	CString text;
	_cSelectionsitems.GetText(n,text);
	if(wID == IDC_UPBUTTON)
	{
		_cSelectionsitems.DeleteString(n);
		if(n-1<0)
		{
			n = _cSelectionsitems.InsertString(-1,text);
			_cSelectionsitems.SetCurSel(n);
		}
		else
		{
			n=_cSelectionsitems.InsertString(n-1,text);
			_cSelectionsitems.SetCurSel(n);
		}
	}
	else
	{
		_cSelectionsitems.DeleteString(n);
		if(n>=_cSelectionsitems.GetCount())
			n=_cSelectionsitems.InsertString(0,text);
		else
			n=_cSelectionsitems.InsertString(n+1,text);
		_cSelectionsitems.SetCurSel(n);

	}
	return 0;
}
LRESULT CSelectionDlg::OnAddRemoveCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	if(wID == IDC_ADDBUTTON)
	{	
		int numberSelected = _cAllitems.GetSelCount();
		if(numberSelected<0)
			return 0;
		std::vector<int> selIndex(numberSelected);
		_cAllitems.GetSelItems( numberSelected, &selIndex[0] );
		CString text;
		for(int i=0;i<	numberSelected; i++)
		{
			_cAllitems.GetText(selIndex[i], text);
			_cSelectionsitems.AddString(text);
		}
	}
	else if(wID == IDC_REMOVEBUTTON)
	{	
		int n = _cSelectionsitems.GetCurSel();
		if(n<0)// no selection ..
			return 0;	
		n=_cSelectionsitems.DeleteString(n); 
		_cSelectionsitems.SetCurSel(n-1);
	}
	return 0;
}
LRESULT CSelectionDlg::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString text;
	_selecteditems.clear();
	for(int i=0; i< _cSelectionsitems.GetCount(); i++)
	{
		_cSelectionsitems.GetText(i, text);
		_selecteditems.push_back((LPCSTR) text);
	}

	EndDialog(wID);
	return 0;
}
LRESULT CSelectionDlg::OnSelectAllCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	if(wID == IDC_SELECTALLBUTTON)
	{
		_cAllitems.SelItemRange(TRUE, 0, _cAllitems.GetCount()-1);
	}
	if(wID == IDC_UNSELECTALLBUTTON)
	{
		_cAllitems.SelItemRange(FALSE, 0, _cAllitems.GetCount()-1);
	}	
	return 0;
}
////////////////////////////////////////////////////////////////////////////////

LRESULT CPropertiesDlg::OnAddDeleteCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	if(wID == IDC_ADD)
	{
		std::string nvpair;
		CString text;
		cName.GetWindowTextA(text);
		nvpair+=(LPCSTR) text;
		nvpair+=",";
		cValue.GetWindowTextA(text);
		nvpair+=(LPCSTR) text;
		nvpair+=",";
		cUnits.GetWindowTextA(text);
		nvpair+=(LPCSTR) text;
		nvpair+=",";
		cDescription.GetWindowTextA(text);
		nvpair+=(LPCSTR) text;
		nvpair+=";";
		listbox.AddString(nvpair.c_str());
		cName.SetWindowTextA("");
		cValue.SetWindowTextA("");
		cUnits.SetWindowTextA("");
		cDescription.SetWindowTextA("");
	}
	else if(wID == IDC_EDITBUTTON)
	{
		CString text;
		int n=listbox.GetCurSel();
		if(n<0)
			return 0;
		listbox.GetText(n,text);
		std::vector<std::string> tokens = Tokenize(RightTrim(std::string((LPCSTR) text),";"),",");

		if (tokens.size() < 1)  tokens.push_back("");
		if (tokens.size() < 2)  tokens.push_back("");
		if (tokens.size() < 3) tokens.push_back("");
		
		cName.SetWindowTextA(tokens[0].c_str());
		cValue.SetWindowTextA(tokens[1].c_str());
		cUnits.SetWindowTextA(tokens[2].c_str());
		cDescription.SetWindowTextA(tokens[3].c_str());
		listbox.DeleteString(n);
	}

	return 0;
}

void CTestFormView::DrawObjects()
{
	double xscale=1,yscale=1;
	for(int i=0; i<m_module.size(); i++)
		if(m_module[i]->m_hWnd!=NULL)
			m_module[i]->DestroyWindow();
	for(int i=0; i<m_bevellines.size(); i++)
		if(m_bevellines[i]->m_hWnd!=NULL)
			m_bevellines[i]->DestroyWindow();



	// if objects size and modules size dont match or are different - need to destroy window.
	_objects = Layout().objects();
	for(int i=0; i< _objects.size(); i++)
	{
		std::string resource = _objects[i]->GetValue("associatedResource");
		if(resource == "Area")
		{
			double iX  = (GetSystemMetrics(SM_CXSCREEN)) ;
			double iY  = (GetSystemMetrics(SM_CYSCREEN));
			boundingbox.right=iX;
			boundingbox.bottom=iY;

			xscale =	magnifier * iX / atof(_objects[i]->GetValue("boundaryWidth").c_str());
			yscale =	magnifier * iY / atof(_objects[i]->GetValue("boundaryDepth").c_str());
		}
	}
	for(int i=0; i< _objects.size(); i++)
	{
		std::string resource = _objects[i]->GetValue("associatedResource");	

		int off=1;
		if(resource == "Area")
		{
			CRect arect(off,off, xscale *boundingbox.Width()-off, yscale * boundingbox.Height()-off); 
			//m_bevellines.push_back(new CBevelSquare(m_hWnd, "", arect, 3,3,true));
			continue;
		}
		int boundaryWidth =	 atof(_objects[i]->GetValue("boundaryWidth").c_str()) ;
		int boundaryDepth =	 atof(_objects[i]->GetValue("boundaryDepth").c_str()) ;
		int placementX =	 atof(_objects[i]->GetValue("placementX").c_str()) ;
		int placementY =	 atof(_objects[i]->GetValue("placementY").c_str()) ;

		if(resource == "Room")
		{
			std::string name = _objects[i]->GetValue("name");
			CRect arect(placementX * xscale,placementY * yscale, 
				(placementX+boundaryWidth)* xscale,(placementY+ boundaryDepth) * yscale); 
			OutputDebugString(StdStringFormat("Room = %d %d %d %d\n",  arect.left, arect.top, arect.right , arect.bottom).c_str());
			m_bevellines.push_back(new CBevelSquare(m_hWnd,  name.c_str(), arect,3,3,true));
			continue;

		}
		CRect rect(CPoint(placementX* xscale,placementY* yscale),CSize(boundaryWidth* xscale,boundaryDepth* yscale));

		OutputDebugString(StdStringFormat("%d,%d,%d,%d,%s\n", rect.top,rect.left,rect.Width(), rect.Height(),resource.c_str()).c_str());

		m_module.push_back(new CModuleWindow(m_hWnd,resource.c_str(), rect,2,2));
		m_moduleMap[resource.c_str()]= m_module.back();

		// Add tooltip
		std::string descr = _objects[i]->GetValue("description");
		TTAdd( (UINT) m_module.back()->GetId() );
		TTSetTxt( (UINT) m_module.back()->GetId() , ATL::_U_STRINGorID(descr.c_str()) );

		// Add MTConnect connection
		std::string url = _objects[i]->GetPropertyValue("MTConnect");
		if(url.size() > 0)
			m_module.back()->SetMTConnection(url);

	}
	Invalidate();
}

LRESULT CTestFormView::ResetMTConnect(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	for(int i=0, j=0; i< m_module.size(); i++)
	{
		std::string resource = _objects[i]->GetValue("associatedResource");	

		if(resource == "Area")
			continue;
		if(resource == "Room")
			continue;
		// Reset MTConnect connection
		std::string url = _objects[i]->GetPropertyValue("MTConnect");
		if(url.size() > 0)
			m_module[j]->SetMTConnection(url);
		j++;
	}
	return 0;
}

LRESULT CTestFormView::OnZoom(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

	SIZE sizeWnd;
	GetScrollSize(sizeWnd);
	if(wID==ID_ZOOM_IN)
	{
		magnifier += .2;
	}
	else if(wID==ID_ZOOM_OUT)
	{
	//	SetScrollSize(sizeWnd.cx/2, sizeWnd.cx/2);
		magnifier -= .2;
	}	
	
	DrawObjects();
	Invalidate();

	return 0;
}
