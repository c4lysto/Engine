#ifndef _RECON_SYSSEMAPHORE_H_
#define _RECON_SYSSEMAPHORE_H_

#include <atomic>
#include <condition_variable>
#include <mutex>

#include "UtilitiesInclude.h"
#include "../Math Lib/MathLib.h"

namespace recon
{

class SysSemaphore
{
public:
	typedef void* Handle;

private:
	u32 m_MaxCount;
	u32 m_CurrCount;
	std::mutex m_ConditionMutex;
	std::recursive_mutex m_CountMutex;
	std::condition_variable m_CV;

public:
	SysSemaphore(u32 nMaxCount = U32_MAX);
	~SysSemaphore();

	SysSemaphore(const SysSemaphore& rhs) = delete;
	SysSemaphore& operator=(const SysSemaphore& rhs) = delete;

	void Acquire();
	bool TryAcquire();

	void Release(u32 nReleaseCount = 1);
};

inline SysSemaphore::SysSemaphore(u32 nMaxCount /*= U32_MAX*/) : 
	m_MaxCount(nMaxCount), 
	m_CurrCount(0)
{
}

inline SysSemaphore::~SysSemaphore()
{
	m_CountMutex.lock();
	m_MaxCount = 0;
	m_CurrCount = 0;
	m_CountMutex.unlock();

	m_CV.notify_all();
}

__forceinline void SysSemaphore::Acquire()
{
	while(true)
	{
		m_CountMutex.lock();
		if(m_CurrCount > 0)
		{
			--m_CurrCount;
			m_CountMutex.unlock();
			break;
		}
		else
		{
			m_CountMutex.unlock();
			m_CV.wait(std::unique_lock<std::mutex>(m_ConditionMutex));
		}
	}
}

__forceinline bool SysSemaphore::TryAcquire()
{
	bool bAcquired = false;

	m_CountMutex.lock();
	if(m_CurrCount > 0)
	{
		--m_CurrCount;
		bAcquired = true;
	}
	m_CountMutex.unlock();

	return bAcquired;
}

__forceinline void SysSemaphore::Release(u32 nReleaseCount /*= 1*/)
{
	m_CountMutex.lock();
	m_CurrCount = Min(m_CurrCount + nReleaseCount, m_MaxCount);
	m_CountMutex.unlock();
	m_CV.notify_all();
}

} // namespace recon

#endif // _RECON_SYSSEMAPHORE_H_