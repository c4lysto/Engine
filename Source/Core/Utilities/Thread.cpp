#include "Thread.h"
#include <process.h>

#include "Event.h"

namespace recon
{

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

	if(Verifyf(GetThreadHandle() == nullptr, "Thread is Already Active, Start Thread will not do anything."))
	{
		if(Verifyf(pThreadProc, "No Function Set for the starting thread"))
		{

			m_ThreadArgs.m_pThreadFunc = pThreadProc;
			m_ThreadArgs.m_pArgs = pArgs;

			m_Thread = std::thread(DefaultThreadProc, &m_ThreadArgs);

			if(GetThreadHandle() != nullptr)
			{
				SysSetThreadName(szThreadName, this);
				SysSetThreadPriority(eThreadPrio, this);

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

unsigned int __stdcall Thread::DefaultThreadProc(void* pArgs)
{
	u32 nProcRetVal = (u32)-1;

	if(pArgs)
	{
		ThreadArgs& threadArgs = *(ThreadArgs*)pArgs;

		(threadArgs.m_pThreadFunc)(threadArgs.m_pArgs);

		nProcRetVal = 0;
	}

#if RECON_ASSERT
	if(nProcRetVal == (u32)-1)
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
void SysSetThreadName(const char* szName, Thread* pThread /*= nullptr*/)
{
	// How to Set Thread Name According to MSDN

	const DWORD MS_VC_EXCEPTION = 0x406D1388;

	struct THREADNAME_INFO
	{
		const DWORD dwType = 0x1000; // Must be 0x1000.
		LPCSTR szName; // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags; // Reserved for future use, must be zero.
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
}

void SysSetThreadPriority(ThreadPriority threadPriority, Thread* pThread /*= nullptr*/)
{
	if (Verifyf((threadPriority == ThreadPriority::Idle || threadPriority == ThreadPriority::Critical) ||
		(threadPriority >= ThreadPriority::Low && threadPriority <= ThreadPriority::High), "SysSetThreadPriority() - Invalid Thread Priority"))
	{
		SetThreadPriority(pThread ? pThread->GetThreadHandle() : GetCurrentThread(), (int)threadPriority);
	}
}

} // namespace recon
