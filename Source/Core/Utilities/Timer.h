#ifndef _RECON_TIMER_H_
#define _RECON_TIMER_H_

#include <chrono>

#include "UtilitiesInclude.h"

namespace recon
{

enum class TimeInterval
{
	Hours = 0,
	Minutes,
	Seconds,
	Milliseconds,
	Microseconds,
	Nanoseconds,
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
	template<> static __forceinline TimeDuration In<TimeInterval::Hours>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::ratio<3600>>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Minutes>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::ratio<60>>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Seconds>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Milliseconds>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::milli>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Microseconds>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::micro>(fDuration)); return tmp; }
	template<> static __forceinline TimeDuration In<TimeInterval::Nanoseconds>(const f32& fDuration) { TimeDuration tmp; tmp.m_timeDuration = std::chrono::duration_cast<_TimeDuration>(std::chrono::duration<f32, std::nano>(fDuration)); return tmp; }


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
	__forceinline f32 Get() const { static_assert(false, "TimeDuration::Get<>() Template NOT Implemented Please Use A Template Argument From The recon::TimeInterval Enum"); }

	template<> __forceinline f32 Get<TimeInterval::Hours>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::ratio<3600>>>(m_timeDuration).count(); }
	template<> __forceinline f32 Get<TimeInterval::Minutes>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::ratio<60>>>(m_timeDuration).count(); }
	template<> __forceinline f32 Get<TimeInterval::Seconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32>>(m_timeDuration).count(); }
	template<> __forceinline f32 Get<TimeInterval::Milliseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::milli>>(m_timeDuration).count(); }
	template<> __forceinline f32 Get<TimeInterval::Microseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::micro>>(m_timeDuration).count(); }
	template<> __forceinline f32 Get<TimeInterval::Nanoseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::nano>>(m_timeDuration).count(); }
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
};


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

	template<> __forceinline f32 GetDeltaTime<TimeInterval::Hours>() const { return m_ElapsedTimeDuration.Get<TimeInterval::Hours>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Minutes>() const { return m_ElapsedTimeDuration.Get<TimeInterval::Minutes>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Seconds>() const { return m_ElapsedTimeDuration.Get<TimeInterval::Seconds>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Milliseconds>() const { return m_ElapsedTimeDuration.Get<TimeInterval::Milliseconds>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Microseconds>() const { return m_ElapsedTimeDuration.Get<TimeInterval::Microseconds>(); }
	template<> __forceinline f32 GetDeltaTime<TimeInterval::Nanoseconds>() const { return m_ElapsedTimeDuration.Get<TimeInterval::Nanoseconds>(); }
};

enum class GameTimer
{
	UnDialated = 0,
	UI = UnDialated,

	Dialated,
	Game = Dialated,

	LastFrame,
	NumTimers
};

class GameClock
{
private:
	static Timer ms_Timers[(u32)GameTimer::NumTimers];

public:

	static void Init();

	static void Update(f32 fTimeDialation = 1.0f);

	static __forceinline f32 GetDeltaTime(GameTimer gameTimer) \
	{ \
		Assertf(gameTimer >= GameTimer::UnDialated && gameTimer < GameTimer::NumTimers, "GameClock - Attempting To Query An Invalid Timer!"); \
		return ms_Timers[(u32)gameTimer].GetDeltaTime<TimeInterval::Seconds>(); \
	}

	static __forceinline f32 GetDialatedDT() { return GetDeltaTime(GameTimer::Dialated); }
	static __forceinline f32 GetGameDeltaTime() { return GetDialatedDT(); }

	static __forceinline f32 GetUnDialatedDT() { return GetDeltaTime(GameTimer::UnDialated); }
	static __forceinline f32 GetUIDeltaTime() { return GetUnDialatedDT(); }

	static __forceinline f32 GetLastFrameDeltaTime() { return GetDeltaTime(GameTimer::LastFrame); }


	static __forceinline f32 GetFrameRate() { return 1.0f / GetUnDialatedDT(); }
};

} // namespace recon

#endif // _RECON_TIMER_H_