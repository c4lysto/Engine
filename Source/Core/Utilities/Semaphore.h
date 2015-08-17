#ifndef _RECON_SEMAPHORE_H_
#define _RECON_SEMAPHORE_H_

#include <atomic>
#include <condition_variable>
#include <mutex>

#include "UtilitiesInclude.h"
#include "../Math Lib/MathLib.h"

namespace recon
{

class Semaphore
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
	Semaphore(u32 nMaxCount = U32_MAX);
	~Semaphore();

	Semaphore(const Semaphore& rhs) = delete;
	Semaphore& operator=(const Semaphore& rhs) = delete;

	void Acquire();
	bool TryAcquire();

	void Release(u32 nReleaseCount = 1);
};

inline Semaphore::Semaphore(u32 nMaxCount /*= U32_MAX*/) : 
	m_MaxCount(nMaxCount), 
	m_CurrCount(0)
{
}

inline Semaphore::~Semaphore()
{
	m_CountMutex.lock();
	m_MaxCount = 0;
	m_CurrCount = 0;
	m_CountMutex.unlock();

	m_CV.notify_all();
}

__forceinline void Semaphore::Acquire()
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

__forceinline bool Semaphore::TryAcquire()
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

__forceinline void Semaphore::Release(u32 nReleaseCount /*= 1*/)
{
	m_CountMutex.lock();
	m_CurrCount = Min(m_CurrCount + nReleaseCount, m_MaxCount);
	m_CountMutex.unlock();
	m_CV.notify_all();
}

} // namespace recon

#endif // _RECON_SEMAPHORE_H_