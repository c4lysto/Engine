#ifndef _RECON_SYS_CRITICAL_SECTION_H_
#define _RECON_SYS_CRITICAL_SECTION_H_

#include <Windows.h>

#include "UtilitiesInclude.h"

namespace recon
{

class SysCriticalSection
{
private:
	CRITICAL_SECTION m_CriticalSection;

public:
	inline SysCriticalSection(DWORD dwSpinCount = 1000);
	inline ~SysCriticalSection();

	// Undefined to avoid bad things.
	SysCriticalSection(const SysCriticalSection& rhs) = delete;
	SysCriticalSection& operator=(const SysCriticalSection& rhs) = delete;

	inline void Lock();
	inline bool TryLock();
	inline void Unlock();
};

// This Class Is Meant For An Easy Wrapper Of A Scoped Critical Section
class SysLocalCriticalSection
{
private:
	SysCriticalSection& m_CriticalSection;

public:
	inline SysLocalCriticalSection(SysCriticalSection& critSection, bool bAutoLock = true);
	inline ~SysLocalCriticalSection();

	// Undefined to avoid bad things.
	SysLocalCriticalSection(const SysLocalCriticalSection& rhs) = delete;
	SysLocalCriticalSection& operator=(const SysLocalCriticalSection& rhs) = delete;

	inline void Lock();
	inline void TryLock();
	inline void Unlock();
};

inline SysCriticalSection::SysCriticalSection(DWORD dwSpinCount /*= 1000*/)
{
	InitializeCriticalSectionAndSpinCount(&m_CriticalSection, dwSpinCount);
}

inline SysCriticalSection::~SysCriticalSection()
{
	DeleteCriticalSection(&m_CriticalSection);
}

inline void SysCriticalSection::Lock()
{
	EnterCriticalSection(&m_CriticalSection);
}

inline bool SysCriticalSection::TryLock()
{
	return TryEnterCriticalSection(&m_CriticalSection) ? true : false;
}

inline void SysCriticalSection::Unlock()
{
	if (m_CriticalSection.OwningThread == (void*)GetCurrentThreadId())
		LeaveCriticalSection(&m_CriticalSection);
}


inline SysLocalCriticalSection::SysLocalCriticalSection(SysCriticalSection& critSection, bool bAutoLock /*= true*/) : m_CriticalSection(critSection)
{
	if (bAutoLock)
		m_CriticalSection.Lock();
}

inline SysLocalCriticalSection::~SysLocalCriticalSection()
{
	Unlock();
}

inline void SysLocalCriticalSection::Lock()
{
	m_CriticalSection.Lock();
}

inline void SysLocalCriticalSection::TryLock()
{
	m_CriticalSection.TryLock();
}

inline void SysLocalCriticalSection::Unlock()
{
	m_CriticalSection.Unlock();
}

} // namespace recon

#endif // _RECON_SYS_CRITICAL_SECTION_H_