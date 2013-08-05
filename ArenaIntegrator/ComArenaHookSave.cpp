#include "StdAfx.h"
#include "ComArenaHook.h"
#include "StdStringFcn.h"
#include "ATLComTime.h"
#include "ResourceIntegrator.h"

////////////////////////////////////////////////////
CComArenaHook::CComArenaHook(void)
{
}

CComArenaHook::~CComArenaHook(void)
{
}

void CComArenaHook::PutData(CComPtr<Arena::IModule>, bstr_t operandName,  _bstr_t operandValue)
{


}
/**
 Operand Name                       Text
   ---------------------------------- --------------------------------
   Station                                                              
   StSet                                                                
   Batch                              Batch Size                        
   Offset                             First Creation                    
   Interval                           Time Between                      
   Max                                Max Batches                       
   Mark                               Mark Time Attribute               
   SzNoneSG                                                             
   ReqSG                                                                
   AccSG                                                                
   WhereSG                                                              
   Statn                              Station                           
   StExpr                             Expression                        
   Move                               Route Time                        
   Connect                            Next Label                        
   StationSG                                       
*/
CComPtr<Arena::IModule> CComArenaHook::CreateArrive(std::string label, int x, int y)
{
	USES_CONVERSION;
	CComPtr<Arena::IModule> arrive = _Modules->Create(_bstr_t(L"Common"), _bstr_t(L"Arrive"), x, y);
	arrive->PutData ( _bstr_t(L"Station"), _bstr_t(A2W(label.c_str()))); 
	arrive->PutData ( _bstr_t(L"Batch"), _bstr_t("4")); 
	arrive->PutData ( _bstr_t(L"Interval"), _bstr_t("6")); 
	arrive->PutData ( _bstr_t(L"Mark"), _bstr_t("ArrTime")); 
	
	return arrive;
}

/*
 Operands Contained in Dialog 'SeizeDB':

   Operand Name                       Text
   ---------------------------------- --------------------------------
   Pri                                Priority                          
   QLabel                             Queue Label                       
   Label                              Label                             
   Next                               Next Label                        

   Operands Contained in Repeat Group 'SeizeRG':

   Operand Name                       Text
   ---------------------------------- --------------------------------                
   SG                                 Resource Name                     
   Res                                Resource                          
   Set                                Resource Set                      
   Rule                               Rule                              
   Att                                Store Index in Att                
   Member                             Set Index                         
   Static                             Static                            
   Attr                               Attribute                         
   Expr                               Expression                        
   Qty                                Seize Quantity                    
   ResState                           Resource State                    
                  
   */
CComPtr<Arena::IModule> CComArenaHook::CreateSeize(std::string label, int x, int y)
{
	USES_CONVERSION;
	CComPtr<Arena::IModule> seize = _Modules->Create(_bstr_t(L"Support"), _bstr_t(L"Seize"), x, y);
	seize->PutData ( _bstr_t(L"Label"), _bstr_t(A2W(label.c_str()))); //Delay Label

	//_modules[0]->PutData ( _bstr_t(L"Next Label"), _bstr_t(L"CNC2"));
	seize->PutData ( _bstr_t(L"SG(1)"), _bstr_t(L"Specific Member"));
	seize->PutData ( _bstr_t(L"SG(1)"), _bstr_t(L"Specific Member"));
	return seize;
}

/**
 Operand Name                       Text
   ---------------------------------- --------------------------------
   DelayType                          Delay Type   - Expression, Static, Attribute                      
   Exp                                Expression                        
   Static                             Static                            
   Att                                Attribute                         
   Storage                            Storage                           
   Label                              Label                             
   Next                               Next Label                        
*/
CComPtr<Arena::IModule> CComArenaHook::CreateDelay(std::string label, int x, int y)
{	
	USES_CONVERSION;
	CComPtr<Arena::IModule> delay = _Modules->Create(_bstr_t(L"Support"), _bstr_t(L"Delay"), x,y);
	delay->PutData ( _bstr_t(L"Label"), _bstr_t(A2W(label.c_str()))); //Delay Label
	delay->PutData ( _bstr_t(L"DelayType"), _bstr_t(L"Expression")); //Delay Type
 	//delay->PutData ( _bstr_t(L"Exp"), _bstr_t(L"DelayTime(SetIndex)")); // Expression
	delay->PutData ( _bstr_t(L"Exp"), _bstr_t(L"EXPO( Mean )"));
	return delay;
}

