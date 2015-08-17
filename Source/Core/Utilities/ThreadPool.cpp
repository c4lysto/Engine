#include "ThreadPool.h"
#include <sstream>

namespace recon
{

ThreadPool::ThreadPool()
{
	
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

					SysSetThreadPriority(ThreadPriority::Normal);
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
	m_JobSemaphore.Acquire();

	SysAutoCriticalSection jobCS(m_JobCS);

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
			m_vThreads.push_back(Thread(WorkerThreadProc, this, ThreadPriority::Normal, threadName.str().c_str()));
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
}

void ThreadPool::AddWork(ThreadProc pProc, void* pArgs, ThreadPriority ePriority /*= ThreadPriority::Normal*/)
{
	SysAutoCriticalSection jobCS(m_JobCS);

	m_qJobs.push(JobArgs(pProc, pArgs, ePriority));

	m_JobSemaphore.Release();
}

void ThreadPool::ClearWorkQueue()
{
	SysAutoCriticalSection jobCS(m_JobCS);

	while(!m_qJobs.empty())
	{
		m_qJobs.pop();
	}

	m_JobSemaphore.Release((u32)m_vThreads.size());
}

} // namespace recon
