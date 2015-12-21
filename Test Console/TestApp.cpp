#include "TestApp.h"

#include <windows.h>
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