void CComArenaHook::open()
{
	HRESULT hr;
	//{F9FC9A7E-7887-4c25-A02C-7808998476D7}
	try 
	{
	_appdispatch.CoCreateInstance(L"Arena.Application"); // works
	_appdispatch->Activate();
	_arenamodels=_appdispatch->Models;
	_mymodel=_arenamodels->Add();
	//_mymodel->SaveAs (bstr_t(L"MTConnect"));
	//SetTypedProperty<Arena::IModelPtr>(_mymodel, _bstr_t("Name"), _bstr_t("MTConnect"));
	_Modules=_mymodel->Modules;
	_myconnections =_mymodel->Connections;

	
	// Define Parts as "Entites"
	CComPtr<Arena::IModule> entity=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Entity"), 100, 400);
	entity->PutData ( _bstr_t(L"Name"), _bstr_t(L"Bracket"));
	entity=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Entity"), 100, 400);
	entity->PutData ( _bstr_t(L"Other"), _bstr_t(L"3")); // index into cycle time array
	entity->PutData ( _bstr_t(L"Name"), _bstr_t(L"Shim"));
	entity->PutData ( _bstr_t(L"Other"), _bstr_t(L"2")); // index into cycle time array

	CComPtr<Arena::IModule> batch=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Batch"), 900, 400);
	batch->PutData ( _bstr_t(L"Name"), _bstr_t(L"JobsTable"));
	batch->PutData ( _bstr_t(L"Batch Size"), _bstr_t(L"1"));

	// Create Parts
	CComPtr<Arena::IModule> create=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Create"), 100, 400);
	create->PutData ( _bstr_t(L"Name"), _bstr_t(L"BracketWorkOrder"));
	create->PutData ( _bstr_t(L"Max Batches"), _bstr_t(L"100"));
	create->PutData ( _bstr_t(L"Entity Type"), _bstr_t(L"Bracket"));
	_myparts.push_back(create);
	
	_myconnections->Create(create,batch);

	create=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Create"), 100, 400+600);
	create->PutData ( _bstr_t(L"Name"), _bstr_t(L"ShimWorkOrder"));
	create->PutData ( _bstr_t(L"Max Batches"), _bstr_t(L"200"));
	create->PutData ( _bstr_t(L"Entity Type"), _bstr_t(L"Shim"));
	_myparts.push_back(create);
	_myconnections->Create(create,batch);


	create=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Create"), 100, 400+1200);
	create->PutData ( _bstr_t(L"Name"), _bstr_t(L"BodyJointWorkOrder"));
	create->PutData ( _bstr_t(L"Max Batches"), _bstr_t(L"300"));
	create->PutData ( _bstr_t(L"Entity Type"), _bstr_t(L"BodyJoint"));
	_myparts.push_back(create);
	_myconnections->Create(create,batch);	

	CComPtr<Arena::IModule> dispose=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Dispose"), 4800, 400);
	dispose->PutData ( _bstr_t(L"Name"), _bstr_t(L"Inspection Holding Area"));

	CComPtr<Arena::IModule> decide=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Decide"), 1800, 400);
	decide->PutData ( _bstr_t(L"Name"), _bstr_t(L"JobAllocation"));

	bstr_t type = decide->GetData( _bstr_t(L"Type"));
	type = decide->GetData( _bstr_t(L"Percent True"));
	type = decide->GetData( _bstr_t(L"TypeNamed"));
	decide->PutData ( _bstr_t(L"Type"), _bstr_t(L"NWith"));

	int N=4;
	for(int j=0; j< N; j++)
	{
		std::string name = StdStringFormat("CNC%d",j+1);
		std::string percent = StdStringFormat("%4.2f", (double) 100.0/N);
		std::string percenttrue = StdStringFormat("N Percent True(%d)", j+1);
		std::string machine = StdStringFormat("Machine%d",j+1);

		CComPtr<Arena::IModule> create1=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Process"), 3150, 0+j*600);
		CComPtr<Arena::IModule> resource1=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Resource"), 3150, 0+j*600);

		_mymachines.push_back(create1);

		resource1->PutData ( _bstr_t(L"Name"), _bstr_t(machine.c_str()));
		resource1->PutData ( _bstr_t(L"Capacity"), _bstr_t("1"));

		create1->PutData ( _bstr_t(L"Name"), _bstr_t(name.c_str()));
		create1->PutData ( _bstr_t(L"Action"), _bstr_t(L"SDR"));

		create1->PutData ( _bstr_t(L"Resource Type(1)"), _bstr_t(L"Resource"));
		create1->PutData ( _bstr_t(L"Resource Name(1)"), _bstr_t(machine.c_str()));
		create1->PutData ( _bstr_t(L"Quantity(1)"), _bstr_t("1"));

		decide->PutData ( _bstr_t(percenttrue.c_str()), _bstr_t(percent.c_str()));

		// Connections
		_myconnections->Create(decide, create1,_bstr_t(L"N Next Label Yes") , vtMissing, j+1);
		_myconnections->Create(create1,dispose) ; 
	}

	_myconnections->Create(batch,decide);
	_myconnections->Create(decide,dispose);

	// Add clock
	COleDateTime t1 = COleDateTime::GetCurrentTime();
	CComPtr<Arena::IStatusDates> dates = _mymodel->StatusDates;
	CComPtr<Arena::IStatusClocks> clocks =  _mymodel->StatusClocks;
    CComPtr<Arena::IStatusDate> date =  dates->Create (
        2000,
        -900,
        4050,
        -450,
        Arena::smDateDisplayText, // enum smDateDisplayType dateType,
        Arena::smDateFormatMonthDayYear, // enum smDateFormatType DateFormat,
        Arena::smDateUnitSecond, // enum smDateUnitType dateUnits,
        t1.GetMonth(),
        t1.GetDay(),
        t1.GetYear(),
        t1.GetHour(),
        t1.GetMinute(),
        t1.GetSecond(),
        0,
        0xFF0000, // blue background
		0xFFFFFF, // font color
		_bstr_t(L"Microsoft Sans Serif" ));
	
	clocks->Create(
		4050, 
		-900,
		5800,
		-450,
		VARIANT_TRUE,
		VARIANT_FALSE,
		60.0,
		0,
		0,
		0,
		0,
		0xFF0000, // blue background
		0xFFFFFF );

	// Remove entity 1 which is automatically created This will find it.
	long index = _Modules->FindByData(_bstr_t("Name"), _bstr_t("Entity 1"),1);
	CComPtr<Arena::IModule> finder =_Modules->Item[index];
	// Dont Create last part, replace Entity 1 with this one.
	//entity=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Entity"), 100, 400);
	finder->PutData ( _bstr_t(L"Name"), _bstr_t(L"BodyJoint"));
	finder->PutData ( _bstr_t(L"Other"), _bstr_t(L"1")); // index into cycle time array

	/*int n = _Modules->Count;
	for(int k=1; k<= n; k++)
	{
		CComPtr<Arena::IModule> finder =_Modules->Item[k];
		bstr_t name = finder->GetData(_bstr_t(L"Name"));
		if(name == _bstr_t(L"Entity 1"))
			break;
	}*/

	CComPtr<Arena::IShapes> shapes =_mymodel->Shapes;
	shapes->CreateText(1000  , -1200,_bstr_t(L"Job Shop Capacity Discrete Event Simulation"),
		_bstr_t(L"Times New Roman"),24 * 12,0,VARIANT_TRUE,VARIANT_FALSE,VARIANT_FALSE );

	// BodyJoint=1
	// Bracket=2
	// Shim=3
	for(int i=0; i< _mymachines.size(); i++)
	{
		// Simulate cycle time per part in each machine
		_mymachines[i]->PutData ( _bstr_t("DelayType"), _bstr_t("Expression"));
		_mymachines[i]->PutData ( _bstr_t("Expression"), _bstr_t(StdStringFormat("(Entity.Type  == %d) * 10 + (Entity.Type  ==  %d) * 10 + (Entity.Type  ==  %d) *  10", 1,2,3).c_str()));
		_mymachines[i]->PutData ( _bstr_t("Units"), _bstr_t("Minutes"));
	}

	// Define cost function variables
	CComPtr<Arena::IModule> var=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Variable"), 00, 0);
	var->PutData ( _bstr_t("Name"), _bstr_t("Modules"));
	var->PutData ( _bstr_t("Rows"), _bstr_t(StdStringFormat("%d", _mymachines.size()).c_str()));
	var->PutData ( _bstr_t("Columns"), _bstr_t("1"));
	var->PutData ( _bstr_t("Data Type"), _bstr_t("String"));
	
	for(int i=0; i< _mymachines.size(); i++)
	{
		bstr_t name = 	_mymachines[i]->GetData ( _bstr_t("Name"));
		name = "\"" + name + "\"";
		var->PutData ( _bstr_t(StdStringFormat("Initial Value(%d)(1)", i+1).c_str()), name);
		//var->PutData ( _bstr_t("Initial Value(2)(1)"), _bstr_t("32"));
		//var->PutData ( _bstr_t("Initial Value(3)(1)"), _bstr_t("33"));
		//var->PutData ( _bstr_t("Initial Value(4)(1)"), _bstr_t("34"));
	}

	// Add variables
	//var=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Variable"), 00, 0);
	//var->PutData ( _bstr_t("Name"), _bstr_t("TSTART"));

	_mymodel->ProjectDescription=_bstr_t(L"Simple Job Shop contains 4 machines and 3 parts. 24/7 shifts");
	_mymodel->ProjectTitle=_bstr_t(L"Estimating Job Shop Capacity");;
	_mymodel->HoursPerDay=_bstr_t(L"8");
	// note, usuing this will continue creating brackets until shims and body joints are both > 200
	//_mymodel->TerminatingCondition= _bstr_t(L"(EntitiesOut(BodyJoint) > 200 ) * (EntitiesOut(Bracket)>100) * (EntitiesOut(Shim) >200)");

	CComPtr<Arena::IStatusVariables> variables = _mymodel->StatusVariables;
	CComPtr<Arena::IStatusVariable> variable = variables->Create(4950 , 1050,  5800,  700 ,
		bstr_t("(CalDayOfYear(TNOW)-CalDayOfYear(0))  * 3"),
		 bstr_t("######"),VARIANT_FALSE, 0xFF0000,0xFF0000,0xFFFFFF,bstr_t("Times New Roman"));
	variable->UseTitle = VARIANT_TRUE;
	variable->PutTitleText("Shifts to complete work");
	variable->PutTitlePercentHeight(50);

#if 0
	// CalMonth(TNOW), CalDayOfMonth(TNOW), CalYear(TNOW), CalHour(TNOW), CalMinute(TNOW), CalSecond(TNOW);
	bstr_t startdatetime = _mymodel->StartDateTime ;
	CComPtr<Arena::ISIMAN> siman = _mymodel->SIMAN;


	_mymodel->Go(Arena::smGoReturn); 
	double dRunTime;
	double dTime = siman->CalendarDateToBaseTime (2012, 6, 23);
	while ( _mymodel->State == Arena::smStateRunning)
	{
		dRunTime = siman->RunCurrentTime;
		::Sleep(1000);
	}
	// If the ending time is defaulted, TFIN returns a large value (1.0E+20). 
	long day0 = siman->CalendarDayOfYear (0);
	long dayn = siman->CalendarDayOfYear (dRunTime);
#endif


	// Quit Arena
	//_appdispatch->Quit(); // works
	}
	catch(...)
	{
		OutputDebugString("CoCreateInstance Arena.Application failed\n");

	}

}

