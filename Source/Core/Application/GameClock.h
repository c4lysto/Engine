#ifndef _RECON_GAMECLOCK_H_
#define _RECON_GAMECLOCK_H_

#include "../Utilities/Timer.h"

namespace recon
{

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

#endif // _RECON_DEFAULTGAMEAPP_H_
