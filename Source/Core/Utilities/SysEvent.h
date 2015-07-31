#ifndef _RECON_SYSEVENT_H_
#define _RECON_SYSEVENT_H_

#include "UtilitiesInclude.h"

namespace recon
{

// Event Can Only Be Created Via SysCreateEvent(bool,bool)
// Event Must Be Closed Via SysCloseEvent(SysEvent&)
class SysEvent
{
public:
	typedef void* Handle;

private:
	SysEvent::Handle m_Event;

public:
	SysEvent();
	~SysEvent();

	void Wait();
	bool IsSignaled();
	void Signal();

public:

	friend void SysCreateEvent(SysEvent& sysEvent, bool bInitiallySignaled = false);
	friend void SysCloseEvent(SysEvent& sysEvent);
};

} // namespace recon

#endif // _RECON_SYSEVENT_H_