#ifndef	_RECON_THREADPOOL_H_
#define _RECON_THREADPOOL_H_

#include <atomic>
#include <queue>
#include <vector>

#include "Mutex.h"
#include "Thread.h"
#include "Semaphore.h"

namespace recon
{

class ThreadPool
{
private:
	struct JobArgs
	{
		ThreadProc m_pProc;
		void* m_pArgs;
		ThreadPriority m_ePriority;

		JobArgs() {}
		JobArgs(ThreadProc pProc, void* pArgs, ThreadPriority ePriority) :
			m_pProc(pProc), m_pArgs(pArgs), m_ePriority(ePriority) {}
	};

private:
	Semaphore m_JobSemaphore;
	SysCriticalSection m_JobCS;
	std::vector<Thread> m_vThreads;
	std::queue<JobArgs> m_qJobs;

	static void WorkerThreadProc(void* pArgs);

	bool GetWork(JobArgs& jobArgs);

public:
	ThreadPool();
	~ThreadPool();

	// Optional Call
	void Init(size_t poolSize, const char* szPoolName = "Thread Pool");

	void Shutdown();

	void AddWork(ThreadProc pProc, void* pArgs, ThreadPriority ePriority = ThreadPriority::Normal);

	void ClearWorkQueue();
};

} // namespace recon

#endif // _RECON_THREADPOOL_H_