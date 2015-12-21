#include <Windows.h>

#include "../Source/Core/Application/AppEntryPoint.h"

#if RECON_OS_WINDOWS
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
int main(int argc, char** argv)
{
	int returnCode = -1;

	if(recon::AppEntryPoint::InitEntryPoint(argc, argv))
	{
		returnCode = recon::AppEntryPoint::ExecuteApp();

		recon::AppEntryPoint::ShutdownEntryPoint();
	}

	return returnCode;
}
#else
	#error "Unhandled OS Application Type, Not Sure Of Entry Point Syntax!"
#endif