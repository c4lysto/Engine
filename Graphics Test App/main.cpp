#include <Windows.h>

#include "../Source/Core/Application/AppEntryPoint.h"

#if RECON_OS_WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	int returnCode = -1;

	if(recon::AppEntryPoint::InitEntryPoint())
	{
		LPWSTR arguments = GetCommandLineW();

		int argc;
		LPWSTR* argv = CommandLineToArgvW(arguments, &argc);

		returnCode = recon::AppEntryPoint::ExecuteApp(argc, argv);

		recon::AppEntryPoint::ShutdownEntryPoint();
	}

	return returnCode;
}
#else
	#error "Unhandled OS Application Type, Not Sure Of Entry Point Syntax!"
#endif