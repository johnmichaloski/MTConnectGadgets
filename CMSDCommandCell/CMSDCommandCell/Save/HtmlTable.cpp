//
// HtmlTable.cpp
//


#include "StdAfx.h"
#include "HtmlTable.h"


CHtmlTable::CHtmlTable(void)
{
}


CHtmlTable::~CHtmlTable(void)
{
}
std::string  CHtmlTable::CreateHtmlTable()
{
	std::string updatetable;
	std::string style;
	
	updatetable += "<TABLE class=\"gridtable\">\n";
	updatetable +=   "<TR>";
	updatetable +=  GetHeaderRow();
	updatetable +=   "</TR>\n";

	for(int i = 0; i!=_values.size(); i++)
	{
		std::vector<std::string> values = _values[i];
	

		updatetable +=   "<TR>\n";
		for(int j=0; j< values.size(); j++)
		{
			updatetable +=   "<TD";
			if((((int) _aligns.size())-1) > j )
				if( !_aligns[j].empty())
					updatetable += " align=\""+ _aligns[j] + "\"";
			updatetable +=   "> "+ values[j] + "</TD>" ;
		}
		updatetable +=   "</TR>\n";
	}

	updatetable += "</TABLE>\n";
	return updatetable;
}
std::string CHtmlTable::CreateHtmlAndTable()
{
	std::string html = CreateHtmlDocument();
	html=ReplaceOnce(html, "Loading", CreateHtmlTable());
	return html;

}
STDMETHODIMP CHtmlTable::AddRow(std::string csvFields, std::string csvValues)
{
	std::vector<std::string> values = TrimmedTokenize(csvValues,",");
	std::vector<std::string> fields = TrimmedTokenize(csvFields,",");
	if(fields.size() != values.size())
		return E_FAIL;
	_values.push_back(values);
	return S_OK;
}
STDMETHODIMP CHtmlTable::AddRows(std::string csvFields, std::string csvValues)
{
	std::vector<std::string> valuelines = TrimmedTokenize(csvValues,"\n");
	std::vector<std::string> fields = TrimmedTokenize(csvFields,",");

	for(int i=0; i< valuelines.size(); i++)
	{
		std::vector<std::string> values = TrimmedTokenize(valuelines[i],",");
		if(fields.size() != values.size())
			return E_FAIL;
		_values.push_back(values);
	}
	return S_OK;
}	


STDMETHODIMP CHtmlTable::SetAlignment(std::string aligns)
{
	if(aligns.size() < 1)
		return E_FAIL;
	_aligns = TrimmedTokenize(aligns,",");
	return S_OK;
}

STDMETHODIMP CHtmlTable::SetHeaderColumns(std::string csv)
{
	std::string fields( csv);
	if(fields.size() < 1)
		return E_FAIL;
	_fields = TrimmedTokenize(fields,",");
	return S_OK;
}

std::string CHtmlTable::GetHeaderRow()
{
	std::string html;
	for(int i=0; i< _fields.size(); i++)
	{
		html+="<TH>" + _fields[i] + "</TH>";
	}
	html+="\n";
	return html;
}

std::string CHtmlTable::CreateHtmlFrontEnd(std::string title)
{
	std::string html;
	html += "<HTML>\n";
	html += "<HEAD>\n";
	html +=" <title>" + title + "</title>";
	html += "<STYLE>" + HtmlStyle() ; 
	html +="$('#myTable td[title]')\n";
	html +=".hover(function() {\n";
	html +="    showTooltip($(this));\n";
	html +=" }, function() {\n";
	html +="     hideTooltip();\n";
	html +=" })\n";
	html +=";\n";
	html += "</STYLE>"; 
	html +="<script type=\"text/javascript\">\n";
	html +="function showTooltip($el) {\n";
	html +="    // insert code here to position your tooltip element (which i'll call $tip)\n";
	html +="    $tip.html($el.attr('title'));\n";
	html +="}\n";
	html +="function hideTooltip() {\n";
	html +="    $tip.hide();\n";
	html +="}\n";
	html +="</script>\n";

	html +="</HEAD>\n";
	html +="<BODY>\n";
	return html;
}

std::string CHtmlTable::CreateHtmlDocument(std::string title)
{
	std::string html= CreateHtmlFrontEnd(title);
	html += "<DIV id=""Header""> Plant Performance</DIV>\n";
	html += "<DIV id=""Device""> Loading </DIV>\n";
	html += "</BODY>\n";
	html += "</HTML>\n";
	return html;
}

