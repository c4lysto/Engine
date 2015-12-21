#include "Timer.h"

namespace recon
{
	Timer GameClock::ms_Timers[];

	COMMENT(static) void GameClock::Init()
	{

	}

	COMMENT(static) void GameClock::Update(f32 fTimeDialation /*= 1.0f*/)
	{
		ms_Timers[(u32)GameTimer::LastFrame] = ms_Timers[(u32)GameTimer::UnDialated];

		TimePoint currTimePoint = Timer::Now();

		Timer& normalTimer = ms_Timers[(u32)GameTimer::UnDialated];
		normalTimer.Update(currTimePoint);

		Timer& dialatedTimer = ms_Timers[(u32)GameTimer::Dialated];
		dialatedTimer.UpdateWithDialation(currTimePoint, fTimeDialation);
	}

} // namespace recon