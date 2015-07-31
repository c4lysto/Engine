#ifndef _RECON_SYSSEMAPHORE_H_
#define _RECON_SYSSEMAPHORE_H_

#include "UtilitiesInclude.h"

namespace recon
{

// Semaphore Can Only Be Created Via SysCreateSemaphore(SysSemaphore&, int)
// Semaphore Must Be Closed Via SysCloseSemaphore(SysSemaphore&)
class SysSemaphore
{
public:
	typedef void* Handle;

private:
	SysSemaphore::Handle m_Semaphore;

public:
	SysSemaphore();
	~SysSemaphore();

	SysSemaphore(const SysSemaphore& rhs) = delete;
	SysSemaphore& operator=(const SysSemaphore& rhs) = delete;

	void Wait();
	bool TryWait();
	void Unlock(int nSignalCount = 1);

public:

	friend void SysCreateSemaphore(SysSemaphore& sysSemaphore, int nInitialCount = 0);
	friend void SysCloseSemaphore(SysSemaphore& sysSemaphore);
};

} // namespace recon

#endif // _RECON_SYSSEMAPHORE_H_