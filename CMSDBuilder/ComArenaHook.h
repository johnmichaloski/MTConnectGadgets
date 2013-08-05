//
// ComArenaHook.h
//

#pragma once
#include <vector>
#import "C:\\Program Files\\Rockwell Software\\Arena\\Arena.exe"

class CArenaComHook
{
public:
	//CComPtr<IDispatch> _appdispatch;
	CComPtr<Arena::IArenaApp> _appdispatch;
	CComPtr<Arena::IModels> _arenamodels;
	CComPtr<Arena::IModules> _Modules;
	CComPtr<Arena::IModel> _mymodel;
	CComPtr<Arena::IConnections> _myconnections;
	std::vector<CComPtr<Arena::IModule>> _mymachines;
	CComPtr<Arena::IModule> _curmodule;
	std::vector<CComPtr<Arena::IModule>> _myparts;

	CArenaComHook(void);
	~CArenaComHook(void);
	void open();
	void quit() { if(_appdispatch !=NULL ) _appdispatch->Quit(); }

	CComPtr<Arena::IModule> CreateSeize(std::string label, int x, int y);
	CComPtr<Arena::IModule> CreateDelay(std::string label, int x, int y);
	CComPtr<Arena::IModule> CreateArrive(std::string label, int x, int y);
	//CCMSDIntegrator xml;

	void demo6();
	void demo7();
	//void JobShopBuilder(std::string filename);
	void JobShopBuilder(CCMSDIntegrator &xml);

	double _CapacityFactor;

};
