//
//
//
#include "stdafx.h"
#include <sstream>

#include <numeric>
#include "NIST/SimpleReflection.h"
#include "NIST/ResourceIntegrator.h"
#include "NIST/StdStringFcn.h"

crp::Config IObject::config;

MetaType IObject::GetType(int i) 
{  
	MyStructMeta ** metadata = GetMetaData(); 
	return (MetaType) metadata[i]->eType; 
}
MetaType IObject::GetType(bstr_t name) 
{  
	int n = GetIndex ((LPCSTR) name); 
	if(n>=0) 
		return GetType(n); 
	else 
		return  type_is_none;
}
bstr_t IObject::GetDelimString(std::vector<bstr_t> strs, std::string delim)
{
	bstr_t tmp("");
	for(int i=0; i< strs.size(); i++)
	{
		tmp+=strs[i]+delim.c_str();
	}
	return tmp;
}
std::vector<bstr_t>  IObject::GetVectorString(bstr_t commastrs, std::string delim)
{
	std::vector<bstr_t> bstrs;
	std::string tmp(commastrs);
	RightTrim(tmp,delim);
	std::vector<std::string> strs = Tokenize(tmp, delim);
	for(int i=0; i< strs.size(); i++)
		bstrs.push_back(strs[i].c_str());

	return bstrs;
}
std::vector<std::string> IObject::GetList(std::string classname, std::string variable)
{
	int i;
	std::vector<std::string> items;
	for(i=0; i< GetAllClassnames().size(); i++)
	{
		if(GetAllClassnames()[i]==classname)
			break;
	}
	if(i==GetAllClassnames().size())
		return items;
	std::vector<IObjectPtr> * objects = IObject::GetAllObjects()[i];
	for(int j=0; j<objects->size(); j++)
	{
		items.push_back( objects->at(j)->GetValue(variable));
	}
	return items;
}
std::string IObject::GetPropertyValue(std::string name)
{
	for(int i=0; i< properties.size(); i++)
	{
		std::vector<std::string> tokens = Tokenize(RightTrim(std::string((LPCSTR) properties[i]),";"),",");
		if(tokens.size() < 2)
			continue;
		if(tokens[0]==name)
			return tokens[1];
	}
	return "";
}

void IObject::Copy(IObject * from)
{
	std::stringstream tmp; 
	MyStructMeta ** metato = this->GetMetaData();
	for(int i=0; metato[i]!=NULL; i++)
	{
		MyStructMeta * ameta =  metato[i];
		if(ameta->eType == type_is_bstr_t)
		{
			bstr_t data = (LPCSTR) *(bstr_t *) ((char *) from + ameta->oFieldOffset);
			*(bstr_t *)((char *) this + ameta->oFieldOffset) =  data;
		}
		else if(ameta->eType == type_is_array ||
			ameta->eType == type_is_propertylist )  // comma delimited string
		{
			std::vector<bstr_t> * bstrs = (std::vector<bstr_t> *) ((char *) from + ameta->oFieldOffset);
			*(std::vector<bstr_t> *) ((char *) this + ameta->oFieldOffset) =  * bstrs;
	
		}
	}
}

