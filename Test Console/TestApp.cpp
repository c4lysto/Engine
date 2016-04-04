#include "TestApp.h"

#include <iostream>
#include <random>
#include "Utilities/Random.h"
#include "Utilities/Timer.h"

#include "../Source/Core/Application/AppEntryPoint.h"

RECON_REGISTER_APPLICATION(TestApp, Test App)

TestApp::TestApp(const std::string& appName) : recon::IApplication(appName)
{

}

TestApp::~TestApp()
{

}

void TestApp::Run(recon::AppState currState)
{
	recon::IApplication::Run(currState);

	if(currState == recon::AppState::Run)
	{
		std::cout << "Running Test App" << std::endl;

		Vector128 vec = VectorF32ToF16(VectorSet(1.0f, 2.0f, 3.0f, 4.0f));
		Vector128 vec2 = VectorF32ToF16(VectorSet(1.0f, 2.0f, 3.0f, 4.0f), VectorSet(5.0f, 6.0f, 7.0f, 8.0f));

		Vector128 vec3 = VectorF16ToF32(vec2);
		
		Vector128 vec4, vec5;
		VectorF16ToF32(vec2, vec4, vec5);

		std::cout << Max(0, 5, 10, 3, 2, 50, 49, -12, 15) << std::endl;
		f32 fVal = Min(-5, 11.546819681);
		std::cout << Min(5, -11.546819681) << std::endl;//, 3, 2, 50, 49, -12, 15) << std::endl;

		Vec4V vMin = Max(Vec4V(I_ONE), Vec4V(I_NEG_ONE), Vec4V(500.0f, -30.0f, 10000.0f, -75.254689681f), Vec4V(-10.0f));

		s32 loopCount = 100000000;
		s32 randVal = 0;

		recon::Timer tstTimer;
		tstTimer.Reset();
		for(int i = 0; i < loopCount; ++i)
		{
			randVal += recon::Rand::Draw(0, 100);
		}
		tstTimer.Update();

		std::cout << "Rand Val: " << randVal << "\nTotal Time: " << tstTimer.GetDeltaTime<recon::TimeInterval::Seconds>();

		randVal = 0;
		std::mt19937 stdRand;
		std::uniform_int_distribution<s32> stdRandRange(0, 100);
		tstTimer.Reset();
		for(s32 i = 0; i < loopCount; ++i)
		{
			randVal += stdRandRange(stdRand);
		}
		tstTimer.Update();

		std::cout << "Rand Val: " << randVal << "\nTotal Time: " << tstTimer.GetDeltaTime<recon::TimeInterval::Seconds>();


		recon::AppEntryPoint::SetState(recon::AppState::Shutdown);
	}
	
}

void TestApp::InitCmdLineArgsConfigType()
{
	//recon::CmdLineManager::AddCmdLineArgConfigTypes("x64");
}

bool TestApp::Init()
{
	recon::IApplication::Init();

#if RECON_DEBUG && RECON_OS_WINDOWS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	recon::CmdLineArg arg_AllocBreak("allocbreak");
	s32 allocBreak = -1;

	arg_AllocBreak.Get(allocBreak);

	_CrtSetBreakAlloc(allocBreak);
#endif // RECON_DEBUG

	return true;
}

void TestApp::Shutdown()
{
	recon::IApplication::Shutdown();
}
