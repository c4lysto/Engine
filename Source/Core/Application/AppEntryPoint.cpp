#include "AppEntryPoint.h"

#include "Application.h"
#include "../Utilities/Thread.h"

namespace recon
{

AppState AppEntryPoint::ms_AppState = AppState::Prologue;
//IApplication* AppEntryPoint::ms_pApp = nullptr;

bool AppEntryPoint::InitEntryPoint(int argc, char** argv)
{
	if(!Verifyf(ms_pApp, "App Entry Point Already Created!"))
	{
		return false;
	}

	ms_pApp->InitCmdLineArgsConfigType();
	CmdLineManager::ProcessCmdLineArgs(argc, argv);

	Thread::InitMainThread();

	return true;
}

int AppEntryPoint::ExecuteApp()
{
	int returnCode = 0;

	if(Verifyf(ms_pApp, "App Not Yet Created!"))
	{
		while(ms_AppState != AppState::Epilogue)
		{
			ms_pApp->Run(ms_AppState);
		}
	}

	return returnCode;
}

void AppEntryPoint::ShutdownEntryPoint()
{
	if(ms_pApp)
	{
		delete ms_pApp;
		ms_pApp = nullptr;
	}

	CmdLineManager::ShutdownCmdLineArgs();
}

} // namespace recon
