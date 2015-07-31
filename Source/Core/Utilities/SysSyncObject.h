#ifndef _RECON_SYSSYNCOBJECT_H_
#define _RECON_SYSSYNCOBJECT_H_
#include "UtilitiesInclude.h"

namespace recon
{

class SysSyncObject
{
	friend class SysSyncObjectMultiple;

protected:
	void* m_pHandle;

public:
	SysSyncObject();
	SysSyncObject(void* pWaitHandle);
	~SysSyncObject();

	void SetHandle(void* pWaitHandle);

	void Wait(unsigned int nWaitTimeInMS = INFINITE);

	// Returns True if the Object is already signaled
	bool TryWait(unsigned int nWaitTimeInMS = 0);
};

class SysSyncObjectMultiple
{
private:
#ifdef RECON_OS_WINDOWS
	static const size_t MAX_WAIT_HANDLES = MAXIMUM_WAIT_OBJECTS;
#else
	static const size_t MAX_WAIT_HANDLES = 64;
#endif

private:
	int m_nNumWaitHandles;
	void* m_pHandles[MAX_WAIT_HANDLES];

public:
	SysSyncObjectMultiple();
	~SysSyncObjectMultiple();

	void AddSyncObject(const SysSyncObject& hWaitObject);
	void RemoveSyncObject(const SysSyncObject& hWaitHandle);

	void ClearWaitHandles();

	void Wait();
	bool WaitAny();
};

} // namespace recon

#endif // _RECON_SYSSYNCOBJECT_H_