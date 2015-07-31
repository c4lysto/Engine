#include "SysEvent.h"

namespace recon
{

SysEvent::SysEvent()
{
	m_Event = nullptr;
}

SysEvent::~SysEvent()
{
	SysCloseEvent(*this);
}

void SysEvent::Wait()
{
	if(m_Event)
	{
		WaitForSingleObject(m_Event, INFINITE);
	}
}

bool SysEvent::IsSignaled()
{
	if(m_Event)
	{
		return (WaitForSingleObject(m_Event, 0) == WAIT_OBJECT_0);
	}

	return false;
}

void SysEvent::Signal()
{
	if(m_Event)
		SetEvent(m_Event);
}

void SysCreateEvent(SysEvent& sysEvent, bool bInitiallySignaled /*= false*/)
{
	SysCloseEvent(sysEvent);

	SysEvent::Handle pEvent = CreateEvent(false, false, bInitiallySignaled, nullptr);
	Assert(pEvent, "Failed To Create SysEvent!");

	if(pEvent)
		sysEvent.m_Event = pEvent;
}

void SysCloseEvent(SysEvent& sysEvent)
{
	if(sysEvent.m_Event)
	{
		CloseHandle(sysEvent.m_Event);
		sysEvent.m_Event = nullptr;
	}
}

} // namespace recon