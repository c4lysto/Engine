#ifndef _RECON_SYSEVENT_H_
#define _RECON_SYSEVENT_H_

#include "SysSemaphore.h"

namespace recon
{

class SysEvent
{

private:
	SysSemaphore m_Semaphore;

public:
	SysEvent() : m_Semaphore(1) { }
	~SysEvent() { }

	SysEvent(const SysEvent& rhs) = delete;
	SysEvent& operator=(const SysEvent& rhs) = delete;

	void Wait() { m_Semaphore.Acquire(); }

	void Signal() { m_Semaphore.Release(); }
};

} // namespace recon

#endif // _RECON_SYSEVENT_H_