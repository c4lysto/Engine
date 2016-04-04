#include "Thread.h"

#if RECON_OS_WINDOWS
#include <process.h>
#endif // RECON_OS_WINDOWS

#include "CmdLineArg.h"
#include "Event.h"
#include "Random.h"
#include "Timer.h"

namespace recon
{

static CmdLineArg s_ThreadRandomSeed("randomseed");

THREADLOCAL u32 Thread::ms_ThreadType = ThreadType::Worker;
THREADLOCAL u32 Thread::ms_ThreadFlags = 0;

Thread::Thread()
{
}

Thread::Thread(ThreadProc pThreadProc, void* pArgs, ThreadPriority eThreadPrio /*= ThreadPriority::Normal*/, u32 threadType /*= ThreadType::Generic*/, u32 threadFlags /*= 0*/, const char* szThreadName /*= nullptr*/)
{
	StartThread(pThreadProc, pArgs, eThreadPrio, threadType, threadFlags, szThreadName);
}

Thread::Thread(Thread&& rhs) :
	m_Thread(std::move(rhs.m_Thread)),
	m_ThreadArgs(std::move(rhs.m_ThreadArgs))
{
}

Thread::~Thread()
{
	EndThread();
}

bool Thread::StartThread(ThreadProc pThreadProc, void* pArgs, ThreadPriority eThreadPrio /*= ThreadPriority::Normal*/, u32 threadType /*= ThreadType::Generic*/, u32 threadFlags /*= 0*/, const char* szThreadName /*= nullptr*/)
{
	bool bThreadStarted = false;

	//if(Verifyf(GetThreadHandle() == nullptr, "Thread is Already Active, Start Thread will not do anything."))
	{
		if(Verifyf(pThreadProc, "No Function Set for the starting thread"))
		{

			m_ThreadArgs.m_pThreadFunc = pThreadProc;
			m_ThreadArgs.m_pArgs = pArgs;
			m_ThreadArgs.m_ThreadType = threadType;
			m_ThreadArgs.m_ThreadFlags = threadFlags;

			m_Thread = std::thread(DefaultThreadProc, &m_ThreadArgs);

			if(GetHandle() != nullptr)
			{
				Thread::SetName(szThreadName, this);
				Thread::SetPriority(eThreadPrio, this);

				bThreadStarted = true;
			}
			else
			{
				DisplayDebugString("Failed To Create New Thread!");
			}
		}
	}

	return bThreadStarted;
}

int Thread::DefaultThreadProc(void* pArgs)
{
	s32 nProcRetVal = -1;

	if(pArgs)
	{
		s32 randomSeed = (s32)TimePoint::Now().GetAs<TimeInterval::Milliseconds>();

		s_ThreadRandomSeed.Get(randomSeed);
			
		Rand::Seed(randomSeed);

		ThreadArgs& threadArgs = *(ThreadArgs*)pArgs;

		ms_ThreadType = threadArgs.m_ThreadType;
		ms_ThreadFlags = threadArgs.m_ThreadFlags;

		(threadArgs.m_pThreadFunc)(threadArgs.m_pArgs);

		nProcRetVal = 0;
	}

#if RECON_ASSERT
	if(nProcRetVal == -1)
	{
		Assertf(false, "Failed To Properly Start Thread! pArgs must be NULL for some reason!");
	}
#endif // RECON_ASSERT

	return nProcRetVal;
}

void Thread::Wait()
{
	if(m_Thread.joinable() && m_Thread.get_id() != std::this_thread::get_id())
	{
		m_Thread.join();
	}
}

void Thread::EndThread()
{	
	Wait();
}

// pThread - Pass nullptr to set Calling Thread's Name
void Thread::SetName(const char* szName, Thread* pThread /*= nullptr*/)
{
	(void)szName;
	(void)pThread;

#if RECON_OS_WINDOWS
	// How to Set Thread Name According to MSDN

	const DWORD MS_VC_EXCEPTION = 0x406D1388;

	struct THREADNAME_INFO
	{
		const DWORD dwType = 0x1000;	// Must be 0x1000.
		LPCSTR szName;					// Pointer to name (in user addr space).
		DWORD dwThreadID;				// Thread ID (-1=caller thread).
		DWORD dwFlags;					// Reserved for future use, must be zero.
	};

	THREADNAME_INFO info;
	info.szName = szName ? szName : "Worker Thread";
	info.dwThreadID = pThread ? ::GetThreadId(pThread->GetHandle()) : (DWORD)-1;
	info.dwFlags = 0;

	__try
	{
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {}
#endif // RECON_OS_WINDOWS
}

void Thread::SetPriority(ThreadPriority threadPriority, Thread* pThread /*= nullptr*/)
{
	(void)threadPriority;
	(void)pThread;

#if RECON_OS_WINDOWS
	if (Verifyf((threadPriority == ThreadPriority::Idle || threadPriority == ThreadPriority::Critical) ||
		(threadPriority >= ThreadPriority::Low && threadPriority <= ThreadPriority::High), "Thread::SetThreadPriority() - Invalid Thread Priority"))
	{
		::SetThreadPriority(pThread ? pThread->GetHandle() : GetCurrentThread(), (int)threadPriority);
	}
#endif // RECON_OS_WINDOWS
}

void Thread::InitMainThread(u32 threadFlags /*= 0*/)
{ 
	ms_ThreadType = ThreadType::Main; 
	ms_ThreadFlags = threadFlags; 

	s32 randomSeed = (s32)TimePoint::Now().GetAs<TimeInterval::Milliseconds>();
	s_ThreadRandomSeed.Get(randomSeed);

	Rand::Seed(randomSeed);
}

} // namespace recon
