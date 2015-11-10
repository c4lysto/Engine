#ifndef _RECON_APPWINDOW_H_
#define _RECON_APPWINDOW_H_

#include "../Utilities/UtilitiesInclude.h"

#include "../Utilities/Function.h"

namespace recon
{

#if RECON_OS_WINDOWS
typedef void* WindowMessageHandlerArgs;
#else
typedef void* WindowMessageHandlerArgs;
#endif

// Return True To Allow Default App Proc To Handle Mesage
// Return False To NOT Allow Default App Proc To Handle Message
typedef bool WindowMessageHandlerReturn;
typedef recon::Function<WindowMessageHandlerReturn(WindowMessageHandlerArgs)> WindowMessageHandler;

enum class AppState;

class IAppWindow
{
protected:
	static WindowMessageHandler ms_WindowMessageHandler;

public:
	void Run(AppState appState);

	virtual const WindowMessageHandler& GetWindowMessageHandler() const { return ms_WindowMessageHandler; };
	virtual void SetWindowMessageHandler(WindowMessageHandler& messageHandler) { ms_WindowMessageHandler = messageHandler; }

protected:
	virtual bool Init() = 0;
	virtual void RunSingleLoop() = 0;
	virtual void Shutdown() = 0;
};

} // namespace recon

#endif // _RECON_APPWINDOW_H_