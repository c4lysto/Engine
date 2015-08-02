#include "ThreadPool.h"
#include <sstream>

namespace recon
{

ThreadPool::ThreadPool()
{
	SysCreateSemaphore(m_JobSemaphore);
}

ThreadPool::~ThreadPool()
{
	Shutdown();
}

void ThreadPool::WorkerThreadProc(void* pArgs)
{
	if(pArgs)
	{
		ThreadPool* pThreadPool = (ThreadPool*)pArgs;
		JobArgs jobArgs;

		if(pThreadPool)
		{
			while(true)
			{
				if(pThreadPool->GetWork(jobArgs))
				{
					SysSetThreadPriority(jobArgs.m_ePriority);

					(jobArgs.m_pProc)(jobArgs.m_pArgs);

					SysSetThreadPriority(SysThreadPriority::Normal);
				}
				else
				{
					break;
				}
			}
		}
	}
}

bool ThreadPool::GetWork(ThreadPool::JobArgs& jobArgs)
{
	m_JobSemaphore.Wait();

	SysLocalCriticalSection jobCS(m_JobCS);

	bool bValidJob = false;

	if (!m_qJobs.empty())
	{
		jobArgs = m_qJobs.front();
		bValidJob = true;
	}

	return bValidJob;
}

void ThreadPool::Init(size_t poolSize, const char* szPoolName /*= "Thread Pool"*/)
{
	// Pool Has Already Been Initialized, Don't Be Stupid
	if(m_vThreads.size() == 0)
	{
		for(size_t i = 0; i < poolSize; ++i)
		{
			std::ostringstream threadName;
			threadName << szPoolName << "(" << i << ")";
			m_vThreads.push_back(SysThread(WorkerThreadProc, this, SysThreadPriority::Normal, threadName.str().c_str()));
		}
	}
}

void ThreadPool::Shutdown()
{
	ClearWorkQueue();

	for(size_t i = 0; i < m_vThreads.size(); ++i)
	{
		m_vThreads[i].Wait();
	}

	m_vThreads.clear();

	SysCloseSemaphore(m_JobSemaphore);
}

void ThreadPool::AddWork(SysThreadProc pProc, void* pArgs, SysThreadPriority ePriority /*= SysThreadPriority::Normal*/)
{
	SysLocalCriticalSection jobCS(m_JobCS);

	m_qJobs.push(JobArgs(pProc, pArgs, ePriority));

	m_JobSemaphore.Unlock();
}

void ThreadPool::ClearWorkQueue()
{
	SysLocalCriticalSection jobCS(m_JobCS);

	while(!m_qJobs.empty())
	{
		m_qJobs.pop();
	}

	m_JobSemaphore.Unlock();
}

} // namespace recon
