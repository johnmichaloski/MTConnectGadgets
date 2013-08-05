//
// SimpleReflection.h
//

#pragma once
#include <comdef.h>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "Config.h"

// From atlcom.h
//#ifdef  _WIN64
//#define offsetof(s,m)   (size_t)( (ptrdiff_t)&reinterpret_cast<const volatile char&>((((s *)0)->m)) )
//#else
//#define offsetof(s,m)   (size_t)&reinterpret_cast<const volatile char&>((((s *)0)->m))
//#endif


class IObject;
typedef boost::shared_ptr<IObject> IObjectPtr;


// this is the metadata I need for each field of the structure
class MyStructMeta {
public:
   char * pszFieldName;
   size_t oFieldOffset;
   size_t cbFieldSize;
   int    eType;
   std::vector<IObjectPtr>  * ptr;
   char * pszMenuName;
   MyStructMeta( char * _pszFieldName,
	   size_t _oFieldOffset,
	   size_t _cbFieldSize,
	   int    _eType, 
	   std::vector<IObjectPtr>  * pobjects=NULL, 
	   char * _pszMenuname="") :
   pszFieldName(_pszFieldName), oFieldOffset(_oFieldOffset), 
	   cbFieldSize(_cbFieldSize),   eType(_eType) ,
  	   ptr(pobjects),   pszMenuName(_pszMenuname) 
 {
   }
   MyStructMeta() {}
} ;

// these are the field types I need to handle.
enum MetaType {
  type_is_none=-1,
  type_is_int,
  type_is_char,
  type_is_string,
  type_is_bstr_t,
   type_is_date,
    type_is_time,
    type_is_datetime,
	type_is_propertylist,
	type_is_array,  // array of object identifiers - multilist 
	type_is_menu  // 1 selection list
};

// these macros help to emit the metadata
#define NUMELMS(ary)     (sizeof(ary)/(sizeof(ary)[0]))
#define FIELDOFF(tag,fld)  ((size_t)&(((tag *)0)->fld))
#define FIELDSIZ(tag,fld)  sizeof(((tag *)0)->fld)

// now we declare the metadata for the StructIWantToIterate structure

