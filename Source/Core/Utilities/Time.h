#ifndef _RECON_TIME_H_
#define _RECON_TIME_H_

#include <chrono>

#include "UtilitiesInclude.h"

namespace recon
{

enum class TimeInterval
{	
	Nanoseconds = 0,
	Microseconds,
	Milliseconds,
	Seconds,
	Minutes,
	Hours,
	Days,
	NumIntervals
};

class TimeDuration
{
	friend class TimePoint;

	typedef std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period> _TimeDuration;

private:
	_TimeDuration m_timeDuration;

public:
	TimeDuration() : m_timeDuration(_TimeDuration::zero()) {}
	TimeDuration(const TimeDuration& rhs) : m_timeDuration(rhs.m_timeDuration) {}

	template<TimeInterval _Interval>
	static __forceinline TimeDuration In(const f32& fDuration) { static_assert(false, "TimeDuration::In<>() Template NOT Implemented Please Use A Template Argument From The recon::TimeInterval Enum"); }
	template<> static __forceinline TimeDuration In<TimeInterval::Nanoseconds>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::nano>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Microseconds>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::micro>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Milliseconds>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::milli>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Seconds>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Minutes>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::ratio<60>>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Hours>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::ratio<3600>>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Days>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::ratio<86400>>(fDuration)); return tmp; }
	


	TimeDuration& operator=(const TimeDuration& rhs)
	{
		if(this != &rhs)
		{
			m_timeDuration = rhs.m_timeDuration;
		}
		return *this;
	}

	__forceinline TimeDuration operator+(const TimeDuration& rhs) const { TimeDuration tmp(*this); tmp.m_timeDuration += rhs.m_timeDuration; return tmp; }
	__forceinline TimeDuration& operator+=(const TimeDuration& rhs) { m_timeDuration += rhs.m_timeDuration; return *this; }

	__forceinline TimeDuration operator-(const TimeDuration& rhs) const { TimeDuration tmp(*this); tmp.m_timeDuration -= rhs.m_timeDuration; return tmp; }
	__forceinline TimeDuration& operator-=(const TimeDuration& rhs) { m_timeDuration -= rhs.m_timeDuration; return *this; }

	__forceinline TimeDuration operator*(const TimeDuration& rhs) const { TimeDuration tmp(*this); tmp.m_timeDuration *= rhs.m_timeDuration.count(); return tmp; }
	__forceinline TimeDuration& operator*=(const TimeDuration& rhs) { m_timeDuration *= rhs.m_timeDuration.count(); return *this; }

	__forceinline TimeDuration operator/(const TimeDuration& rhs) const { TimeDuration tmp(*this); tmp.m_timeDuration /= rhs.m_timeDuration.count(); return tmp; }
	__forceinline TimeDuration& operator/=(const TimeDuration& rhs) { m_timeDuration /= rhs.m_timeDuration.count(); return *this; }

	__forceinline bool operator==(const TimeDuration& rhs) const { return m_timeDuration == rhs.m_timeDuration; }
	__forceinline bool operator!=(const TimeDuration& rhs) const { m_timeDuration != rhs.m_timeDuration; }

	__forceinline bool operator<(const TimeDuration& rhs) const { return m_timeDuration < rhs.m_timeDuration; }
	__forceinline bool operator<=(const TimeDuration& rhs) const { m_timeDuration <= rhs.m_timeDuration; }

	__forceinline bool operator>(const TimeDuration& rhs) const { return m_timeDuration > rhs.m_timeDuration; }
	__forceinline bool operator>=(const TimeDuration& rhs) const { m_timeDuration >= rhs.m_timeDuration; }


	template<TimeInterval _Interval>
	__forceinline f32 GetAs() const { static_assert(false, "TimeDuration::Get<>() Template NOT Implemented Please Use A Template Argument From The recon::TimeInterval Enum"); }

	template<> __forceinline f32 GetAs<TimeInterval::Nanoseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::nano>>(m_timeDuration).count(); }
	template<> __forceinline f32 GetAs<TimeInterval::Microseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::micro>>(m_timeDuration).count(); }
	template<> __forceinline f32 GetAs<TimeInterval::Milliseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::milli>>(m_timeDuration).count(); }
	template<> __forceinline f32 GetAs<TimeInterval::Seconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32>>(m_timeDuration).count(); }
	template<> __forceinline f32 GetAs<TimeInterval::Minutes>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::ratio<60>>>(m_timeDuration).count(); }
	template<> __forceinline f32 GetAs<TimeInterval::Hours>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::ratio<3600>>>(m_timeDuration).count(); }
	template<> __forceinline f32 GetAs<TimeInterval::Days>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::ratio<86400>>>(m_timeDuration).count(); }
};


