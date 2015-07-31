#ifndef _RECON_SYSMUTEX_H_
#define _RECON_SYSMUTEX_H_

#include "UtilitiesInclude.h"

#include <mutex>

namespace recon
{

class SysMutex
{
	friend class SysLocalMutex;

public:
	typedef std::mutex::native_handle_type Handle;

private:
	std::mutex m_Mutex;

public:
	SysMutex() {}
	~SysMutex() {}

	SysMutex(const SysMutex& rhs) = delete;
	SysMutex& operator=(const SysMutex& rhs) = delete;

	void Lock() {m_Mutex.lock();}
	bool TryLock() {return m_Mutex.try_lock();}
	void Unlock() {m_Mutex.unlock();}

public:

	friend void SysCreateMutex(SysMutex& sysMutex, bool bInitialOwner = false);
	friend void SysCloseMutex(SysMutex& sysMutex);
};


class SysLocalMutex
{
private:
	std::lock_guard<std::mutex> m_Lock;

public:
	SysLocalMutex(SysMutex& sysMutex) :
		m_Lock(sysMutex.m_Mutex)
	{
	}
	
	~SysLocalMutex()
	{
	}
};

} // namespace recon

#endif // SYSMUTEX_H