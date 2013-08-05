//
// Sql2CMSDIntegrator.cpp
//

#include "StdAfx.h"
#include <algorithm>
#include "CMSDIntegrator.h"

#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

// Here is the complete Ol' Dirty Bastard function reference:
// http://msdn.microsoft.com/en-us/library/ms714562(VS.85).aspx

#pragma comment( lib, "odbc32.lib" )

HRESULT CHECK( SQLRETURN rc, char * msg, bool throwFailedExpection=false, bool printSucceededMsg=false  )
{
	if( SQL_SUCCEEDED( rc ) )
	{
		if( printSucceededMsg )  AtlTrace( "%s succeeded\n", msg ) ; 
		return S_OK ;
	}
	else
	{
		AtlTrace( "NO!!!  %s has FAILED!!\n", msg ) ;
		if(throwFailedExpection)
			throw std::exception((std::string(msg) + " exception").c_str());
		return E_FAIL ;
	}
}

void status( SQLSMALLINT handleType, SQLHANDLE theHandle, int line )
{
	SQLCHAR sqlState[6];
	SQLINTEGER nativeError;
	SQLCHAR msgStr[256];
	SQLSMALLINT overBy ; // the number of characters that msgStr buffer was TOO SHORT..

	// http://msdn.microsoft.com/en-us/library/ms716256(VS.85).aspx
	// This must be the WEIRDEST ERROR REPORTING FUNCTION I've EVER seen.
	// It requires 8 parameters, and its actually pretty .. silly
	// about the amount of state information it expects YOU to keep track of.

	// It isn't so much a "GetLastError()" function
	// as it is a "GetMeStatus( something very, very specific )" function.

	SQLRETURN retCode ;

	for( int i = 1 ; i < 20 ; i++ )
	{
		retCode = SQLGetDiagRecA(

			handleType,  // the type of object you're checking the status of
			theHandle,   // handle to the actual object you want the status of

			i, // WHICH status message you want.  The "Comments" section at the 
			// bottom of http://msdn.microsoft.com/en-us/library/ms716256(VS.85).aspx
			// seems to explain this part well.

			sqlState,    // OUT:  gives back 5 characters (the HY*** style error code)
			&nativeError,// numerical error number
			msgStr,      // buffer to store the DESCRIPTION OF THE ERROR.
			// This is the MOST important one, I suppose

			255,         // the number of characters in msgStr, so that
			// the function doesn't do a buffer overrun in case it
			// has A LOT to tell you
			&overBy      // again in case the function has A LOT to tell you,
			// the 255 character size buffer we passed might not be large
			// enough to hold the entire error message.  If that happens
			// the error message will truncate and the 'overBy' variable
			// will have a value > 0 (it will measure number of characters
			// that you 'missed seeing' in the error message).

			) ;

		if( CHECK( retCode, "SQLGetDiagRecA" ) )
		{
			AtlTrace( "LINE %d:  [%s][%d] %s\n", line, sqlState, nativeError, msgStr ) ;
		}
		else
		{
			// Stop looping when retCode comes back
			// as a failure, because it means there are
			// no more messages to tell you
			break ;
		}
	}
}

static std::string GetDDLType(MetaType type )
{
	switch (type)
	{
	case type_is_none: return "VARCHAR(255)";
	case type_is_int: return "INT(11)";
	case type_is_char: return "CHAR";
	case type_is_string: return "VARCHAR(255)";
	case type_is_bstr_t: return "VARCHAR(255)";
	case type_is_date: return "TIMESTAMP";
	case type_is_time: return "TIMESTAMP";
	case type_is_datetime: return "TIMESTAMP";
	case type_is_propertylist: return "CHAR(255)";
	case type_is_array: return "CHAR(255)";  // array of object identifiers - multilist 
	case type_is_menu: return "CHAR(255)";  // 1 selection list
	default:
		return "VARCHAR(255)";
	}
}

