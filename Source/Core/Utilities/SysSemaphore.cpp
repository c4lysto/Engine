#include "SysSemaphore.h"

namespace recon
{

SysSemaphore::SysSemaphore()
{
	m_Semaphore = nullptr;
}

SysSemaphore::~SysSemaphore()
{
	SysCloseSemaphore(*this);
}

void SysSemaphore::Wait()
{
	if(m_Semaphore)
	{
		WaitForSingleObject(m_Semaphore, INFINITE);
	}
}

bool SysSemaphore::TryWait()
{
	if(m_Semaphore)
	{
		return (WaitForSingleObject(m_Semaphore, 0) == WAIT_OBJECT_0);
	}

	return false;
}

void SysSemaphore::Unlock(int nSignalCount /*= 1*/)
{
	if(m_Semaphore)
		ReleaseSemaphore(m_Semaphore, nSignalCount, NULL);
}

void SysCreateSemaphore(SysSemaphore& sysSemaphore, int nInitialCount /*= 0*/)
{
	SysCloseSemaphore(sysSemaphore);

	SysSemaphore::Handle pSemaphore = CreateSemaphore(nullptr, nInitialCount, LONG_MAX, nullptr);
	Assertf(pSemaphore, "Failed To Create Semaphore!");

	if(pSemaphore)
		sysSemaphore.m_Semaphore = pSemaphore;
}

void SysCloseSemaphore(SysSemaphore& sysSemaphore)
{
	if (sysSemaphore.m_Semaphore)
	{
		CloseHandle(sysSemaphore.m_Semaphore);
		sysSemaphore.m_Semaphore = nullptr;
	}
}

} // namespace recon