//
// ShdrEcho.cpp
//

// This software was developed by U.S. Government employees as part of
// their official duties and is not subject to copyright. No warranty implied 
// or intended.

#include "StdAfx.h"
#include "ShdrEcho.h"
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

void CShdrEchoInstance::EchoShdr(std::string s)
{
	OutputDebugString(s.c_str());
	std::cout << s.c_str();
}

CShdrEchoInstance::CShdrEchoInstance(std::string devicesxmlfilename, 
									 std::string shdrfilename, 
									 int ipport, 
									 double dOverride,
									 std::string devicename)
{
	Init(devicesxmlfilename, shdrfilename,  ipport, dOverride, devicename);
}
void CShdrEchoInstance::Init(std::string devicesxmlfilename, 
									 std::string shdrfilename, 
									 int ipport, 
									 double dOverride,
									 std::string devicename)
{
	DevicesXmlFilename()=devicesxmlfilename;
	ShdrFilename() =shdrfilename;
	IpAddress() ="127.0.0.1"; // really cant be anything else
	IpPort()=ipport;
	DeviceName() = devicename;
	Override()=dOverride;
	_bFaultThread=false;

	if(DevicesXmlFilename().empty())
		DevicesXmlFilename()=ExeDirectory() + "devices.xml";

	_bRepeat=true;

	_backend = new CoComMTCShdrBackEnd();
	_backend->Init(_bstr_t(IpAddress().c_str()), IpPort(), _bstr_t(DeviceName().c_str()));
	_backend->MyLogger().AddListener(boost::bind(&CShdrEchoInstance::EchoShdr, this,_1));

	_dict = _deviceparser.ReadDeviceDescription(DevicesXmlFilename());
	std::string storemap,itemlist, typelist;
	int i=0;
	for(DataDictionary::iterator it = _dict.begin(); it!=_dict.end(); it++, i++)
	{
		if((*it).first.empty())
		{
			i--;
			continue;
		}
		if(i>0) itemlist+=",";
		if(i>0) typelist+=",";
		storemap+=(*it).first+"="+(*it).first+"\n";  // isomorphic: alias = name
		itemlist+=(*it).first;
		typelist+=_dict[(*it).first];
	}
	_backend->StoreTagMap(_bstr_t(storemap.c_str()));
	_backend->StoreTypeMap(_bstr_t(itemlist.c_str()),bstr_t(typelist.c_str()));

	Open();
	_state=Ready;
}

CShdrEchoInstance::~CShdrEchoInstance(void)
{
}

void CShdrEchoInstance::Open() 
{
	// FIXME: blank lines and other stuff not handled well.

	if(GetFileAttributesA(_shdrfilename.c_str())== INVALID_FILE_ATTRIBUTES)
	{
		_shdrfilename= ::ExeDirectory() + _shdrfilename;
	}

	in.open(_shdrfilename.c_str());
	if(GetNextTokens())
	{
		lasttime = GetDateTime(tokens[0]);
		//SetTimer ( 1, 1000 );
		OutputTokens();

		localvalues=_backend->_values;
		std::string info=_backend->ShdrString(_backend->_values);;
		if(!info.empty())
			EchoShdr(info.c_str());
	}
	else
	{
		Fault();
		std::cout << StdStringFormat("Problem reading file%s\n", ShdrFilename().c_str());
	}
}

void CShdrEchoInstance::Start()
{
	_state=Running;
	_bRunning=true;
	_thread= boost::thread(boost::bind(&CShdrEchoInstance::Cycle, this));
	if(_bFaultThread)
	{
		_faultthread= boost::thread(boost::bind(&CShdrEchoInstance::FaultThread, this)); 
	}
}
void CShdrEchoInstance::Close(void)
{
	_state=Stopping;
	_bRunning=false;
	::Sleep(1000);
	_backend->Quit();
}

