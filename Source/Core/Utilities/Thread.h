#ifndef _RECON_THREAD_H_
#define _RECON_THREAD_H_

#include "Function.h"
#include <thread>


namespace recon
{

typedef Function<void(void*)> ThreadProc;

class Event;

enum class ThreadPriority
{
	Idle = -15,
	Low = -2,
	Normal = 0,
	High = 2,
	Critical = 15
};

class Thread
{
public:
	typedef std::thread::native_handle_type Handle;

private:
	struct ThreadArgs
	{
		void* m_pArgs;
		ThreadProc m_pThreadFunc;

		ThreadArgs() :
			m_pArgs(nullptr),
			m_pThreadFunc(nullptr)
		{}
	};

private:
	std::thread m_Thread;
	ThreadArgs m_ThreadArgs;

	static unsigned int __stdcall DefaultThreadProc(void* pArgs);

public:
	Thread();
	Thread(ThreadProc pThreadProc, void* pArgs, ThreadPriority eThreadPrio = ThreadPriority::Normal, const char* szThreadName = nullptr);
	Thread(Thread&& rhs);
	~Thread();

	// Undefined to avoid bad things.
	Thread(const Thread& rhs) = delete;
	Thread& operator=(const Thread& rhs) = delete;

	Thread::Handle GetThreadHandle() {return m_Thread.native_handle();}

	operator bool() {return m_Thread.get_id() != std::thread::id();}
	u64 GetID() { std::hash<std::thread::id> hashFn; return (u64)hashFn(m_Thread.get_id()); }

	bool StartThread(ThreadProc pThreadProc, void* pArgs, ThreadPriority threadPriority = ThreadPriority::Normal, const char* szThreadName = nullptr);

	// Wait For Thread To Finish
	void Wait();

	void EndThread();

public:
	// pThread - Pass nullptr to set Calling Thread's Name
	static void SetThreadName(const char* szName, Thread* pThread = nullptr);

	// pThread - Pass nullptr to set Calling Thread's Priority
	static void SetThreadPriority(ThreadPriority threadPriority, Thread* pThread = nullptr);
};

} // namespace recon

#endif // _RECON_THREAD_H_
