//
// DataDictionary.h
//

#pragma once
#include <string>
#include "StdStringFcn.h"

class less_NoCaseString
{
public:
	bool operator() (const std::string& x, const std::string& y) const
	{return (stricmp( x.c_str(), y.c_str() )<0); }
};
class DataDictionary : public std::map<std::string, std::string, less_NoCaseString> 
{
public:
	std::string ValueList(std::string csvfields)
	{
		std::string tmp;
		std::vector<std::string> _fields = Tokenize(csvfields,",");
		for(int i=0; i< _fields.size(); i++)
		{
			if(i>0) tmp+=",";
			tmp+= this->operator [](_fields[i]);
		}
		return tmp;
	}

	static std::string HrMinSecFormat(int sec);
	static std::string HrMinSecFormat(double sec);
	void Update(double seconds);
	std::map<std::string, double, less_NoCaseString>  accumulations;
};

