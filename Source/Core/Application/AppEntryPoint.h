#ifndef _RECON_APPENTRYPOINT_H_
#define _RECON_APPENTRYPOINT_H_

#include <type_traits>

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
class IAppWindow;

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
	static IAppWindow* ms_pAppWindow;

public:
	static bool InitEntryPoint();
	static int ExecuteApp(int argc, wchar_t** argv);
	static void ShutdownEntryPoint();

	static AppState GetState() { return ms_AppState; }
	static void SetState(AppState appState) { ms_AppState = appState; }

	static IApplication* GetApp() { return ms_pApp; }
	static IAppWindow* GetWindow() { return ms_pAppWindow; }
};

} // namespace recon

#endif // _RECON_APPENTRYPOINT_H_