static std::string GetDDLDefault(MetaType type )
{
	switch (type)
	{
	case type_is_none: return "DEFAULT NULL";
	case type_is_int: return "DEFAULT 0";
	case type_is_char: return "DEFAULT ''";
	case type_is_string: return "DEFAULT ''";
	case type_is_bstr_t: return "DEFAULT ''";
	case type_is_date: return "";
	case type_is_time: return "";
	case type_is_datetime: return "";
	case type_is_propertylist: return "DEFAULT ''";
	case type_is_array: return "DEFAULT ''";  // array of object identifiers - multilist 
	case type_is_menu: return "DEFAULT ''";  // 1 selection list
	default:
		return "VARCHAR(255)";
	}
}
static std::string AddProperty(std::string & properties , std::string prop)
{
	static int propkey=1;
	std::vector<std::string> props = Tokenize(prop,";");
	std::string keystr;
	for(int i=0; i< props.size(); i++)
	{
		ReplaceAll(props[i],"None", "");
		if(props[i].size() < 1)
			props[i]=",,,";
		std::string key = StdStringFormat("%d", propkey++);;
		properties+= "INSERT INTO Properties VALUES (" ;
		properties+= key;
		std::vector<std::string> eachprop = Tokenize(props[i],",");
		for(int j=0; j< eachprop.size(); j++)
		{
			properties+= ",";
			properties+= "'"+ eachprop[j] + "'";
		}
		properties+= ");\n" ;
		keystr+=key + ",";
	}
	return keystr;
}
static std::string GetDDLValue(IObject * obj, int i , std::string & properties)
{
	MetaType type = obj->GetType(i);
	std::string value = obj->GetValue(i);
	if( value == "None")
		value = "";
	switch (type)
	{
	case type_is_none: return "DEFAULT NULL";
	case type_is_int: return value;
	case type_is_char: return "'"+ value + "'";
	case type_is_string: return "'"+ value + "'";
	case type_is_bstr_t: return "'"+ value + "'";
	case type_is_date: return Trim(value);
	case type_is_time: return Trim(value);
	case type_is_datetime: return Trim(value);
	case type_is_propertylist: return "'"+ AddProperty(properties , value) + "'";
	case type_is_array: return "'"+ value + "'";  // array of object identifiers - multilist 
	case type_is_menu: return  "'"+ value + "'";  // 1 selection list
	default:
		return  "'"+ value + "'";
	}
}

std::string CCMSDIntegrator::GenerateSchema(std::string schema) 
{
	std::stringstream buffer;
	std::string table;
	buffer << "CREATE SCHEMA IF NOT EXISTS `" << schema << "` DEFAULT CHARACTER SET latin1;"  << std::endl;
	buffer << "USE "<< schema << ";"  << std::endl ;
	schema="`"+schema+"`";

	buffer << std::endl <<   std::endl ;
	buffer << "DROP TABLE IF EXISTS " << schema << "." << "Properties" <<  ";" << std::endl;
	buffer << "CREATE  TABLE IF NOT EXISTS " << schema << "." << "Properties" << "(" << std::endl;
	buffer << "identifier  CHAR(255) NOT NULL,"<< std::endl;
	buffer << "name CHAR(255)  NOT NULL DEFAULT '',"<< std::endl;
	buffer << "value CHAR(255)NOT NULL DEFAULT '', "<< std::endl;
	buffer << "units CHAR(255) NULL DEFAULT '',"<< std::endl;
	buffer << "description CHAR(255) NULL DEFAULT '',"<< std::endl;
	buffer <<  std::endl << "PRIMARY KEY (`identifier`)" << std::endl;
	buffer << ") ENGINE=InnoDB DEFAULT CHARSET=utf8;" << std::endl;

	std::vector<IObject::CreatorFcn> & creators = IObject::GetAllCreators();
	for(int j=0; j< creators.size(); j++)
	{
		IObject::CreatorFcn fcn = creators[j];
		//Part * apart = (Part*) new Part();
		IObject * apart = fcn();
		table=apart->GetClassname(); // "`Part`";

		buffer << std::endl << std::endl;
		buffer << "-- -----------------------------------------------------" << std::endl;
		buffer << "-- Table " <<  schema << "." << table << std::endl;
		buffer << "-- -----------------------------------------------------" << std::endl;

		buffer << "DROP TABLE IF EXISTS "<< schema << "." << table <<  ";" << std::endl;
		buffer << "CREATE  TABLE IF NOT EXISTS "<< schema << "." << table << "(" << std::endl;

		std::vector<std::string> fields = apart->GetHeaders();
		for(int i=0; i< fields.size(); i++)
		{
			MetaType type = apart->GetType(i);
			std::string field = fields[i];
			ReplaceAll(field,".", "_");
			buffer << "`" << field << "` " << GetDDLType(type ) << " " ;
			buffer << (( fields[i]=="identifier")?  "NOT NULL " :  "NULL ");
			buffer << GetDDLDefault(type );
			if((i+1)!=fields.size()) buffer <<  ", " << std::endl;
		}

		if(std::find(fields.begin(), fields.end(), "identifier")!=fields.end())
			buffer <<  ", " << std::endl << "PRIMARY KEY (`identifier`)" << std::endl;


		buffer << ") ENGINE=InnoDB DEFAULT CHARSET=utf8;" << std::endl;
	}
	return buffer.str();
}

