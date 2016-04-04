#ifndef _RECON_THREAD_H_
#define _RECON_THREAD_H_

#include <chrono>
#include <thread>

#include "Function.h"


namespace recon
{

typedef Function<void(void*)> ThreadProc;

enum class ThreadPriority
{
	Idle = -15,
	Low = -2,
	Normal = 0,
	High = 2,
	Critical = 15
};

enum ThreadType
{
	Main = 0,
	Worker = 1,

	NumReconThreadTypes
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
		u32 m_ThreadType;
		u32 m_ThreadFlags;

		ThreadArgs() :
			m_pArgs(nullptr),
			m_pThreadFunc(nullptr)
		{}
	};

private:
	static THREADLOCAL u32 ms_ThreadType;
	static THREADLOCAL u32 ms_ThreadFlags;

	static int DefaultThreadProc(void* pArgs);

private:
	std::thread m_Thread;
	ThreadArgs m_ThreadArgs;

public:
	Thread();
	Thread(ThreadProc pThreadProc, void* pArgs, ThreadPriority eThreadPrio = ThreadPriority::Normal, u32 threadType = ThreadType::Worker, u32 threadFlags = 0, const char* szThreadName = nullptr);
	Thread(Thread&& rhs);
	~Thread();

	// Undefined to avoid bad things.
	Thread(const Thread& rhs) = delete;
	Thread& operator=(const Thread& rhs) = delete;

	Thread::Handle GetHandle() {return m_Thread.native_handle();}

	operator bool() {return m_Thread.get_id() != std::thread::id();}
	u64 GetID() const { std::hash<std::thread::id> hashFn; return (u64)hashFn(m_Thread.get_id()); }

	bool StartThread(ThreadProc pThreadProc, void* pArgs, ThreadPriority threadPriority = ThreadPriority::Normal, u32 threadType = ThreadType::Worker, u32 threadFlags = 0, const char* szThreadName = nullptr);

	// Wait For Thread To Finish
	void Wait();

	void EndThread();

public:
	// pThread - Pass nullptr to set Calling Thread's Name
	static void SetName(const char* szName, Thread* pThread = nullptr);

	// pThread - Pass nullptr to set Calling Thread's Priority
	static void SetPriority(ThreadPriority threadPriority, Thread* pThread = nullptr);

	// Stupid Microsoft #defined Yield(), not a smart choice for a name as common as Yield
	static void Yield() { std::this_thread::yield(); }

	static void Sleep(u32 timeInMS) { std::this_thread::sleep_for(std::chrono::duration<u32, std::milli>(timeInMS)); }

	static u64 GetCurrentThreadID() { std::hash<std::thread::id> hashFn; return (u64)hashFn(std::this_thread::get_id()); }

	//static Thread::Handle GetCurrentThreadHandle() { return std::this_thread::; }

	static u32 GetType() { return ms_ThreadType; }
	static u32 GetFlags() { return ms_ThreadFlags; }

	static void InitMainThread(u32 threadFlags = 0);
};

} // namespace recon

#endif // _RECON_THREAD_H_