std::string CHtmlTable::CreateHtmlSytlesheetFrontEnd(std::string title)
{
	std::string html;
	html += "<HTML>\n";
	html += "<HEAD>\n";
	html +=" <title>" + title + "</title>\n";
	//html +=" <link rel=\"stylesheet\" href=\"file:///" + ReplaceAll(::ExeDirectory(),"\\","/") + "tank.css\" type=\"text/css\">\n";
	html += "<STYLE>\n" ; 
	html+=TableStyle();
	html += "</STYLE>\n"; 
	html += "</HEAD>\n";


	//html += "</BODY>\n";
	//html += "</HTML>\n";
	return html;
}
std::string CHtmlTable::HtmlStyle()
{
	std::string style;
	style+= "P\n";
	style+= "{\n";
	style+= " FONT-FAMILY: ""Myriad"", sans-serif;\n";
	// style+= " FONT-SIZE: 70%;\n";
	style+= " LINE-HEIGHT: 12pt;\n";
	style+= " MARGIN-BOTTOM: 0px;\n";
	style+= " MARGIN-LEFT: 10px;\n";
	style+= " MARGIN-TOP: 10px\n";
	style+= "}\n";
	style+= "input.btn {   color:#050;   font: bold 84% 'trebuchet ms',helvetica,sans-serif;   background-color:#fed;   border: 1px solid;   border-color: #696 #363 #363 #696;   filter:progid:DXImageTransform.Microsoft.Gradient   (GradientType=0,StartColorStr='#ffffffff',EndColorStr='#ffeeddaa'); } \n";
	style+= "input.btnhov {   border-color: #c63 #930 #930 #c63; <input type=\"button\" value=\"Submit\" class=\"bt\n\"   onmouseover=\"this.className='btn btnhov'\" onmouseout=\"this.className='btn'\"/> }\n";

	style+= "H1\n";
	style+= "{\n";
	style+= " BACKGROUND-COLOR: #003366;\n";
	style+= " BORDER-BOTTOM: #336699 6px solid;\n";
	style+= " COLOR: #ffffff;\n";
	style+= " FONT-SIZE: 130%;\n";
	style+= " FONT-WEIGHT: normal;\n";
	style+= " MARGIN: 0em 0em 0em -20px;\n";
	style+= " PADDING-BOTTOM: 8px;\n";
	style+= " PADDING-LEFT: 30px;\n";
	style+= " PADDING-TOP: 16px\n";
	style+= "}\n";
	style+=TableStyle();
		return style;
}
std::string CHtmlTable::TableStyle()
{
	std::string style;
	style+= "table.gridtable {\n";
	style+= "  BACKGROUND-COLOR: #f0f0e0;\n";
	style+= " BORDER-BOTTOM: #ffffff 0px solid;\n";
	style+= " BORDER-COLLAPSE: collapse;\n";
	style+= " BORDER-LEFT: #ffffff 0px solid;\n";
	style+= " BORDER-RIGHT: #ffffff 0px solid;\n";
	style+= " BORDER-TOP: #ffffff 0px solid;\n";
	//style+= " FONT-SIZE: 70%;\n";
	style+= " FONT-SIZE: 9pt;\n";
	style+= " MARGIN-LEFT: 10px\n";
	style+= "  }\n";
	style+= "table.gridtable td {\n";
	style+= " BACKGROUND-COLOR: #e7e7ce;\n";
	style+= " BORDER-BOTTOM: #ffffff 1px solid;\n";
	style+= " BORDER-LEFT: #ffffff 1px solid;\n";
	style+= " BORDER-RIGHT: #ffffff 1px solid;\n";
	style+= " BORDER-TOP: #ffffff 1px solid;\n";
	style+= " PADDING-LEFT: 3px\n";
	style+= "  }\n";
	style+= "table.gridtable th {\n";
	style+= " BACKGROUND-COLOR: #cecf9c;\n";
	style+= " BORDER-BOTTOM: #ffffff 1px solid;\n";
	style+= " BORDER-LEFT: #ffffff 1px solid;\n";
	style+= " BORDER-RIGHT: #ffffff 1px solid;\n";
	style+= " BORDER-TOP: #ffffff 1px solid;\n";
	style+= " COLOR: #000000;\n";
	style+= " FONT-WEIGHT: bold\n";
	style+= "  }\n";

	/*style+= "  h1 {\n";
	style+= "  font-size : 11px;\n";
	style+= "  text-transform : uppercase;\n";
	style+= "  margin : 0;\n";
	style+= "  }\n";
	style+= "  h2 {\n";
	style+= "  color : #9A1212;\n";
	style+= "  font-size : 20px;\n";
	style+= "  font-weight : normal;\n";
	style+= "  padding : 5px 10px;\n";
	style+= "  margin : 0;\n";
	style+= "  }\n";*/

	return style;
}

std::string CHtmlTable::HtmlStateInfo()
{
	std::string tmp;
	tmp +="<P>";
	tmp +="Factory equipment can be modeled by state machines. \n";
	tmp +="Using a state model, resource cost-function can be modeled be time in a state.\n";
	tmp += "The basic state machine formalism is given as: OFF, PROCESSING(Busy), FAULTED(Down), BLOCKED and STARVED.\n";
		tmp += "<P>The Off state indicates that the process equipment is not in use (unpowered).  \n";
		tmp += "The Processing state indicates the equipment is working to produce product.  \n";
		tmp += "The Starved state indicates that there are missing input materials so the equipment is paused.  \n";
		tmp += "If the storage facility for the process output is full, the process is in the Blocked state and the equipment delays processing.\n";
		tmp += "When equipment has a break down or fault, the process stops and the equipment is in the Faulted state. \n";
		tmp += "The numbers for repair for a piece of equipment when it has a break down or fault, indicate the equipment is immediately in the repair state although this is unlikely. \n";

		tmp +="<P>";

	return tmp;
}