std::string CCMSDIntegrator::GenerateTableData(std::string schema) 
{
	std::stringstream buffer;
	std::string table;
	std::string properties;
	buffer << "USE "<< schema << ";"  << std::endl ;
	schema="`"+schema+"`";

	std::vector<std::vector<IObjectPtr> *> & allobjects = IObject::GetAllObjects();
	for(int j=0; j<allobjects.size(); j++)
	{
		std::vector<IObjectPtr> * objects = allobjects[j];
		for(int k=0; k< objects->size(); k++)
		{
			IObject * apart = objects->at(k).get();
			table=apart->GetClassname(); // "`Part`";

			buffer << "INSERT INTO " << schema << "." << table << " VALUES (" ;
			//	'7060',-6,0,0,0,0
			std::vector<std::string> fields = apart->GetHeaders();
			for(int jj=0; jj< fields.size(); jj++)
			{
				std::string value = GetDDLValue(apart, jj, properties) ; //apart->GetValue(jj);
				buffer << value;
				if((jj+1)!=fields.size()) buffer <<  "," ;
			}
			buffer << ");" << std::endl;
		}
	}

	buffer << std::endl << std::endl << properties;
	return buffer.str();
}

HRESULT CCMSDIntegrator::OpenSqlDatabase(std::string dbname)
{
	SQLRETURN retCode;
	try {
		retCode = SQLAllocHandle( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv ) ;
		CHECK( retCode, "allocate environment handle" ) ;

		retCode = SQLSetEnvAttr( hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0 ) ; 
		CHECK( retCode, "setting the environment attribute setting to ODBC version 3" ) ;

		CHECK( SQLAllocHandle( SQL_HANDLE_DBC, hEnv, &hConn ), "allocate handle" ) ;
		SQLCHAR* dsnName = (SQLCHAR*)dbname.c_str() ;  // MUST BE THE SAME
		SQLCHAR* userid = (SQLCHAR*)"root";
		SQLCHAR* password = (SQLCHAR*)"bingo";  // using a BLANK
		retCode = SQLConnectA(
			hConn,
			dsnName,  
			SQL_NTS,  // the DSN name is a NULL TERMINATED STRING, so "count it yourself"
			userid,
			SQL_NTS,  // userid is a null-terminated string 
			password,
			SQL_NTS   // password is a null terminated string  
			) ;
		if( CHECK( retCode, "SqlConnectA", false ) )
		{    
			status( SQL_HANDLE_DBC, hConn, __LINE__ ) ;
			return E_FAIL;
		}
	}
	catch(...)
	{

	}

	return S_OK;
}
// Only SQL_C_CHAR for now
std::string CCMSDIntegrator::GetData(SQLHSTMT  hStmt, int j)
{
	SQLRETURN retCode;
	char buf[256];
	SQLINTEGER numBytes;
	retCode = SQLGetData(
		hStmt,
		j,           // COLUMN NUMBER of the data to get
		SQL_C_CHAR,  // the data type that you expect to receive
		buf,         // the place to put the data that you expect to receive
		255,         // the size in bytes of buf (-1 for null terminator)
		&numBytes    // size in bytes of data returned
		) ;
	if( CHECK( retCode, "SQLGetData", false ) )
	{    
		status( SQL_HANDLE_DBC, hConn, __LINE__ ) ;
		return "";
	}

	buf[numBytes+1]=0;
	return buf;
}

void CCMSDIntegrator::GetAllProperties()
{
	SQLRETURN retCode;
	SQLSMALLINT numCols ;
	SQLLEN numRows ;
	SQLHSTMT hStmt = 0;
	std::map<std::string,std::string> cols;

	_sqlProperties.clear();

	retCode = CHECK(SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt), "SQLAllocHandle Statement Handle"); 
	retCode = CHECK(SQLExecDirect(hStmt, (SQLCHAR *) "SELECT * FROM `factory`.`properties`", SQL_NTS), "SQLExecDirect SELECT * FROM `factory`.`properties`");
	retCode = CHECK(SQLRowCount( hStmt, &numRows ) , "SQLRowCount");
	retCode = CHECK(SQLNumResultCols( hStmt, &numCols ), "SQLNumResultCols"); // SqlNumResultCols

	int bufferSize = 1024;
	SQLSMALLINT bufferLenUsed;
	SQLPOINTER* columnLabels = (SQLPOINTER *)malloc( sizeof(SQLPOINTER*) ); // allocate 1 column
	columnLabels[0] = (SQLPOINTER)malloc( bufferSize*sizeof(char) );  // reuse


	for (int i=0,retCode = SQLFetch(hStmt); retCode == SQL_SUCCESS; retCode = SQLFetch(hStmt),i++) 
	{
		cols.clear();
		for (int i = 0 ; i < numCols ; i++ ) 
		{			
			retCode = SQLColAttribute(hStmt, (SQLUSMALLINT)i + 1, SQL_DESC_LABEL, columnLabels[0], (SQLSMALLINT)bufferSize, &bufferLenUsed, NULL);
			std::string value = GetData(hStmt, i+1);
			if(value.size() < 1) value = "None";
			cols[(char *) columnLabels[0]] = value;  			
		}

		PropertyElement prop; 
		if(cols["identifier"]=="None")
			continue;
		prop.name = cols["name"].c_str();
		prop.value = cols["value"].c_str();
		prop.units = cols["units"].c_str();
		prop.description = cols["description"].c_str();
		_sqlProperties[cols["identifier"]]=prop;
	}
	SQLFreeHandle( SQL_HANDLE_STMT, hStmt ) ;
}

