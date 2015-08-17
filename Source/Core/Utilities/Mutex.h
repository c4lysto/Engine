#ifndef _RECON_MUTEX_H_
#define _RECON_MUTEX_H_

#include "UtilitiesInclude.h"

#include <mutex>

namespace recon
{

class Mutex;

typedef Mutex SysCriticalSection;

class Mutex
{
	friend class SysAutoMutex;

private:
	const u32 m_nSpinCount;
	std::recursive_mutex m_Mutex;

public:
	Mutex(u32 nSpinCount = 1000) : m_nSpinCount(nSpinCount) {}
	~Mutex() {}

	Mutex(const Mutex& rhs) = delete;
	Mutex& operator=(const Mutex& rhs) = delete;

	void Lock();
	bool TryLock();
	void Unlock();

public:

	friend void SysCreateMutex(Mutex& sysMutex, bool bInitialOwner = false);
	friend void SysCloseMutex(Mutex& sysMutex);
};

__forceinline void Mutex::Lock()
{ 
	u32 nCurrSpin = m_nSpinCount; 
	while(nCurrSpin--)
	{
		if(TryLock()) 
			return;
	} 
	m_Mutex.lock(); 
}

__forceinline bool Mutex::TryLock()
{
	return m_Mutex.try_lock(); 
}

__forceinline void Mutex::Unlock()
{
	m_Mutex.unlock();
}


class SysAutoMutex;

typedef SysAutoMutex SysAutoCriticalSection;

class SysAutoMutex
{
private:
	Mutex& m_Mutex;

public:
	SysAutoMutex(Mutex& sysMutex) :
		m_Mutex(sysMutex)
	{
		m_Mutex.Lock();
	}
	
	~SysAutoMutex()
	{
		m_Mutex.Unlock();
	}

	void Lock() { m_Mutex.Lock(); }
	bool TryLock() { return m_Mutex.TryLock(); }
	void Unlock() { m_Mutex.Unlock(); }
};

} // namespace recon

#endif // _RECON_MUTEX_H_