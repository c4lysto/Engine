#ifndef _RECON_SYSMUTEX_H_
#define _RECON_SYSMUTEX_H_

#include "UtilitiesInclude.h"

#include <mutex>

namespace recon
{

class SysMutex;

typedef SysMutex SysCriticalSection;

class SysMutex
{
	friend class SysAutoMutex;

private:
	const u32 m_nSpinCount;
	std::recursive_mutex m_Mutex;

public:
	SysMutex(u32 nSpinCount = 1000) : m_nSpinCount(nSpinCount) {}
	~SysMutex() {}

	SysMutex(const SysMutex& rhs) = delete;
	SysMutex& operator=(const SysMutex& rhs) = delete;

	void Lock();
	bool TryLock();
	void Unlock();

public:

	friend void SysCreateMutex(SysMutex& sysMutex, bool bInitialOwner = false);
	friend void SysCloseMutex(SysMutex& sysMutex);
};

__forceinline void SysMutex::Lock()
{ 
	u32 nCurrSpin = m_nSpinCount; 
	while(nCurrSpin--)
	{
		if(TryLock()) 
			return;
	} 
	m_Mutex.lock(); 
}

__forceinline bool SysMutex::TryLock()
{
	return m_Mutex.try_lock(); 
}

__forceinline void SysMutex::Unlock()
{
	m_Mutex.unlock();
}


class SysAutoMutex;

typedef SysAutoMutex SysAutoCriticalSection;

class SysAutoMutex
{
private:
	SysMutex& m_Mutex;

public:
	SysAutoMutex(SysMutex& sysMutex) :
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

#endif // SYSMUTEX_H