/*    SQLColAttribute (handleSTMT, howmanycols, SQL_DESC_CONCISE_TYPE,
SQL_NULL, 0, SQL_NULL, &coltype);*/

void CCMSDIntegrator::LoadCMSDFromSql()
{

	SQLRETURN retCode;
	SQLSMALLINT numCols ;
	SQLLEN numRows ;
	SQLHSTMT hStmt = 0;
	std::vector<std::string> colNames;

	int bufferSize = 1024;
	SQLSMALLINT bufferLenUsed;
	SQLPOINTER* columnLabels = (SQLPOINTER *)malloc( sizeof(SQLPOINTER*) );
	columnLabels[0] = (SQLPOINTER)malloc( bufferSize*sizeof(char) );

	GetAllProperties();

	static const IObject::CreatorFcn arr[] = {&ProcessPlan::CreateStatic,&Process::CreateStatic,
	&Resource::CreateStatic,&Cell::CreateStatic, &Part::CreateStatic,&Job::CreateStatic,
	&Calendar::CreateStatic,&Shift::CreateStatic,&Schedule::CreateStatic,&Distribution::CreateStatic};
	std::vector<IObject::CreatorFcn>  creators(arr, arr + sizeof(arr) / sizeof(arr[0]));

	//std::vector<IObject::CreatorFcn> & creators = IObject::GetAllCreators();
	for(int n=0; n< creators.size(); n++)
	{
		IObject::CreatorFcn fcn = creators[n];
		IObject * apart = fcn();
		std::string  table=apart->GetClassname(); // "`Part`";
		//	std::string table = "part";
		table = MakeLower(table);


		retCode = CHECK(SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt), "SQLAllocHandle Statement Handle"); 
		retCode = SQLExecDirect(hStmt, (SQLCHAR *) StdStringFormat("SELECT * FROM `factory`.`%s`", table.c_str()).c_str(), SQL_NTS);

		retCode = CHECK(SQLRowCount( hStmt, &numRows ), "SQLRowCount");  ;
		retCode = CHECK(SQLNumResultCols( hStmt, &numCols ), "SQLNumResultCols "); ; // SqlNumResultCols


		for (int i = 0 ; i < numCols ; i++ ) 
		{
			CHECK( SQLColAttribute(hStmt, (SQLUSMALLINT)i + 1, SQL_DESC_LABEL, columnLabels[0], (SQLSMALLINT)bufferSize, &bufferLenUsed, NULL), "SQLColAttribute");
			colNames.push_back((char *) columnLabels[0]);
		}

		for (int i=0,retCode = SQLFetch(hStmt); retCode == SQL_SUCCESS; retCode = SQLFetch(hStmt),i++) 
		{
			IObject * apart = fcn()->Create()->Store();
			for(int j=0; j< numCols; j++)
			{
				std::string value = GetData(hStmt,  j+1);
				if(colNames[j]=="properties")
				{
					std::vector<std::string> items = TrimmedTokenize(value, ",");
					for(int k=0; k<items.size(); k++)
					{
						if(	_sqlProperties.find(items[k]) == _sqlProperties.end()	)
							continue;

						apart->properties.push_back( _sqlProperties[items[k]].name+ "," 
							+ _sqlProperties[items[k]].value + "," + 
							_sqlProperties[items[k]].units   + "," + 
							_sqlProperties[items[k]].description + ";" );
					}

					continue;
				}
				if(value.size() < 1) value = "None";
				apart->SetValue(colNames[i], value);
			}
		}
	}
	SQLFreeHandle( SQL_HANDLE_STMT, hStmt ) ;
}
HRESULT CCMSDIntegrator::CloseSqlDatabase()
{
	SQLFreeHandle( SQL_HANDLE_DBC, hConn ) ;
	SQLFreeHandle( SQL_HANDLE_ENV, hEnv ) ;

	return S_OK;
}

