#ifndef _RECON_TIMER_H_
#define _RECON_TIMER_H_

#include "Time.h"

namespace recon
{

class Timer
{
private:
	TimePoint m_PrevTimePoint;
	TimeDuration m_ElapsedTimeDuration;

public:
	static __forceinline TimePoint Now() { return TimePoint::Now(); }

public:
	Timer()
	{
		Reset();
	}

	Timer(const Timer& rhs) :
		m_PrevTimePoint(rhs.m_PrevTimePoint),
		m_ElapsedTimeDuration(rhs.m_ElapsedTimeDuration)
	{
	}

	~Timer() {}

	Timer& operator=(const Timer& rhs)
	{
		if(this != &rhs)
		{
			m_PrevTimePoint = rhs.m_PrevTimePoint;
			m_ElapsedTimeDuration = rhs.m_ElapsedTimeDuration;
		}
		return *this;
	}

	__forceinline void Reset()
	{
		m_PrevTimePoint = TimePoint::Now();
		m_ElapsedTimeDuration = TimeDuration();
	}

	__forceinline void Update(const TimePoint& now)
	{
		m_ElapsedTimeDuration = now - m_PrevTimePoint;
		m_PrevTimePoint = now;
	}

	__forceinline void Update()
	{
		return Update(TimePoint::Now());
	}

	__forceinline void UpdateWithDialation(const TimePoint& now, const f32& fTimeDialation)
	{
		m_ElapsedTimeDuration = (now - m_PrevTimePoint) * TimeDuration::In<TimeInterval::Seconds>(fTimeDialation);
		m_PrevTimePoint = now;
	}

	__forceinline void UpdateWithDialation(const f32& fTimeDialation)
	{
		return UpdateWithDialation(TimePoint::Now(), fTimeDialation);
	}

	template<TimeInterval _Interval>
	f32 GetDeltaTime() const { static_assert(false, "Timer::GetDeltaTime<>() Template NOT Implemented Please Use A Template Argument From The recon::TimeInterval Enum"); }

	template<> __forceinline f32 GetDeltaTime<TimeInterval::Days>() const { return m_ElapsedTimeDuration.GetAs<TimeInterval::Days>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Hours>() const { return m_ElapsedTimeDuration.GetAs<TimeInterval::Hours>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Minutes>() const { return m_ElapsedTimeDuration.GetAs<TimeInterval::Minutes>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Seconds>() const { return m_ElapsedTimeDuration.GetAs<TimeInterval::Seconds>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Milliseconds>() const { return m_ElapsedTimeDuration.GetAs<TimeInterval::Milliseconds>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Microseconds>() const { return m_ElapsedTimeDuration.GetAs<TimeInterval::Microseconds>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Nanoseconds>() const { return m_ElapsedTimeDuration.GetAs<TimeInterval::Nanoseconds>(); }
};

} // namespace recon

#endif // _RECON_TIMER_H_