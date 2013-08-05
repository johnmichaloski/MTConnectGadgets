//
// C:\Program Files\NIST\proj\MTConnect\Nist\MTConnectGadgets\CMSDCommandCell\CMSDCommandCell\StateModel.h
//
#pragma once
#include <boost/thread/thread.hpp>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/lambda/bind.hpp"
#include <boost/function.hpp> 
#include <boost/timer.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp> 
#include <boost/timer.hpp>


#define BOOST_CB_DISABLE_DEBUG // The Debug Support has to be disabled, otherwise the code produces a runtime error.
#include <boost/circular_buffer.hpp>

using namespace boost::tuples;

// To do: 
// RCS StateModel - use enum strings, add mutex cmd/status queue or shared mem use CONNECTOR to write
// Sim StateModel - off, idle, starved, blocked, running, faulted
// boost thread synchronization: http://www.boost.org/doc/libs/1_45_0/doc/html/thread/synchronization.html
// ref: http://en.highscore.de/cpp/boost/functionobjects.html 
namespace StateModel
{

	enum ConditionType {Clear=0, Fault, Warning, Message } ;
	class IModule
	{
	public:
		virtual void Configure(std::string inifilename) =0;
		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void Stop() = 0;
		virtual void Reset() = 0;
		virtual void Quit()=0;
		virtual void Condition(ConditionType type, const char * id, const char *s)=0;

	};

	class AsyncMethod
	{
	public:
		AsyncMethod() : _thread(NULL) {}
		bool IsRunning()
		{
			if(_thread==NULL)
				return false;

			if(_thread->timed_join(boost::posix_time::microseconds(10)))
			{
				delete _thread;
				_thread=NULL;
				return false;
			}

			return true;
		} 

		template<typename T>
		bool Run(T t) 
		{ 
			if(IsRunning())
				return false;
			//  if(_thread ==NULL)
			if(_thread!=NULL)
			{
				delete _thread;
			}
			_thread = new boost::thread(t); 
			return true;
		} 
		inline void Join() 
		{ 
			if(_thread != NULL) 
			{ 
				_thread->join(); 
			} 
		} 
	private:
		boost::thread *_thread; 

	};




__declspec(selectany)  std::string off = std::string("off");
_declspec(selectany)  std::string ready = std::string("ready");
_declspec(selectany)  std::string loaded =std::string("loaded");
_declspec(selectany)  std::string running= std::string("running");
_declspec(selectany)  std::string stopped =std::string("stopped");
_declspec(selectany)  std::string interrupted =std::string("interrupted");
_declspec(selectany)  std::string faulted = std::string("faulted");
_declspec(selectany)  std::string  finished =std::string("finished");
_declspec(selectany)  std::string  exit =std::string("exit");
_declspec(selectany)  std::string  estopped =std::string("estopped");
_declspec(selectany)  std::string  any= std::string("any");
_declspec(selectany)  std::string  stepping =std::string("stepping");
_declspec(selectany)  std::string  starved =std::string("starved");
_declspec(selectany)  std::string  blocked= std::string("blocked");

_declspec(selectany)  std::string  ok =std::string("ok");
_declspec(selectany)  std::string  init =std::string("init");
_declspec(selectany)  std::string  load =std::string("load");
_declspec(selectany)  std::string  run =std::string("run");
_declspec(selectany)  std::string  stop =std::string("stop");
_declspec(selectany)  std::string  hold =std::string("hold");
_declspec(selectany)  std::string  fail =std::string("fail");
_declspec(selectany)  std::string  reset =std::string("reset");
_declspec(selectany)  std::string  resume =std::string("resume");
_declspec(selectany)  std::string  done =std::string("done");
_declspec(selectany)  std::string  quit= std::string("quit");
_declspec(selectany)  std::string  rewind= std::string("rewind");
_declspec(selectany)  std::string  estop= std::string("estop");
_declspec(selectany)  std::string  block= std::string("block");
_declspec(selectany)  std::string  starve =std::string("starve");
_declspec(selectany)  std::string  step =std::string("step");
_declspec(selectany)  std::string  singlestep =std::string("singlestep");
_declspec(selectany)  std::string  update =std::string("update");
_declspec(selectany)  std::string  empty =std::string("empty");


class ControlThread;

typedef std::string StateType;
typedef std::string EventType;

inline std::string StateStr(StateType s) { return s; }
inline std::string EventStr(EventType s) { return s; }



typedef boost::function< bool () > ControlThreadCondFnc;
typedef boost::function< void () > ControlThreadFnc;
typedef boost::function< void () > ControlNullThreadCondFnc;

typedef boost::function< void (ControlThread *) > ControlThreadCallbackFnc;
typedef boost::tuple<std::string, std::string, std::string, ControlThreadCondFnc ,ControlNullThreadCondFnc  > StateMachineTuple;
// State, Name, Unit, Description, init value, cost multiplier
// 0    , 1   ,  2  , 3           , 4        , 5
typedef boost::tuple<std::string, std::string, std::string, std::string, double , double  > CostFcnTuple;

