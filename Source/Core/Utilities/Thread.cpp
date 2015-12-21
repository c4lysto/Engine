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

Thread::Thread()
{
}

Thread::Thread(ThreadProc pThreadProc, void* pArgs, ThreadPriority eThreadPrio /*= ThreadPriority::Normal*/, const char* szThreadName /*= nullptr*/)
{
	StartThread(pThreadProc, pArgs, eThreadPrio, szThreadName);
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

bool Thread::StartThread(ThreadProc pThreadProc, void* pArgs, ThreadPriority eThreadPrio /*= ThreadPriority::Normal*/, const char* szThreadName /*= nullptr*/)
{
	bool bThreadStarted = false;

	//if(Verifyf(GetThreadHandle() == nullptr, "Thread is Already Active, Start Thread will not do anything."))
	{
		if(Verifyf(pThreadProc, "No Function Set for the starting thread"))
		{

			m_ThreadArgs.m_pThreadFunc = pThreadProc;
			m_ThreadArgs.m_pArgs = pArgs;

			m_Thread = std::thread(DefaultThreadProc, &m_ThreadArgs);

			if(GetThreadHandle() != nullptr)
			{
				Thread::SetThreadName(szThreadName, this);
				Thread::SetThreadPriority(eThreadPrio, this);

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
		s32 randomSeed = (s32)(TimePoint::Now() - TimePoint()).Get<TimeInterval::Milliseconds>();

		s_ThreadRandomSeed.Get(randomSeed);

		Rand::Seed(randomSeed);

		ThreadArgs& threadArgs = *(ThreadArgs*)pArgs;

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
void Thread::SetThreadName(const char* szName, Thread* pThread /*= nullptr*/)
{
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
	info.dwThreadID = pThread ? GetThreadId(pThread->GetThreadHandle()) : (DWORD)-1;
	info.dwFlags = 0;

	__try
	{
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except(EXCEPTION_EXECUTE_HANDLER) {}
#endif // RECON_OS_WINDOWS
}

void Thread::SetThreadPriority(ThreadPriority threadPriority, Thread* pThread /*= nullptr*/)
{
#if RECON_OS_WINDOWS
	if (Verifyf((threadPriority == ThreadPriority::Idle || threadPriority == ThreadPriority::Critical) ||
		(threadPriority >= ThreadPriority::Low && threadPriority <= ThreadPriority::High), "Thread::SetThreadPriority() - Invalid Thread Priority"))
	{
		::SetThreadPriority(pThread ? pThread->GetThreadHandle() : GetCurrentThread(), (int)threadPriority);
	}
#endif // RECON_OS_WINDOWS
}

} // namespace recon
