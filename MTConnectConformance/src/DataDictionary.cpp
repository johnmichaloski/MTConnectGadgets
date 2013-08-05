//
// DataDictionary.cpp
//
#include "stdafx.h"
#include "DataDictionary.h"
#include "StdStringFcn.h"

std::string DataDictionary::HrMinSecFormat(int sec)
{
	return StdStringFormat("%02d:%02d:%02d", sec/3600,  (sec%3600)/60,  sec%60);
}
std::string DataDictionary::HrMinSecFormat(double dsec)
{
	int sec=dsec;
//	return StdStringFormat("%02d:%02d:%02d", sec/3600,  (sec/60),  sec%60);
	return StdStringFormat("%02d:%02d:%02d", sec/3600,  (sec%3600)/60,  sec%60);
}

void DataDictionary::Update(double seconds)
{
	if(this->find("Srpm")!=this->end())
	{
		int srpm = ConvertString<int>(this->operator[]("Srpm"), 0);
		accumulations["Srpm"]+= srpm * seconds/60.0 ; // number of revolutions
	}
	// add loads

}