	class ControlThread
	{ 
		//////
		///////////////////////////////////////////////////////////////////////
	public: 

		ControlThread() : _thread(NULL)
		{
			_cycle=0;
			_laststate=_state=off;
			_nDebugLevel=0;
			_updaterate=1000; // 1 second for now, eventually speed up
			eventtrace.resize(10);
			_dSpeedup=1.0;
			_dLoopTime=1.0; // loop time 1 second 
			_dTotalTime=0.0;
		}
		virtual ~ControlThread() 
		{ 
			Join(); 
			delete _thread; 
		} 

		// Error handling
		std::string GetErrorMessage() { return _errmsg; }
		void SetErrorMessage(std::string err) {  _errmsg=err; }

		unsigned int _updaterate;

		unsigned int & UpdateRate() { return _updaterate; }
		double UpdateRateSec() { return _updaterate / 1000.0 * _dSpeedup; }
		void SetUpdateRate(unsigned int milliseconds) {if(milliseconds>0) UpdateRate()=milliseconds; }

		static double _dSpeedup;  // good for all the state machines
		static boost::timer threadtimer;
		static double _dTotalTime;
		static double _dLoopTime;
		static std::map<std::string, double> globalCosts;
		static void Restart() { threadtimer.restart(); }

		void AddCostFunction(CostFcnTuple s) 
		{
			_costfcns.push_back(s);
		}

		static void Delay(double amt =0)
		{
			_dTotalTime += _dLoopTime;  // again in secondes (double)
			
			if(amt<0)
				return; // no delay...
			// Sleep a second
			boost::xtime xt;
			boost::xtime_get(&xt, boost::TIME_UTC);
			xt.sec += amt; 
			boost::thread::sleep(xt);
		}
		// Event handling
		void Trigger(StateType e)
		{ 
			_eventQueue.push_back(e); 
			//			Cycle(); // make events synchronously happen  = FIXME
		}

		// Conditions
		bool NullCondition() {return true; }
		void SetStateMachineName(std::string name) { _statemachinename=name; }
		void SetStateUpdate(StateType state1, StateModel::ControlThreadFnc fcn)
		{
			_stateMap[state1]=fcn;
		}
		// ISSUE here is that state transition has to exist first before eadding
		void SetStateTransition(StateType s1,  EventType e, StateType s2, StateModel::ControlThreadFnc fcn)
		{
			for(int i=0; i< _statemachine.size(); i++)
			{
				if(s1==get<0>(_statemachine[i]) && e==get<1>(_statemachine[i])&& s2==get<2>(_statemachine[i]) )
				{
					get<4>(_statemachine[i])=fcn;
				}
			}
		}
		void SetCondition(StateType s1, EventType e, StateModel::ControlThreadCondFnc fcn)
		{
			for(int i=0; i< _statemachine.size(); i++)
			{
				if(s1==get<0>(_statemachine[i]) && e==get<1>(_statemachine[i]))
				{
					get<3>(_statemachine[i])=fcn;
				}
			}
		}