std::string GetRandomAlaram()
{
	static char * alarms[] = { 
		"Door open",
		"Battery alarm",
		"Temperature alarm",
		"Fan alarm",
		"5V/24V encoder or 15V D/A converter undervoltage",
		"NC memory full",
		"Software limit switch",
		"feedrate not programmed",
		"Axis at working area limit"
	};
	int n = rand() % sizeof(alarms)/sizeof(char *);
	return alarms[n];
}
#include "SimMath.h"
void  CShdrEchoInstance::FaultThread()
{
	//	2009-06-15T00:02:19.575164|htemp|WARNING|HTEMP|1|HIGH|Oil Temperature High

	// Never ending loop. Normally the thread will never finish
	double delay = _mtbfstat.RandomVariable();
	boost::this_thread::sleep(boost::posix_time::milliseconds((int) (delay*60.0*1000.)));  
	_backend->StoreValue(_bstr_t("system"), _bstr_t("FAULT"), "logic_cond", _bstr_t("CONDITION"), _bstr_t(""),_bstr_t(""),_bstr_t(GetRandomAlaram().c_str()));
	while(true)
	{
		try
		{
			delay = _mttrstat.random.next_dbl();
			boost::this_thread::sleep(boost::posix_time::milliseconds((int) (delay*60.*1000.)) );  
			_backend->StoreValue(_bstr_t("system"), _bstr_t("NORMAL"), "logic_cond", _bstr_t(""), _bstr_t(""), _bstr_t(""));

			delay = _mtbfstat.RandomVariable();
			boost::this_thread::sleep(boost::posix_time::milliseconds((int) (delay*60.0*1000.)));  
			_backend->StoreValue(_bstr_t("system"), _bstr_t("FAULT"), "logic_cond", _bstr_t("CONDITION"), _bstr_t(""),_bstr_t(""), bstr_t(GetRandomAlaram().c_str()));

			// Interrupt can only occur in wait/sleep or join operation.
			// If you don't do that, call interuption_point().
			// Remove this line, and the thread will never be interrupted.
			boost::this_thread::interruption_point();
		}
		catch(const boost::thread_interrupted&)
		{
			// Thread interruption request received, break the loop
			std::cout<<"- Thread interrupted. Exiting thread."<<std::endl;
			break;
		}
	}
}
int CShdrEchoInstance::GetNextTokens()
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

	tokens=TrimmedTokenize(_buffer, "|");
	if(bSetLastTime && tokens.size()>0)
		lasttime = GetDateTime(tokens[0]);
	return tokens.size();
}

void CShdrEchoInstance::OutputTokens()
{
	// skip token[0] which is a timestamp
	for(int i=1; i< tokens.size(); )
	{
		DataDictionary::iterator it=_dict.find(tokens[i]);
		if(it==_dict.end())
		{
			// assume bad event or sample, ignore bad condition
			i+=2;
			continue;
		}
		std::string type= (*it).second;
		if(type == "sample" || type == "event")
		{
			if(i+1 >= tokens.size())
				break;
			_backend->StoreValue(_bstr_t(tokens[i].c_str()), _bstr_t(tokens[i+1].c_str()), type);
			i=i+2;
		}
		else
		{
			if(i+5 >= tokens.size())
				break;
			_backend->StoreValue(_bstr_t(tokens[i].c_str()), 
				_bstr_t(tokens[i+1].c_str()), type, 
				_bstr_t(tokens[i+2].c_str()), 
				_bstr_t(tokens[i+3].c_str()),
				_bstr_t(tokens[i+4].c_str()),
				_bstr_t(tokens[i+5].c_str())
				);
			i=i+6;
		}
	}
}

HRESULT CShdrEchoInstance::Cycle()
{
	double delay;
	while(_state==Running)
	{
		OutputTokens(); // this parses a line of shdr 
		std::string info = _backend->UpdatedShdrString(localvalues);
		if(!info.empty())
			EchoShdr(info.c_str());
		localvalues=_backend->_values;

		GetNextTokens();
		// That's it all done for now. Have to start again.
		if(tokens.size() < 1)
			break;

		intime = GetDateTime(tokens[0]);
	/*	if(intime.GetStatus() != valid)
		{
			intime=lasttime;

		}*/
		if(lasttime.m_dt == 0.0)
			lasttime=intime;

		diff= (intime-lasttime);
		::AtlTrace("Diff = %f\n", diff.GetTotalSeconds());
		delay = diff.GetTotalSeconds() * 1000;
		delay = delay * 100.0/ _dOverride;
		if(delay<1) 
			delay=10;

		lasttime=intime;
		boost::posix_time::milliseconds workTime((int) delay); 
		boost::this_thread::sleep(workTime);  
	}
	 _state=Ready;
	 return 0;
}



