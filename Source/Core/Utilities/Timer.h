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
		Nanoseconds
	};

	class Timer
	{
	public:
		typedef std::chrono::high_resolution_clock::time_point TimePoint;

	private:
		typedef std::chrono::duration<std::chrono::system_clock::rep, std::chrono::system_clock::period> TimeDuration;

	private:
		TimePoint m_PrevTimePoint;
		TimeDuration m_ElapsedTimeDuration;

	public:
		__forceinline static TimePoint Now() { return std::chrono::high_resolution_clock::now(); }

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
			m_PrevTimePoint = Timer::Now();
			m_ElapsedTimeDuration = TimeDuration::zero();
		}

		__forceinline void Update(const TimePoint& now)
		{
			m_ElapsedTimeDuration = now - m_PrevTimePoint;
			m_PrevTimePoint = now;
		}

		__forceinline void Update()
		{
			return Update(Timer::Now());
		}

		__forceinline void UpdateWithDialation(const TimePoint& now, const f32& fTimeDialation)
		{
			std::chrono::duration<f32> dialatedTime(fTimeDialation);
			m_ElapsedTimeDuration = (now - m_PrevTimePoint) * std::chrono::duration_cast<TimeDuration>(dialatedTime).count();
			m_PrevTimePoint = now;
		}

		__forceinline void UpdateWithDialation(const f32& fTimeDialation)
		{
			return UpdateWithDialation(Timer::Now(), fTimeDialation);
		}

		template<TimeInterval _Interval>
		f32 GetDeltaTime() const { static_assert(false, "Timer::GetDeltaTime<>() Template NOT Implemented Please Use A Template Argument From The recon::TimeInterval Enum"); }

		template<> __forceinline f32 GetDeltaTime<TimeInterval::Hours>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::ratio<3600>>>(m_ElapsedTimeDuration).count(); }
		template<> __forceinline f32 GetDeltaTime<TimeInterval::Minutes>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::ratio<60>>>(m_ElapsedTimeDuration).count(); }
		template<> __forceinline f32 GetDeltaTime<TimeInterval::Seconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32>>(m_ElapsedTimeDuration).count(); }
		template<> __forceinline f32 GetDeltaTime<TimeInterval::Milliseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::milli>>(m_ElapsedTimeDuration).count(); }
		template<> __forceinline f32 GetDeltaTime<TimeInterval::Microseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::micro>>(m_ElapsedTimeDuration).count(); }
		template<> __forceinline f32 GetDeltaTime<TimeInterval::Nanoseconds>() const { return std::chrono::duration_cast<std::chrono::duration<f32, std::nano>>(m_ElapsedTimeDuration).count(); }
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