		virtual void Nop()	{ LogMessage("Nop\n");	}
		virtual void Break()	{ DebugBreak();	}
		virtual void Postprocess(){}
		virtual void Preprocess(){}
		virtual void Breakpoint()	
		{ 
			LogMessage("Breakpoint\n");	
		}
		int IsActive() { return !_nloop; }
		void Loop()
		{
			boost::timer t; // start timing 
			while(IsActive())
			{
				t.restart();
				this->Cycle();
				int wait_time = UpdateRate() - (1000* t.elapsed()); 
				::Sleep(UpdateRate());
				//if(wait_time > 0)
				//	::Sleep(wait_time);
				//else
				//	::Sleep(1);

			}
		}
		bool FindStateTransitionMatch(StateType _state, EventType _e, std::vector<StateMachineTuple> statemachine, StateMachineTuple &statematch)
		{
			for(int i=0; i< statemachine.size(); i++)
			{
				if((_state==get<0>(statemachine[i]) && _e==get<1>(statemachine[i]))
					|| (any==get<0>(statemachine[i]) && _e==get<1>(statemachine[i]))
					)
				{
					statematch=statemachine[i];
					return true;
				}
			}
			return false;
		}
		void Cycle()
		{
			_cycle++;
			_laststate=GetState();
			_errmsg.clear();
			Preprocess();
			if(_eventQueue.size() > 0)
			{
				EventType e = _eventQueue.front();
				_eventQueue.pop_front();
				StateType state = GetState();
				bool bFail=true;
				StateMachineTuple statematch;
				if(FindStateTransitionMatch(state, e, _statemachine, statematch))
				{
					bFail=false;
					eventtrace.push_back(e);
					// Test guard condition
					if(get<3>(statematch)())
					{
						ControlThreadFnc fcn = get<4>(statematch);
						fcn();
						SetState(get<2>(statematch));
					}
					ListenerIterator it;
					if((it=_eventlisteners.find(e))!=_eventlisteners.end())
					{
						std::vector<ControlThreadCallbackFnc > listeners=(*it).second;
						for(int i=0; i< listeners.size(); i++) 
							listeners[i](this);

					}
				}
				if(bFail)
				{
					std::stringstream buffer;
					buffer << _statemachinename << " ERROR: Cannot process Event " << EventStr(e) << " in state " << StateStr(state) <<std::endl;
					LogMessage(buffer.str(), -1);
					if(_nDebugLevel>10) 
						DebugBreak();
				}

			}
			StateType state = GetState();
			std::string msg = StdStringFormat("%s State update %s \n", this->_statemachinename.c_str(), StateStr(state));
			// Execute current state update method - if no update method, do nothing...
			if(_stateMap.find(state)!=_stateMap.end())
			{
				boost::timer t; // start timing 
				//OutputDebugString(msg.c_str());
				_stateMap[state]();
				_stateMapTiming[state]= MAX(_stateMapTiming[state], t.elapsed());
				//OutputDebugString(StrFormat("Time took %.3f\n", t.elapsed()));
			}
			Postprocess();
		}

		void Join() 
		{ 
			if(_thread != NULL) 
				_thread->join(); 
		} 
		// boost::bind(&BThread::do_work, boost::ref(*this)
		void StartThread() 
		{ 
			_nloop=0;
			//  if(_thread ==NULL)
			if(_thread!=NULL)
				DebugBreak();
			_thread = new boost::thread(boost::bind(&ControlThread::Loop, this)); 
		} 
		void StopThread()
		{
			InterlockedIncrement( &_nloop ); 
			Join();
			SetState(off);
			if(_thread!=NULL)
				_thread = NULL;
		}
		void AddStateTransition(StateMachineTuple s) 
		{
			_statemachine.push_back(s);
		}
		template<typename U>
		void AddStateUpdate(StateType state, U t)
		{
			_stateMap[state]=t;
		}

