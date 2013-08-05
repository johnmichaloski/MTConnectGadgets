#if 0
		html+="MTConnect has XSD models for devices, errors, assets and for streams. This section covers the mapping from streams to OPC UA. \n";
		html+="The MTConnect specification uses the XML schema \"Venetian blinds\" model so that all elements are strongly typed.\n";
		html+="Although all data items are strongly typed, if the type is to an integer or sttring, then XML namespace data type is used for clarity.";
		html+="In this section, MTConnect XSD simple types (including enumerations),MTConnect XSD complex types, and MTConnect XSD elements\n";
		html+="<P>Note, XSD attributes map into OPC UA properties.\n";
		html+=" As such, many MTConnect types have ID and/or Name which are already specified as part of the XXXX OPC UA base type\n";


		html+="<P> the MTCOnnect XML Schema to OPC UA mapping is defined as so far as: <UL>\n";
		html+="<LI> ComplexType name  => BrowseName </LI>\n";
		html+="<LI> Complex type => DataType</LI>\n";
		html+="<LI> Complex Type Attribute=”abstract” = true/false => map into IsAbstract. Assume false if not found.</LI>\n";
		html+="<LI> Complex type with attribute ref  treated as DataType – I need to check this.</LI>\n";
		html+="<LI> For all Attribute-> HasProperty</LI>\n";
		html+="<LI> Complex type check for sequence of elements => map into HasComponent</LI>\n";
		html+="<LI> minOccurs and maxOccurs some reasoning to determine Modeling Rule: <UL>";
		html+="<LI>(0..1) = Optional</LI>\n";
		html+="<LI>(1..x)  = Mandatory</LI>\n";
		html+="<LI>(x..unbounded) = OptionalPlaceholder.</LI>\n";
		html+="</UL></UL>\n";
#endif

For W2010 and an already existing TOC. Select the TOC and the empty paragraph mark on the line below.  Right click and choose Edit Field.  In the Field dialog--with TOC selected as the field code--click the Table of Contents button.   In the Table of Content dialog, the general section in on the lower left.


	style+= "table.gridtable {\n";
	style+= " 	BACKGROUND-COLOR: #f0f0e0;\n";
	style+= "	BORDER-BOTTOM: #ffffff 0px solid;\n";
	style+= "	BORDER-COLLAPSE: collapse;\n";
	style+= "	BORDER-LEFT: #ffffff 0px solid;\n";
	style+= "	BORDER-RIGHT: #ffffff 0px solid;\n";
	style+= "	BORDER-TOP: #ffffff 0px solid;\n";
	//style+= "	FONT-SIZE: 70%;\n";
	style+= "	FONT-SIZE: 9pt;\n";
	style+= "	MARGIN-LEFT: 10px\n";
	style+= "  }\n";

	style+= "table.gridtable td {\n";
	style+= "	BACKGROUND-COLOR: #e7e7ce;\n";
	style+= "	BORDER-BOTTOM: #ffffff 1px solid;\n";
	style+= "	BORDER-LEFT: #ffffff 1px solid;\n";
	style+= "	BORDER-RIGHT: #ffffff 1px solid;\n";
	style+= "	BORDER-TOP: #ffffff 1px solid;\n";
	style+= "	PADDING-LEFT: 3px\n";
	style+= "  }\n";
	style+= "table.gridtable th {\n";
	style+= "	BACKGROUND-COLOR: #cecf9c;\n";
	style+= "	BORDER-BOTTOM: #ffffff 1px solid;\n";
	style+= "	BORDER-LEFT: #ffffff 1px solid;\n";
	style+= "	BORDER-RIGHT: #ffffff 1px solid;\n";
	style+= "	BORDER-TOP: #ffffff 1px solid;\n";
	style+= "	COLOR: #000000;\n";
	style+= "	FONT-WEIGHT: bold\n";
	style+= "  }\n";

	style+= "table.histogram {\n";
	style+= " 	BACKGROUND-COLOR: #f0f0e0;\n";
	style+= "	border-width: 0px;\n";
	style+= "	BORDER-COLLAPSE: collapse;\n";
	style+= "	padding: 0px;\n";
	//style+= "	FONT-SIZE: 70%;\n";
	style+= "	FONT-SIZE: 9pt;\n";
	style+= "	MARGIN-LEFT: 0px\n";
	style+= "  }\n";
	style+= "table.histogram td {\n";
	style+= "	BORDER-BOTTOM: #ffffff 0px solid;\n";
	style+= "	BORDER-LEFT: #ffffff 0px solid;\n";
	style+= "	BORDER-RIGHT: #ffffff 0px solid;\n";
	style+= "	BORDER-TOP: #ffffff 0px solid;\n";
	style+= "	PADDING: 0px\n";
	style+= "	margin: 0px\n";
	style+= "  }\n";
	
	
	/*MSXML2::IXMLDOMNodeListPtr pAttrs = pNode->selectNodes(_bstr_t(".//xs:attribute"));
				for(int j=0; j< pAttrs->length; j++)
				{
					MSXML2::IXMLDOMNodePtr pAttr = NULL;	
					pAttrs->get_item(j, &pAttr);
					AttrType attr;
					attr._name=(LPCSTR)GetAttribute(pAttr, "name");
					attr._type=(LPCSTR)GetAttribute(pAttr, "type");
					std::string use = (LPCSTR)GetAttribute(pAttr, "use");
					if(use == "required")
						attr._use="Mandatory";
					else
						attr._use="Optional";
					type._attr.push_back(attr);
				}*/
				
				
#if 0
				subtype=simpletype._name + "Enum";
				html+="<p>Enumeration: " + ANAME( simpletype._name + "Enum" ) + "</p>\n";

				html+="<table class=\"gridtable\" style='width:600px'>\n";

				html+="<tr><th colspan='2' align='left' style='width:200px'> Enum </th>";
				html+="<th colspan='4' align='left' style='width:400px'> Description </th></tr>";
				int n=1;
				for(std::map<std::string, std::string>::iterator it =  simpletype._enum.begin();
					it!=simpletype._enum.end(); it++, n++) 
				{
					html+="<tr><td colspan='2' align='left' style='width:200px'>" +  (*it).first + "_" + ConvertToString(n) +"</td>";
					html+="<td colspan='4' align='left' style='width:400px'>" + mapping[(*it).first] + "</td></tr>";
				}

				html+="</table><BR>\n";
#endif