//
// boost.h
//
#pragma once
#include <boost/thread/thread.hpp>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"
#include "boost/lambda/bind.hpp"
#include <boost/function.hpp> 
#include <boost/timer.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp> 

using namespace boost::tuples;

// To do: 
// RCS StateModel - use enum strings, add mutex cmd/status queue or shared mem use CONNECTOR to write
// Sim StateModel - off, idle, starved, blocked, running, faulted
// boost thread synchronization: http://www.boost.org/doc/libs/1_45_0/doc/html/thread/synchronization.html
// ref: http://en.highscore.de/cpp/boost/functionobjects.html 
namespace StateModel
{
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


	class ControlThread;

	/**
	ControlThread ct;
	ct.cycle();
	ct.cycle();
	ct.Trigger(init);
	ct.cycle();
	ct.SetStateTransition(ready,load, boost::bind(&Foo::Init1));
	ct.Trigger(load);
	ct.cycle();

	fixme: add state transition listeners (or multiitem map)
	*/

	class CState
	{
	public:
		const std::string off,ready,loaded,running,stopped,interrupted;
		const std::string faulted,finished,estopped,any;
		CState() : 	off("off"), ready("ready"), loaded("loaded"), running("running"), stopped("stopped"),
			interrupted("interrupted"), faulted("faulted"), estopped("estopped"), any("any") {}
	};
	class CEvent
	{
	public:
		const std::string init,run,stop,hold,fail,reset;
		const std::string resume,done,quit,rewind,estop,step;
		CEvent() : 	init("init"), run("run"), stop("stop"), hold("hold"), fail("fail"),
			reset("reset"), resume("resume"), done("done"), quit("quit"),  rewind("rewind"), 
			estop("estop"), step("step") {}
	};
__declspec(selectany)  CEvent Events;

#define GET_NAME(n) (#n)
#define PRINTABLE_ENUM_STRINGS 1
#include "PrintableEnum.h"
	ENUM(State, 0, (off) (ready) (loaded) (running) (stopped) (interrupted) (faulted) (finished)  (exit) (estopped) (any))
		ENUM(Event, 0, (init) (load) (run) (stop) (hold) (fail) (reset) (resume)  (done) (quit) (rewind) (estop))
		//typedef enum { off, ready, loaded, running, stopped, interrupted, faulted, finished,  exit, estopped, any} State;
		//typedef enum { init, load, run, stop, hold, fail, reset, resume, done, quit, rewind, estop} Event;


		typedef boost::function< bool () > ControlThreadCondFnc;
	typedef boost::function< void () > ControlThreadFnc;
	typedef boost::function< void (ControlThread *) > ControlThreadCallbackFnc;
	typedef boost::function< void () > ControlNullThreadCondFnc;

	typedef boost::tuple<int, int, int, ControlThreadCondFnc ,ControlNullThreadCondFnc  > StateMachineTuple;


