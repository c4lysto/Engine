#ifndef	_RECON_THREADPOOL_H_
#define _RECON_THREADPOOL_H_

#include <atomic>
#include <queue>
#include <vector>

#include "SysMutex.h"
#include "SysThread.h"
#include "SysSemaphore.h"

namespace recon
{

class ThreadPool
{
private:
	struct JobArgs
	{
		SysThreadProc m_pProc;
		void* m_pArgs;
		SysThreadPriority m_ePriority;

		JobArgs() {}
		JobArgs(SysThreadProc pProc, void* pArgs, SysThreadPriority ePriority) :
			m_pProc(pProc), m_pArgs(pArgs), m_ePriority(ePriority) {}
	};

private:
	SysSemaphore m_JobSemaphore;
	SysCriticalSection m_JobCS;
	std::vector<SysThread> m_vThreads;
	std::queue<JobArgs> m_qJobs;

	static void WorkerThreadProc(void* pArgs);

	bool GetWork(JobArgs& jobArgs);

public:
	ThreadPool();
	~ThreadPool();

	// Optional Call
	void Init(size_t poolSize, const char* szPoolName = "Thread Pool");

	void Shutdown();

	void AddWork(SysThreadProc pProc, void* pArgs, SysThreadPriority ePriority = SysThreadPriority::Normal);

	void ClearWorkQueue();
};

} // namespace recon

#endif // _RECON_THREADPOOL_H_