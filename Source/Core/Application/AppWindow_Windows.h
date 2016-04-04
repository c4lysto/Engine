#ifndef _RECON_APPWINDOW_WINDOWS_H_
#define _RECON_APPWINDOW_WINDOWS_H_

#include "AppWindow.h"

#if RECON_OS_WINDOWS

#include "../Utilities/Windows_Inc.h"

namespace recon
{

class AppWindow_Windows : public IAppWindow
{
public:
	struct WindowsMessageArgs
	{
		HWND hWnd;
		UINT msg;
		WPARAM wParam;
		LPARAM lParam;
	};

private:
	HWND m_hWnd;

public:
	AppWindow_Windows();
	~AppWindow_Windows();

	virtual bool Init() override;
	virtual void RunSingleLoop() override;
	virtual void Shutdown() override;

	HWND GetWindowHandle() const { return m_hWnd; }

private:
	bool SetupWindow();

	std::string GetWindowsClassName(const std::string& appName) const { return appName + " - WinClass"; }

	bool AlreadyRunning();
	bool RegisterWindow(HINSTANCE hInstance);
	HWND MakeWindow(HINSTANCE hInstance);
	bool RunMessageLoop(WPARAM& quitCode);

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static LONG WINAPI WriteDumpFile(_EXCEPTION_POINTERS* exceptions);
};

} // namespace recon

#endif // RECON_OS_WINDOWS

#endif // _RECON_APPWINDOW_WINDOWS_H_