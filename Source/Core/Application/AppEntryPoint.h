#ifndef _RECON_APPENTRYPOINT_H_
#define _RECON_APPENTRYPOINT_H_

#include <type_traits>

#include "../Utilities/CmdLineArg.h"
#include "../Utilities/CmdLineManager.h"
#include "../Utilities/UtilitiesInclude.h"

// Register New App Via REGISTER_APPLICATION In The Application's *.cpp File!
#define RECON_REGISTER_APPLICATION(appClass, appName) \
	/*{*/ \
		static_assert(std::is_base_of<recon::IApplication, appClass>::value, "App MUST Be Derived From 'IApplication'"); \
		recon::IApplication* recon::AppEntryPoint::ms_pApp = new appClass( #appName ); \
		/*ms_pApp->SetAppName(appName);*/ \
	/*}*/

namespace recon
{

class IApplication;

enum class AppState
{
	Prologue,
	Init,
	Run,
	Shutdown,
	Epilogue,

	// Means Waiting For A State Change, 
	// Window Will Continue To Loop And App Will Not Get Any Update Calls
	// Useful once Init gets called as well as Shutdown
	Pending
};

class AppEntryPoint final
{
private:
	static AppState ms_AppState;
	static IApplication* ms_pApp;

public:
	static bool InitEntryPoint(int argc, char** argv);
	static int ExecuteApp();
	static void ShutdownEntryPoint();

	static AppState GetState() { return ms_AppState; }
	static void SetState(AppState appState) { ms_AppState = appState; }

	static IApplication* GetApp() { return ms_pApp; }
};

} // namespace recon

#endif // _RECON_APPENTRYPOINT_H_
