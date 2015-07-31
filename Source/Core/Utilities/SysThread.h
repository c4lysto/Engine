#ifndef _RECON_SYSTHREAD_H_
#define _RECON_SYSTHREAD_H_

#include "FunctionPointer.h"
#include <thread>

namespace recon
{

typedef FunctionPointer<void, void*> SysThreadProc;
class SysEvent;

enum class SysThreadPriority
{
	Idle = -15,
	Low = -2,
	Below_Normal = -1,
	Normal = 0,
	Above_Normal = 1,
	High = 2,
	Critical = 15
};

class SysThread
{
public:
	typedef std::thread::native_handle_type Handle;

private:
	struct ThreadArgs
	{
		void* m_pArgs;
		SysThreadProc m_pThreadFunc;
		//SysEvent* m_pThreadStartEvent;

		ThreadArgs() :
			m_pArgs(nullptr),
			m_pThreadFunc(nullptr)//,
			//m_pThreadStartEvent(nullptr)
		{}
	};

private:
	std::thread m_Thread;
	ThreadArgs m_ThreadArgs;

	static unsigned int __stdcall DefaultThreadProc(void* pArgs);

public:
	SysThread();
	SysThread(SysThreadProc pThreadProc, void* pArgs, SysThreadPriority eThreadPrio = SysThreadPriority::Normal, const char* szThreadName = nullptr);
	SysThread(SysThread&& rhs);
	~SysThread();

	// Undefined to avoid bad things.
	SysThread(const SysThread& rhs) = delete;
	SysThread& operator=(const SysThread& rhs) = delete;

	SysThread::Handle GetThreadHandle() {return m_Thread.native_handle();}

	operator bool() {return m_Thread.get_id() != std::thread::id();}
	std::size_t GetID() { return m_Thread.get_id().hash(); }

	bool StartThread(SysThreadProc pThreadProc, void* pArgs, SysThreadPriority threadPriority = SysThreadPriority::Normal, const char* szThreadName = nullptr);

	// Wait For Thread To Finish
	void Wait();

	void EndThread();
};

// pThread - Pass nullptr to set Calling Thread's Name
void SysSetThreadName(const char* szName, SysThread* pThread = nullptr);

// pThread - Pass nullptr to set Calling Thread's Priority
void SysSetThreadPriority(SysThreadPriority threadPriority, SysThread* pThread = nullptr);

} // namespace recon

#endif // _RECON_SYSTHREAD_H_