	class ControlThread 
	{ 
		/////////////////////////////////////////////////////////////////////////////
	public: 
		ControlThread() : _thread(NULL)
		{
			_cycle=0;
			_laststate=_state=off;
			_nDebugLevel=0;
			_updaterate=100;
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
		void SetUpdateRate(unsigned int milliseconds) {if(milliseconds>0) UpdateRate()=milliseconds; }

		// Event handling
		void Trigger(int e) { _eventQueue.push_back(e); }
		// Conditions
		bool NullCondition() {return true; }
		void SetStateMachineName(std::string name) { _statemachinename=name; }
		void SetStateUpdate(int state1, StateModel::ControlThreadFnc fcn)
		{
			_stateMap[state1]=fcn;
		}
		// ISSUE here is that state transition has to exist first before eadding
		void SetStateTransition(int s1,  int e, int s2, StateModel::ControlThreadFnc fcn)
		{
			for(int i=0; i< _statemachine.size(); i++)
			{
				if(s1==get<0>(_statemachine[i]) && e==get<1>(_statemachine[i])&& s2==get<2>(_statemachine[i]) )
				{
					get<4>(_statemachine[i])=fcn;
				}
			}
		}
		void SetCondition(int s1, int e, StateModel::ControlThreadCondFnc fcn)
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
		virtual void Breakpoint()	
		{ 
			LogMessage("Breakpoint\n");	
		}

		void Loop()
		{
			boost::timer t; // start timing 
			while(_bLoop)
			{
				t.restart();
				this->Cycle();
				int wait_time = UpdateRate() - (1000* t.elapsed()); 
				if(wait_time > 0)
					::Sleep(wait_time);
				else
					::Sleep(1);

			}
		}
		bool FindStateTransitionMatch(int _state, int _e, std::vector<StateMachineTuple> statemachine, StateMachineTuple &statematch)
		{
			for(int i=0; i< statemachine.size(); i++)
			{
				if((_state==get<0>(statemachine[i]) && _e==get<1>(statemachine[i]))
					|| (StateModel::any==get<0>(statemachine[i]) && _e==get<1>(statemachine[i]))
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
			if(_eventQueue.size() > 0)
			{
				int e = _eventQueue.front();
				_eventQueue.pop_front();
				int state = GetState();
				bool bFail=true;
				StateMachineTuple statematch;
				if(FindStateTransitionMatch(state, e, _statemachine, statematch))
				{
					bFail=false;
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
					buffer << _statemachinename << " ERROR: Cannot process Event " << Event_Str[e] << " in state " << State_Str[state] ;
					LogMessage(buffer.str(), -1);
					if(_nDebugLevel>10) 
						DebugBreak();
				}

			}
			int state = GetState();
			std::string msg = StdStringFormat("%s State update %s \n", this->_statemachinename.c_str(), State_Str[state]);
			// Execute current state update method - if no update method, do nothing...
			if(_stateMap.find(state)!=_stateMap.end())
			{
				boost::timer t; // start timing 
				//OutputDebugString(msg.c_str());
				_stateMap[state]();
				_stateMapTiming[state]= MAX(_stateMapTiming[state], t.elapsed());
				//OutputDebugString(StrFormat("Time took %.3f\n", t.elapsed()));
			}
		}

		int GetState() 
		{
			int state;
			{ boost::mutex::scoped_lock(_mx);state=_state; }
			return state;
		}
		int GetLastState() 
		{
			int state;
			{ boost::mutex::scoped_lock(_mx);state=_laststate; }
			return state;
		}
		void Join() 
		{ 
			if(_thread != NULL) 
			{ 
				_thread->join(); 
			} 
		} 
		// boost::bind(&BThread::do_work, boost::ref(*this)
		void StartThread() 
		{ 
			boost::mutex::scoped_lock(_mx); 
			_bLoop=true;
			//  if(_thread ==NULL)
			if(_thread!=NULL)
				DebugBreak();
			_thread = new boost::thread(boost::bind(&ControlThread::Loop, this)); 
		} 
		void StopThread()
		{
			boost::mutex::scoped_lock(_mx); 
			_bLoop=false;
			Join();
		}
		void AddStateTransition(StateMachineTuple s) 
		{
			_statemachine.push_back(s);
		}
		template<typename T>
		void AddStateUpdate(int s, T t)
		{
			_stateMap[s]=t;
		}

		void AddEventListener(int e, StateModel::ControlThreadCallbackFnc fcn)
		{
			_eventlisteners[e].push_back(fcn);
		}
		void RemoveEventListener(int e, StateModel::ControlThreadCallbackFnc fcn)
		{
			//_eventlisteners::iterator it;
			//if((it=_eventlisteners.find(e)) !=  _eventlisteners.end())
			//	for(int i=0; i< (*it).second.size(); i++)
			//	{
			//		if((*it).second[i] == fcn)
			//			(*it).second.erase(i);
			//	}
		}		
	protected:
		int SetState(int state) 
		{
			boost::mutex::scoped_lock(_mx); 
			int laststate=_state;
			_state=state; 
			return laststate;
		}		/////////////////////////////////////////////////////////////////
		boost::thread *_thread; 
		int _state,_laststate;
		std::vector<StateMachineTuple> _statemachine;
		std::map<int, std::vector<ControlThreadCallbackFnc > > _eventlisteners;
		typedef std::map<int, std::vector<ControlThreadCallbackFnc > >::iterator ListenerIterator;
		std::list<int> _eventQueue;
		std::map<int, ControlNullThreadCondFnc> _stateMap;
		std::map<int, double> _stateMapTiming;
		
		unsigned int _cycle;
		bool _bLoop;
		std::string _errmsg;
		int _nDebugLevel;
		std::string _statemachinename;

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

	class ProgramControlThread  : public ControlThread
	{ 
	public:
		typedef ProgramControlThread MyClass;
		ProgramControlThread()
		{
			_statemachine.push_back(StateMachineTuple(off,init,ready,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Init, this))); 
			_statemachine.push_back(StateMachineTuple(ready,load, loaded,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Load, this))); 
			_statemachine.push_back(StateMachineTuple(ready,run, running,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Run, this))); 
			_statemachine.push_back(StateMachineTuple(loaded,run, running,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Run, this))); 
			_statemachine.push_back(StateMachineTuple(stopped,run, running,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Reset, this))); 
			_statemachine.push_back(StateMachineTuple(running,stop, stopped,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Stop, this))); 
			_statemachine.push_back(StateMachineTuple(running,hold, interrupted,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Hold, this))); 
			_statemachine.push_back(StateMachineTuple(running, done, finished,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Done, this))); 
			_statemachine.push_back(StateMachineTuple(finished, StateModel::rewind, ready,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Rewind, this))); 
			_statemachine.push_back(StateMachineTuple(interrupted,run, running,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Resume, this))); 

			_statemachine.push_back(StateMachineTuple(any,quit, StateModel::exit,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Exit, this))); 
			_statemachine.push_back(StateMachineTuple(any,fail, faulted,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Fail, this))); 
			_statemachine.push_back(StateMachineTuple(any,estop, estopped,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Stop, this))); 
			_statemachine.push_back(StateMachineTuple(any,reset, ready,  boost::bind(&MyClass::NullCondition, this),	boost::bind(&MyClass::Reset, this))); 

			_stateMap[StateModel::off]=boost::bind(&MyClass::Off, this);
			_stateMap[StateModel::ready]=boost::bind(&MyClass::Ready, this);
			_stateMap[StateModel::loaded]=boost::bind(&MyClass::Loaded, this);
			_stateMap[StateModel::running]=boost::bind(&MyClass::Running, this);
			_stateMap[StateModel::stopped]=boost::bind(&MyClass::Stopped, this);
			_stateMap[StateModel::interrupted]=boost::bind(&MyClass::Interrupted, this);
			_stateMap[StateModel::faulted]=boost::bind(&MyClass::Faulted, this);
			_stateMap[StateModel::exit]=boost::bind(&MyClass::Exit, this);
		}
		// State transitions
		virtual void Init() { LogMessage("Init\n"); }
		virtual void Load() { LogMessage("Load\n"); }
		virtual void Run() { LogMessage("Run\n"); }
		virtual void Stop() { LogMessage("Stop\n"); }
		virtual void Fail() { LogMessage("Fail\n"); }
		virtual void Hold() { LogMessage("Hold\n"); }
		virtual void Reset() { LogMessage("Reset\n"); }
		virtual void Done() { LogMessage("Done\n"); }
		virtual void Resume() { LogMessage("Resume\n"); }
		virtual void Rewind() { LogMessage("Rewind\n"); }

		// State methods
		virtual void Nop()	{ LogMessage("Nop\n");	}
		virtual void Off()	{ LogMessage("Off\n");	}
		virtual void Ready() { LogMessage("Ready\n");	 }
		virtual void Loaded() {  LogMessage("Loaded\n");	}
		virtual void Running() { LogMessage("Running\n");	 }
		virtual void Stopped() { LogMessage("Stopped\n");	 }
		virtual void Interrupted() { LogMessage("Interrupted\n");	 }
		virtual void Faulted() { LogMessage("Faulted\n");	 }
		virtual void Exit() { LogMessage("Exit\n");	 }

	};


};
#if 0
/// http://stackoverflow.com/questions/4459194/pausing-a-boostthread-for-unlimited-time
// Pause all
bool m_pause; 
boost::mutex m_pause_mutex; 
boost::condition_variable m_pause_changed; 

void block_while_paused() 
{ 
	boost::unique_lock<boost::mutex> lock(m_pause_mutex); 
	while(m_pause) 
	{ 
		m_pause_changed.wait(lock); 
	} 
} 

void set_paused(bool new_value) 
{ 
	{ 
		boost::unique_lock<boost::mutex> lock(m_pause_mutex); 
		m_pause = new_value; 
	} 

	m_pause_changed.notify_all(); 
} 

#endif