void CComArenaHook::demo6()
{
	HRESULT hr;
	try 
	{
		_appdispatch.CoCreateInstance(L"Arena.Application"); // works
		_appdispatch->Activate();
		_arenamodels=_appdispatch->Models;
		_mymodel=_arenamodels->Add();

		_Modules=_mymodel->Modules;
		_myconnections =_mymodel->Connections;
		
		
		CComPtr<Arena::IModule> var=_Modules->Create(_bstr_t(L"AdvancedTransfer"), _bstr_t(L"Sequence"), 00, 0);

		// Sequence
		//Part1ProcessPlan
		var->PutData ( _bstr_t("Name"), _bstr_t("Part1ProcessPlan"));
		for(int i=0; i< 4; i++)
		{
			_bstr_t timings[] = { _bstr_t(L"TRIA(6,8,10)"),_bstr_t("TRIA(5,8,10)"),_bstr_t("TRIA(5,8,10)"),_bstr_t("TRIA(15,20,25)")};
			_bstr_t order[] = {_bstr_t(L"1"),  _bstr_t(L"2"), _bstr_t(L"3"), _bstr_t(L"4")}; 
			CString n = StdStringFormat("%d",i+1).c_str();
			var->PutData ( _bstr_t(StdStringFormat("Station(%d)",i+1).c_str()), _bstr_t("Cell"+order[i]));
			var->PutData ( _bstr_t("SG(1,"+n+")"), _bstr_t("Attribute"));
			var->PutData ( _bstr_t("Att(1,"+n+")"), _bstr_t("ProcessTime"));
			var->PutData ( _bstr_t("Value(1,"+n+")"), _bstr_t(timings[i]));
		}
		var->PutData ( _bstr_t("Station(5)"), _bstr_t("ExitSystem"));
		
		//Part2ProcessPlan
		var=_Modules->Create(_bstr_t(L"AdvancedTransfer"), _bstr_t(L"Sequence"), 00, 0);
		var->PutData ( _bstr_t("Name"), _bstr_t("Part2ProcessPlan"));		
		for(int i=0; i< 5; i++)
		{
			_bstr_t timings[] = { _bstr_t("TRIA(11,13,15)"),_bstr_t("TRIA(4,6,8)"),_bstr_t("TRIA(15,18,21)"),_bstr_t("TRIA(6,9,12)"),_bstr_t("TRIA(27,33,39)")};
			_bstr_t order[] = {_bstr_t(L"1"),  _bstr_t(L"2"), _bstr_t(L"4"), _bstr_t(L"2"),_bstr_t(L"3")}; 
			CString n = StdStringFormat("%d",i+1).c_str();
			var->PutData ( _bstr_t(StdStringFormat("Station(%d)",i+1).c_str()), _bstr_t("Cell"+order[i]));
			var->PutData ( _bstr_t("SG(1,"+n+")"), _bstr_t("Attribute"));
			var->PutData ( _bstr_t("Att(1,"+n+")"), _bstr_t("ProcessTime"));
			var->PutData ( _bstr_t("Value(1,"+n+")"), _bstr_t(timings[i]));
		}
		var->PutData ( _bstr_t("Station(6)"), _bstr_t("ExitSystem"));

		// Part3ProcessPlan
		var=_Modules->Create(_bstr_t(L"AdvancedTransfer"), _bstr_t(L"Sequence"), 00, 0);
		var->PutData ( _bstr_t("Name"), _bstr_t("Part3ProcessPlan"));		
		for(int i=0; i< 3; i++)
		{
			_bstr_t timings[] = { _bstr_t(L"TRIA(7,9,11)"),_bstr_t("TRIA(7,10,13)"),_bstr_t("TRIA(18,23,28)")};
			_bstr_t order[] = {_bstr_t(L"2"),  _bstr_t(L"1"), _bstr_t(L"3")}; 
			CString n = StdStringFormat("%d",i+1).c_str();
			var->PutData ( _bstr_t(StdStringFormat("Station(%d)",i+1).c_str()), _bstr_t("Cell"+order[i]));
			var->PutData ( _bstr_t("SG(1,"+n+")"), _bstr_t("Attribute"));
			var->PutData ( _bstr_t("Att(1,"+n+")"), _bstr_t("ProcessTime"));
			var->PutData ( _bstr_t("Value(1,"+n+")"), _bstr_t(timings[i]));
		}
		var->PutData ( _bstr_t("Station(4)"), _bstr_t("ExitSystem"));

		{
			CComPtr<Arena::IModule> var=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Variable"), 00, 0);
			var->PutData ( _bstr_t("Name"), _bstr_t("Factor"));
			var->PutData ( _bstr_t("Rows"), _bstr_t(L"2"));
			//var->PutData ( _bstr_t("Data Type"), _bstr_t("String"));
			var->PutData ( _bstr_t("Initial Value(1)"), _bstr_t(L"0.8"));
			var->PutData ( _bstr_t("Initial Value(2)"), _bstr_t(L"1.0"));

			var=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Variable"), 00, 0);
			var->PutData ( _bstr_t("Name"), _bstr_t("TransferTime"));
			var->PutData ( _bstr_t("Initial Value"), _bstr_t(L"2"));
		}

		{
			CComPtr<Arena::IModule> set=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Set"), 00, 0);
			set->PutData ( _bstr_t("Name"), _bstr_t(L"Cell3Machines"));
			set->PutData ( _bstr_t("Type"), _bstr_t(L"Resource"));
			set->PutData ( _bstr_t("Resource Name(1)"), _bstr_t(L"Cell3New"));
			set->PutData ( _bstr_t("Resource Name(2)"), _bstr_t(L"Cell3Old"));

			set=_Modules->Create(_bstr_t(L"AdvancedProcess"), _bstr_t(L"Advanced Set"), 00, 0);
			set->PutData ( _bstr_t("Name"), _bstr_t(L"PartSequence"));
			set->PutData ( _bstr_t("Type"), _bstr_t(L"Other"));
			set->PutData ( _bstr_t("Other(1)"), _bstr_t(L"Part1ProcessPlan"));
			set->PutData ( _bstr_t("Other(2)"), _bstr_t(L"Part2ProcessPlan"));
			set->PutData ( _bstr_t("Other(3)"), _bstr_t(L"Part3ProcessPlan"));

			set=_Modules->Create(_bstr_t(L"Common"), _bstr_t(L"Sets"), 00, 0);
			set->PutData ( _bstr_t("togpic"), _bstr_t(L"Yes"));  // Or Pictures
			set->PutData ( _bstr_t("PSet(1)"), _bstr_t(L"Parts"));  
			set->PutData ( _bstr_t("Picture(1,1)"), _bstr_t(L"Part 1"));  
			set->PutData ( _bstr_t("Picture(2,1)"), _bstr_t(L"Part 2")); 
			set->PutData ( _bstr_t("Picture(3,1)"), _bstr_t(L"Part 3")); 

			set=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Set"), 00, 0);
			set->PutData ( _bstr_t("Name"), _bstr_t(L"PartCycleTimes"));  
			set->PutData ( _bstr_t("Type"), _bstr_t(L"Tally"));
			set->PutData ( _bstr_t("Tally Name(1)"), _bstr_t(L"Part 1 Cycle Time"));
			set->PutData ( _bstr_t("Tally Name(2)"), _bstr_t(L"Part 2 Cycle Time"));
			set->PutData ( _bstr_t("Tally Name(3)"), _bstr_t(L"Part 3 Cycle Time"));

			_mymodel->ProjectTitle=_bstr_t(L"Small Manufacturing System");
			_mymodel->ReplicationLength = _bstr_t("2000");

		}
		CComPtr<Arena::IModule> arrive=_Modules->Create(_bstr_t(L"Common"), _bstr_t(L"Arrive"), 0, 0);
		arrive->PutData ( _bstr_t("Interval"), _bstr_t(L"EXPO(13)"));
		arrive->PutData ( _bstr_t("Batch"), _bstr_t(L"1"));
		arrive->PutData ( _bstr_t("Move"), _bstr_t(L"TransferTime"));
		arrive->PutData ( _bstr_t("WhereSG"), _bstr_t(L"Seq"));

		

		arrive->PutData ( _bstr_t("AssignSG(1)"), _bstr_t(L"Attribute"));
		arrive->PutData ( _bstr_t("Att(1)"), _bstr_t(L"PartIndex"));
		arrive->PutData ( _bstr_t("Value(1)"), _bstr_t(L"DISC(.26,1,.74,2,1.0,3)"));

		arrive->PutData ( _bstr_t("AssignSG(2)"), _bstr_t(L"Other"));
		arrive->PutData ( _bstr_t("Other(2)"), _bstr_t(L"Sequence"));
		arrive->PutData ( _bstr_t("Value(2)"), _bstr_t(L"PartSequence(PartIndex)"));




		CComPtr<Arena::IModule> server;
		for(int i=0; i<3; i++)
		{
			int j[] = {1,2,4};
			int k = j[i];
			bstr_t n = StdStringFormat("%d",k).c_str();
			int x[] = { 0, 0, 0};
			int y[] = { 0, 700, 2100};
			server=_Modules->Create(_bstr_t(L"Common"), _bstr_t(L"Server"), x[i], y[i]);
			server->PutData ( _bstr_t("Label"), _bstr_t(L"Cell"+n));
			server->PutData ( _bstr_t("Station"), _bstr_t(L"Cell"+n));
			server->PutData ( _bstr_t("Res"), _bstr_t(L"Cell"+n+"_R"));
			server->PutData ( _bstr_t("RouteTime"), _bstr_t(L"TransferTime"));
			server->PutData ( _bstr_t("Cap"), _bstr_t(L"1"));
			server->PutData ( _bstr_t("WhereSG"), _bstr_t(L"Seq"));
			server->PutData ( _bstr_t("Delay"), _bstr_t(L"ProcessTime"));
		}

		bstr_t n = L"3";
		server=_Modules->Create(_bstr_t(L"Common"), _bstr_t(L"AdvServer"), 0, 1400);
		server->PutData ( _bstr_t("Label"), _bstr_t(L"Cell"+n));
		server->PutData ( _bstr_t("Station"), _bstr_t(L"Cell"+n));
		server->PutData ( _bstr_t("ResSG"), _bstr_t(L"Resource Set"));
		server->PutData ( _bstr_t("Set"), _bstr_t(L"Cell3Machines"));
		server->PutData ( _bstr_t("Move"), _bstr_t(L"TransferTime"));
		server->PutData ( _bstr_t("Cap"), _bstr_t(L"1"));
		server->PutData ( _bstr_t("WhereSG"), _bstr_t(L"Seq"));
		server->PutData ( _bstr_t("Delay"), _bstr_t(L"ProcessTime*Factor(Index)"));
		server->PutData ( _bstr_t("SetAtt"), _bstr_t(L"Index"));



		
		server=_Modules->Create(_bstr_t(L"Common"), _bstr_t(L"Resource"), 700, 1400);
		server->PutData ( _bstr_t("Server"), _bstr_t(L"Cell3New"));
		server=_Modules->Create(_bstr_t(L"Common"), _bstr_t(L"Resource"), 700, 2100);
		server->PutData ( _bstr_t("Server"), _bstr_t(L"Cell3Old"));
	
		server=_Modules->Create(_bstr_t(L"Common"), _bstr_t(L"Depart"), 1400, 1400);
		server->PutData ( _bstr_t("Station"), _bstr_t(L"ExitSystem"));
		server->PutData ( _bstr_t("TSG"), _bstr_t(L"Tally Set Member"));
		server->PutData ( _bstr_t("TSet"), _bstr_t(L"PartCycleTimes"));
		server->PutData ( _bstr_t("TMem"), _bstr_t(L"PartIndex"));
		server->PutData ( _bstr_t("Int"), _bstr_t(L"EnterTime"));
		
		//CComPtr<Arena::IEntityPictures> pictures = _mymodel->GetEntityPictures ( );
		//CComPtr<Arena::IEntityPicture>pict = pictures->Create(0,0);
		//CComPtr<Arena::IEntityPictureStates>states = pict->States;
		//CComPtr<Arena::IEntityPictureState>state = states->Item
		//state->Name=bstr_t("Part1");
		//state->PictureID=bstr_t("Shape.Circle.Blue");


		CResourceIntegrator xml;
		xml.ReadCmsdXmlFile((::ExeDirectory() + "..\\Examples\\ResourceAllocation.xml").c_str());
		// Create resources
		for(int i=0; i< xml.resources.size(); i++)
		{
			server=_Modules->Create(_bstr_t(L"Common"), _bstr_t(L"Resource"), 700, i * 700);
			server->PutData ( _bstr_t("Server"), xml.resources[i].name);
		}

		for(int i=0; i< xml.cells.size(); i++)
		{
			CComPtr<Arena::IModule> set=_Modules->Create(_bstr_t(L"BasicProcess"), _bstr_t(L"Set"), 00, 0);
			set->PutData ( _bstr_t("Name"), _bstr_t(xml.cells[i].name));
			set->PutData ( _bstr_t("Type"), _bstr_t(L"Resource"));
			for(int j=0; j< xml.cells[i].resourceIds.size(); j++)
			{
				Resource r = xml.FindResource(xml.cells[i].resourceIds[j]);
				bstr_t n = StdStringFormat("%d", j+1).c_str();
				set->PutData ( _bstr_t("Resource Name("+n+")"), _bstr_t(r.name));
			}
		}
	}
	catch(...)
	{
		OutputDebugString("CoCreateInstance Arena.Application failed\n");

	}
}