// OpcUaNotatation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OpcUaGenerator.h"
#include "StdStringFcn.h"

int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hRes = ::CoInitialize(NULL);
	COpcUaGenerator opcua;
	//opcua.ReadXmlSchema(::ExeDirectory() + "MTConnectDevices_1.2.xsd");
	opcua._bSampleTypes=true;
	opcua.ReadXmlSchema(::ExeDirectory() + "MTConnectStreams_1.3.xsd");
	opcua.AddConditions();
	std::string html = opcua.GenerateStreamsDocument(::ExeDirectory() + "test.html");
	WriteFile(::ExeDirectory() + "test.html", html);
	opcua.Close();
	opcua.Clear();

	opcua._bSampleTypes=false;
	opcua.ReadXmlSchema(::ExeDirectory() + "MTConnectAssets_1.2.xsd");
	html =opcua.GenerateAssetsDocument();
	WriteFile(::ExeDirectory() + "assets.html", html);
	opcua.Close();

	opcua.Clear();
	opcua.ReadXmlSchema(::ExeDirectory() + "MTConnectDevices_1.2.xsd");
	opcua._UsedTypes.clear();
	opcua.MarkElementTypes("Sensor");
	opcua.MarkElementTypes("SensorConfiguration");

	
	html =opcua.GenerateSensorsDocument();
	WriteFile(::ExeDirectory() + "sensor.html", html);
	opcua.Close();

	::CoUninitialize();
	return 0;
}

