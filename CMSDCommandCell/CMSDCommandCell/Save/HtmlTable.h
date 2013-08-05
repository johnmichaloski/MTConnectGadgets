//
// HtmlTable.h
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#pragma once

#include <vector>
#include <string>
#include "StdStringFcn.h"

class CHtmlTable
{
public:
	CHtmlTable(void);
	~CHtmlTable(void);
	std::vector<std::string>			_fields;
	std::vector<std::vector<std::string> >			_values;
	std::vector<std::string>			_aligns;
	std::string  CreateHtmlTable();
	std::string CreateHtmlAndTable();
	static std::string CreateHtmlDocument(std::string title="");
	static std::string CreateHtmlSytlesheetFrontEnd(std::string title="");
	static std::string CreateHtmlFrontEnd(std::string title="");
	static std::string HtmlStateInfo();
	static std::string TableStyle();

	STDMETHOD(SetHeaderColumns)(std::string csv); // adds history to end of tab
	STDMETHOD(SetAlignment)(std::string csv); // adds align to TH items
	STDMETHOD(AddRow)(std::string csvFields, std::string values);
	STDMETHOD(AddRows)(std::string csvFields, std::string values);
	STDMETHOD(ClearValues)(){_values.clear(); return S_OK;}

private:
	static std::string HtmlStyle();
	std::string GetHeaderRow();

};