//#define METADATA(fld,as)  #fld, FIELDOFF(tag,fld), FIELDSIZ(tag,fld), as
#define	BEGIN_METADATA(X)\
	static  std::vector<IObjectPtr>  _objects;\
	virtual IObject * Create() { return new  X();  }\
	static IObject * CreateStatic() { return new  X();  }\
	virtual std::vector<IObjectPtr> & objects() { return _objects; }\
	virtual std::vector<IObjectPtr> * objectsPtr() { return &_objects; }\
	virtual bstr_t GetClassname() { return #X; }\
	typedef X _MetaDataClass; \
	virtual void InsertFromCopy(int i) \
	{ \
		X * toapart ( (X*) X().CreateSave<X>());\
		if(objects().size() < 2 || i >= objects().size()) return; \
		IObject * frompart = _objects[i].get();\
		toapart->Copy(frompart);\
	}\
virtual MyStructMeta ** GetMetaData()\
{\
	X _X;\
static const MyStructMeta * aMeta[] = { 

#define	IMPLEMENT_METADATA(X)\
	 std::vector<IObjectPtr>  X::_objects;\
	 int X##Nop() { IObject::PushObjectList(#X, &X::_objects,(IObject::CreatorFcn) &X::CreateStatic); return 0;}\
	 int X##initialize=X##Nop();



// e.g.,    MYFLD(foo, type_is_int), // expands to "foo", 0, sizeof(int), type_is_int
// e.g.,   MYFLD(bar, type_is_char),// expands to "bar", sizeof(int), 16, type_is_char
#define END_METADATA 0}; return (MyStructMeta **) &aMeta[0];} 

// as a virtual this leaks memory
#define STDFLD(fld,as)  new MyStructMeta( #fld, offsetof(_MetaDataClass,fld), sizeof(((_MetaDataClass *)0)->fld), as)

#define MENUFLD(fld,as,objref,name)  new MyStructMeta( #fld, offsetof(_MetaDataClass,fld), sizeof(((_MetaDataClass *)0)->fld), as, (std::vector<IObjectPtr>  * ) objref, name)


class IObject
{
public:
	
	static 	crp::Config config;
	std::vector<bstr_t> properties;
	std::vector<bstr_t> distributions;
	void AddProperty(std::string name, std::string value, std::string units, std::string description)
	{
		std::string prop=name+","+value+","+units+","+description;
		std::vector<bstr_t>::iterator it = find( properties.begin(), properties.end(), bstr_t(name.c_str()));
		if(it!=properties.end())
			(*it)=prop.c_str();
		else
			properties.push_back(prop.c_str());
	}

	typedef IObject *  (*CreatorFcn)();

	static std::vector<std::vector<IObjectPtr> *> & GetAllObjects() 
	{
		static  std::vector<std::vector<IObjectPtr> *> allobjects; 
		return allobjects; 
	}
	static std::vector<std::string> & GetAllClassnames() 
	{
		static  std::vector<std::string>  classnames; 
		return classnames; 
	}
	static std::vector<CreatorFcn> & GetAllCreators() 
	{
		static  std::vector<CreatorFcn>  creators; 
		return creators; 
	}
	static void PushObjectList(std::string name, std::vector<IObjectPtr> * objects, CreatorFcn fcn)
	{
		IObject::GetAllClassnames().push_back(name); 
		IObject::GetAllObjects().push_back(objects); 
		IObject::GetAllCreators().push_back(fcn); 
	}

	virtual bstr_t GetClassname(){return L"None";};
	virtual MyStructMeta ** GetMetaData(){return NULL;};
	MetaType GetType(int i);
	MetaType GetType(bstr_t name);
	std::string Dump();
	bstr_t GetDelimString(std::vector<bstr_t>, std::string delim=",");
	std::vector<bstr_t>  GetVectorString(bstr_t commastrs, std::string delim=",");
	static std::vector<std::string> GetList(std::string classname, std::string variable);

	int HeaderCount() { int cnt; 	MyStructMeta ** meta = this->GetMetaData(); for(cnt=0; meta[cnt]!=NULL; cnt++); return cnt; }
	std::vector<std::string> GetHeaders();
	std::string GetValue(std::string name);
	std::string GetPropertyName(std::string prop);
	std::string GetPropertyValue(std::string propname);
	std::string GetPropertyUnits(std::string propname);
	std::string GetPropertyDescription(std::string name);
	std::string GetProperty(int index, int field);

	std::string GetValue(int index);
	void SetValue(std::string name, std::string value);
	void SetValue(int index, std::string value);
	virtual std::vector<IObjectPtr> & objects() 
	{ 
		std::vector<IObjectPtr> *ptr = objectsPtr();
		return *ptr; 
	}
	virtual std::vector<IObjectPtr> * objectsPtr() 
	{  
		static  std::vector<IObjectPtr>  _objects; 
		return &_objects;   
	}
	//virtual IObject * Create() { return IObjectPtr(new IObject()).get(); }
	virtual IObject * Create() { return new  IObject();  }
	virtual void InsertFromCopy(int i){}
	int GetIndex (std::string name);
	template<typename X>
	static X * Create() {X * x = new X(); return x;  }
	template<typename X>
	static X * CreateSave() 
	{
		X * x = new X(); 
		x->objects().push_back((IObjectPtr) x); 
		return x;  
	}
	//IObject * Create() { _objects.push_back(IObjectPtr(new  X())); return _objects.back().get(); }
	IObject * Store() { objects().push_back((IObjectPtr) this); return objects().back().get(); }
	void Delete();
	static void Delete(std::vector<IObjectPtr> *, int n);
	//void Copy(int i) { _objects.erase(_objects+i); } 
	void Copy(IObject * from);

	template<typename X>
	static X * CreateCopy(X * x1) 
	{
		X * x2 = new X(); 
		x2->Copy(x1);
		return x2;  
	}
};