		void AddEventListener(EventType e, ControlThreadCallbackFnc fcn)
		{
			_eventlisteners[e].push_back(fcn);
		}
		void RemoveEventListener(EventType e, ControlThreadCallbackFnc fcn)
		{
			//_eventlisteners::iterator it;
			//if((it=_eventlisteners.find(e)) !=  _eventlisteners.end())
			//	for(int i=0; i< (*it).second.size(); i++)
			//	{
			//		if((*it).second[i] == fcn)
			//			(*it).second.erase(i);
			//	}
		}		
		std::string& Name() { return this->_statemachinename; }
		virtual std::string ToString()
		{ 
			return StdStringFormat("%s State  %s \n", this->_statemachinename.c_str(), StateStr(GetState()).c_str());
		}
		std::string ModelToString()
		{ 
			std::string tmp;
			tmp+StdStringFormat("%16s, %16s, %16s\n", "state", "event", "newstate");
			for(int i=0; i< _statemachine.size(); i++)
			{
				// cant easily name condition or action or update action
				tmp+=StdStringFormat("%16s, %16s, %16s\n", StateStr(get<0>(_statemachine[i])), 
					EventStr(get<1>(_statemachine[i])),
					StateStr(get<2>(_statemachine[i])));
			}
			return tmp;
		}

		StateType GetState() 
		{
			StateType state;
			{ boost::mutex::scoped_lock(_mx);state=_state; }
			return state;
		}
		StateType GetLastState() 
		{
			StateType state;
			{ boost::mutex::scoped_lock(_mx);state=_laststate; }
			return state;
		}
		StateType SetState(StateType state) 
		{
			boost::mutex::scoped_lock(_mx); 
			StateType laststate=_state;
			_state=state; 
			return laststate;
		}	

		std::list<StateType> _statestack;
		void PushState(StateType state)
		{
			boost::mutex::scoped_lock(_mx); 
			_statestack.push_back(_state);
			StateType laststate=_state;
			_state=state; 
		}
		void PopState()
		{
			boost::mutex::scoped_lock(_mx); 
			_state = _statestack.front();
			_statestack.pop_front();
		}

		void ResetStateTiming()
		{
			for(std::map<StateType, double>::iterator it=_stateMapTiming.begin(); it!=_stateMapTiming.end(); it++)
				(*it).second=0.0;
		}
		double GetStateTiming(StateType state) { return _stateMapTiming[state]; }

		/////////////////////////////////////////////////////////////////
	protected:
			// problem
		typedef std::map<StateType, std::vector<ControlThreadCallbackFnc > >::iterator ListenerIterator;

		boost::thread *_thread; 
		StateType _state,_laststate;
		std::vector<StateMachineTuple> _statemachine;
		std::map<EventType, std::vector<ControlThreadCallbackFnc > > _eventlisteners;
		std::list<EventType> _eventQueue;
		std::map<StateType, ControlNullThreadCondFnc> _stateMap;
		std::map<StateType, double> _stateMapTiming;
		std::vector<CostFcnTuple> _costfcns;


		unsigned int _cycle;
		long _nloop;
		std::string _errmsg;
		int _nDebugLevel;
		std::string _statemachinename;
		boost::circular_buffer<EventType> eventtrace;

#ifdef DEBUG
		virtual void LogMessage(std::string str, int n=0)
		{
			if(n<_nDebugLevel)
				OutputDebugString(str.c_str());
		}
#else
#define LogMessage(X)
#endif		
	}; 

	__declspec(selectany)   double ControlThread::_dSpeedup;  // good for all the state machines
	__declspec(selectany)   boost::timer ControlThread::threadtimer;
	__declspec(selectany)   double ControlThread::_dTotalTime;
	__declspec(selectany)   double ControlThread::_dLoopTime;
	__declspec(selectany)   std::map<std::string, double>  ControlThread::globalCosts;


};