std::string IObject::Dump()
{
	std::stringstream tmp; 
	MyStructMeta ** meta = this->GetMetaData();
	for(int i=0; meta[i]!=NULL; i++)
	{
		MyStructMeta * ameta =  meta[i];
		if(ameta->eType == type_is_bstr_t)
		{
			OutputDebugString((LPCSTR) ameta->pszFieldName) ; //,(LPCSTR) *(bstr_t *) (object+ ameta->oFieldOffset) ).c_str()); ;
			OutputDebugString(StdStringFormat("%=%s\n", (LPCSTR) *(bstr_t *) ((char *) this + ameta->oFieldOffset) ).c_str()); ;
		}
	}
	return tmp.str();
}
std::vector<std::string> IObject::GetHeaders()
{
	std::vector<std::string> tmp; 
	MyStructMeta ** meta = this->GetMetaData();
	for(int i=0; meta[i]!=NULL; i++)
	{
		MyStructMeta * ameta =  meta[i];
		tmp.push_back(ameta->pszFieldName);
	}
	return tmp;
}
int IObject::GetIndex (std::string name)
{
	MyStructMeta ** meta = this->GetMetaData();
	for(int i=0; meta[i]!=NULL; i++)
	{
		MyStructMeta * ameta =  meta[i];
		if(name ==  (LPCSTR) ameta->pszFieldName)
			return i;
	}
	return -1;

}
bstr_t GetCommaString(std::vector<bstr_t> * bstrs, std::string delim=",")
{
	bstr_t tmp("");
	for(int i=0; i< bstrs->size(); i++)
	{
		if(i>0) tmp+=delim.c_str();
		tmp+=bstrs->at(i);
	}
	return tmp;

}
std::string IObject::GetValue(int index)
{
	MyStructMeta ** meta = this->GetMetaData();

	if(index < 0 || index >= HeaderCount())
	{
		return ""; 
	}
	
	MyStructMeta * ameta =  meta[index];

	if(ameta->eType == type_is_bstr_t)
	{
		return ( (LPCSTR) *(bstr_t *) ((char *) this + ameta->oFieldOffset) );
	}
	// treat like a vector of bstr for now  name=value(units)description,...
	// Big problem is multiline descriptions - not handled
	else if(ameta->eType == type_is_propertylist) 
	{
		std::vector<bstr_t> * bstrs = (std::vector<bstr_t> *) ((char *) this + ameta->oFieldOffset);
		bstr_t a = accumulate( (*bstrs).begin(), (*bstrs).end(), bstr_t("") );
		return ((LPCSTR) a);

	}
	else if(ameta->eType == type_is_array)  // comma delimited string
	{
		std::vector<bstr_t> * bstrs = (std::vector<bstr_t> *) ((char *) this + ameta->oFieldOffset);
		bstr_t a = GetCommaString(bstrs,","); // accumulate( (*bstrs).begin(), (*bstrs).end(), bstr_t(",") );
		return ((LPCSTR) a);
	}
	return "";
}
std::string IObject::GetValue(std::string name)
{
	std::stringstream tmp; 
	MyStructMeta ** meta = this->GetMetaData();
	for(int i=0; meta[i]!=NULL; i++)
	{
		MyStructMeta * ameta =  meta[i];
		if(name !=  (LPCSTR) ameta->pszFieldName)
			continue;
		return GetValue(i);
	}
	return "";
}
static bstr_t appendsemicolon (bstr_t i) { return i+";"; }

void IObject::SetValue(int index, std::string value)
{
	MyStructMeta ** meta = this->GetMetaData();
	if(index < 0 || index >= HeaderCount())
	{
		return; 
	}

	MyStructMeta * ameta =  meta[index];
	if(ameta->eType == type_is_bstr_t)
	{
		bstr_t data = value.c_str();
		*(bstr_t *)((char *) this + ameta->oFieldOffset) =  data;
		return;
	}
	// treat like a vector of bstr for now  name=value(units)description,...
	else if(ameta->eType == type_is_propertylist) 
	{
		std::vector<bstr_t>  bstrs = GetVectorString(value.c_str(), ";");
		std::vector<bstr_t> second(bstrs.size());
		transform (bstrs.begin(), bstrs.end(), second.begin(), appendsemicolon);

		*(std::vector<bstr_t> *) ((char *) this + ameta->oFieldOffset) = second;

	}
	else if(ameta->eType == type_is_array)  // comma delimited string
	{
		std::vector<bstr_t>  bstrs = GetVectorString(value.c_str());
		*(std::vector<bstr_t> *) ((char *) this + ameta->oFieldOffset) = bstrs;
	}	
}

void IObject::SetValue(std::string name, std::string value)
{
	std::stringstream tmp; 
	MyStructMeta ** meta = this->GetMetaData();
	for(int i=0; meta[i]!=NULL; i++)
	{
		MyStructMeta * ameta =  meta[i];
		if(name !=  (LPCSTR) ameta->pszFieldName)
			continue;
		SetValue(i, value); 
		return;
		//if(ameta->eType == type_is_bstr_t)
		//{
		//	bstr_t data = value.c_str();
		//	*(bstr_t *)((char *) this + ameta->oFieldOffset) =  data;
		//	return;
		//}
		//	// treat like a vector of bstr for now  name=value(units)description,...
		//else if(ameta->eType == type_is_propertylist) 
		//{
		//	std::vector<bstr_t>  bstrs = GetVectorString(value.c_str(), ";");
		//	std::vector<bstr_t> second(bstrs.size());
		//	transform (bstrs.begin(), bstrs.end(), second.begin(), appendsemicolon);
  //
		//	*(std::vector<bstr_t> *) ((char *) this + ameta->oFieldOffset) = second;

		//}
		//else if(ameta->eType == type_is_array)  // comma delimited string
		//{
		//	std::vector<bstr_t>  bstrs = GetVectorString(value.c_str());
		//	*(std::vector<bstr_t> *) ((char *) this + ameta->oFieldOffset) = bstrs;
		//}	
	}
}
void IObject::Delete(std::vector<IObjectPtr> * objects, int n)
{
	ATLASSERT(n<objects->size());
	objects->erase(objects->begin() + n);
}

void IObject::Delete() 
{ 
	//objects().erase(objects().begin()+i); 
	for(int i=0; i< objects().size(); i++)
		if(objects()[i].get()==this)
		{
			objects().erase(objects().begin() + i);
			return;
		}
} 
