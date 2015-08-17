#ifndef _RECON_EVENT_H_
#define _RECON_EVENT_H_

#include "Semaphore.h"

namespace recon
{

class Event
{

private:
	Semaphore m_Semaphore;

public:
	Event() : m_Semaphore(1) { }
	~Event() { }

	Event(const Event& rhs) = delete;
	Event& operator=(const Event& rhs) = delete;

	void Wait() { m_Semaphore.Acquire(); }

	void Signal() { m_Semaphore.Release(); }
};

} // namespace recon

#endif // _RECON_EVENT_H_