class TimePoint
{
	typedef std::chrono::high_resolution_clock::time_point _TimePoint;

private:
	_TimePoint m_timePoint;

public:
	static __forceinline TimePoint Now() { TimePoint tmp; tmp.m_timePoint = std::chrono::high_resolution_clock::now(); return tmp; }

public:
	TimePoint() { }
	TimePoint(const TimePoint& rhs) : m_timePoint(rhs.m_timePoint) {}

	TimePoint& operator=(const TimePoint& rhs)
	{
		if(this != &rhs)
		{
			m_timePoint = rhs.m_timePoint;
		}
		return *this;
	}

	__forceinline TimePoint operator+(const TimeDuration& rhs) const { TimePoint tmp; tmp.m_timePoint = m_timePoint + rhs.m_timeDuration; return tmp; }
	__forceinline TimePoint& operator+=(const TimeDuration& rhs) { m_timePoint += rhs.m_timeDuration; return *this; }

	__forceinline TimePoint operator-(const TimeDuration& rhs) const { TimePoint tmp; tmp.m_timePoint = m_timePoint - rhs.m_timeDuration; return tmp; }
	__forceinline TimePoint& operator-=(const TimeDuration& rhs) { m_timePoint -= rhs.m_timeDuration; return *this; }
	__forceinline TimeDuration operator-(const TimePoint& rhs) const { TimeDuration tmp; tmp.m_timeDuration = m_timePoint - rhs.m_timePoint; return tmp;}

	__forceinline bool operator==(const TimePoint& rhs) const { return m_timePoint == rhs.m_timePoint; }
	__forceinline bool operator!=(const TimePoint& rhs) const { return m_timePoint != rhs.m_timePoint; }

	__forceinline bool operator<(const TimePoint& rhs) const { return m_timePoint < rhs.m_timePoint; }
	__forceinline bool operator<=(const TimePoint& rhs) const { return m_timePoint <= rhs.m_timePoint; }

	__forceinline bool operator>(const TimePoint& rhs) const { return m_timePoint > rhs.m_timePoint; }
	__forceinline bool operator>=(const TimePoint& rhs) const { return m_timePoint >= rhs.m_timePoint; }


	template<TimeInterval _Interval>
	__forceinline f32 GetAs() const { static_assert(false, "TimePoint::GetAs<>() Template NOT Implemented Please Use A Template Argument From The recon::TimeInterval Enum"); }

	template<> __forceinline f32 GetAs<TimeInterval::Nanoseconds>() const { return (*this - TimePoint()).GetAs<TimeInterval::Nanoseconds>(); }
	template<> __forceinline f32 GetAs<TimeInterval::Microseconds>() const { return (*this - TimePoint()).GetAs<TimeInterval::Microseconds>(); }
	template<> __forceinline f32 GetAs<TimeInterval::Milliseconds>() const { return (*this - TimePoint()).GetAs<TimeInterval::Milliseconds>(); }
	template<> __forceinline f32 GetAs<TimeInterval::Seconds>() const { return (*this - TimePoint()).GetAs<TimeInterval::Seconds>(); }
	template<> __forceinline f32 GetAs<TimeInterval::Minutes>() const { return (*this - TimePoint()).GetAs<TimeInterval::Minutes>(); }
	template<> __forceinline f32 GetAs<TimeInterval::Hours>() const { return (*this - TimePoint()).GetAs<TimeInterval::Hours>(); }
	template<> __forceinline f32 GetAs<TimeInterval::Days>() const { return (*this - TimePoint()).GetAs<TimeInterval::Days>(); }
};

} // namespace recon

#endif // _RECON_TIME_H_