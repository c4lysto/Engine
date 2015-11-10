#include "AppEntryPoint.h"

#include "Application.h"

#include "AppWindow_Windows.h"

namespace recon
{

AppState AppEntryPoint::ms_AppState = AppState::Prologue;
IAppWindow* AppEntryPoint::ms_pAppWindow = nullptr;
//IApplication* AppEntryPoint::ms_pApp = nullptr;

bool AppEntryPoint::InitEntryPoint()
{
	if(!Verifyf(ms_pApp, "App Entry Point Already Created!"))
	{
		return false;
	}

	if(Verifyf(!ms_pAppWindow, "App Entry Point Already Created!"))
	{
#if RECON_OS_WINDOWS
		ms_pAppWindow = new AppWindow_Windows;
#else
#error "Unhandled OS Entry Point!"
		return false;
#endif //
	}

	return true;
}

int AppEntryPoint::ExecuteApp(int argc, wchar_t** argv)
{
	int returnCode = 0;

	if(Verifyf(ms_pAppWindow, "App Window Not Yet Created!") &&
	   Verifyf(ms_pApp, "App Not Yet Created!"))
	{
		wchar_t* arg0 = argv[0];

		ms_pApp->ProcessCmdLineArgs(argc, argv);

		while(ms_AppState != AppState::Epilogue)
		{
			ms_pAppWindow->Run(ms_AppState);
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

	delete ms_pAppWindow;
	ms_pAppWindow = nullptr;
}

} // namespace recon
