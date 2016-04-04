#include "AppWindow_Windows.h"

#if RECON_OS_WINDOWS

#include "AppEntryPoint.h"
#include "Application.h"

#include <DbgHelp.h>
#pragma comment(lib,"dbghelp.lib")

namespace recon
{

static volatile bool WINDOWED_TMP = true;
static volatile int WINDOW_WIDTH_TMP = 1280;
static volatile int WINDOW_HEIGHT_TMP = 720;

AppWindow_Windows::AppWindow_Windows()
{
	m_hWnd = nullptr;
}

AppWindow_Windows::~AppWindow_Windows()
{

}

bool AppWindow_Windows::Init()
{
	//AppEntryPoint::Init(L"Tmp App Name");

	if(!SetupWindow())
	{
		return false;
	}

#ifdef RECON_DEBUG	
	//Assertf(recon::DebugWindow::Initialize(), "Failed To Create Debug Window");
#endif

	//g_InputManager.Initialize(m_hWnd);

	return true;
}

void AppWindow_Windows::RunSingleLoop()
{
	WPARAM ignore;
	RunMessageLoop(ignore);
}

void AppWindow_Windows::Shutdown()
{
	recon::DebugWindow::Shutdown();

	const std::string appName = AppEntryPoint::GetApp()->GetAppName();
	std::string className = GetWindowsClassName(appName);

	UnregisterClassA(className.c_str(), (HINSTANCE)GetModuleHandleA(NULL));
}

bool AppWindow_Windows::SetupWindow()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);

	SetUnhandledExceptionFilter(WriteDumpFile);

	if(AlreadyRunning())
		return FALSE;

	HINSTANCE hInstance = (HINSTANCE)GetModuleHandleA(NULL);

	if(!RegisterWindow(hInstance))
		return FALSE;

	m_hWnd = MakeWindow(hInstance);

	if(!Verifyf(m_hWnd, "Failed To Create Window! Error Code %d", GetLastError()))
	{
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOW);// nCmdShow);
	UpdateWindow(m_hWnd);

	return true;
}

bool AppWindow_Windows::RunMessageLoop(WPARAM& quitCode)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);

		/*if(msg.message == WM_QUIT)
		{
			quitCode = msg.wParam;
			// Shutdown Code Here!
			//g_InputManager.Shutdown();
			return false;
		}*/
	}

	//g_InputManager.ProcessInput();

	return true;
}

LRESULT CALLBACK AppWindow_Windows::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	bool bAllowDefaultCommandProcessing = true;

	if(ms_WindowMessageHandler)
	{
		WindowsMessageArgs windowMessageArgs = {hWnd, msg, wParam, lParam};
		bAllowDefaultCommandProcessing = ms_WindowMessageHandler(&windowMessageArgs);
	}

	if(bAllowDefaultCommandProcessing)
	{
		switch(msg)
		{
			// Alt+F4
			case WM_CLOSE:
			{
				DestroyWindow(hWnd);
			}
			break;

			case WM_DESTROY:
			{
				PostQuitMessage(0);
				AppEntryPoint::SetState(AppState::Shutdown);
			}
			break;

			case WM_QUIT:
			{

			}
			break;
		}
	}

	return DefWindowProcA(hWnd, msg, wParam, lParam);
}

bool AppWindow_Windows::RegisterWindow(HINSTANCE hInstance)
{
	WNDCLASSEXA window = {};

	window.cbSize = sizeof(WNDCLASSEX);
	window.style = CS_HREDRAW | CS_VREDRAW;
	window.lpfnWndProc = WindowProc;
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	window.hInstance = hInstance;
	window.hCursor = NULL;
	window.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	window.lpszMenuName = NULL;

	std::string className = GetWindowsClassName(AppEntryPoint::GetApp()->GetAppName());
	window.lpszClassName = className.c_str();

	return RegisterClassExA(&window) != 0;
}

HWND AppWindow_Windows::MakeWindow(HINSTANCE hInstance)
{
	// Setup window style flags
	DWORD dwStyleFlags = WS_VISIBLE;

	if(!WINDOWED_TMP)
		// Window without border
		dwStyleFlags |= WS_POPUP;
	else
		// Window with border
		dwStyleFlags |= WS_OVERLAPPEDWINDOW;

	RECT rWindow = {0, 0, WINDOW_WIDTH_TMP, WINDOW_HEIGHT_TMP};

	AdjustWindowRectEx(&rWindow, dwStyleFlags, FALSE, WS_EX_APPWINDOW);

	// Calculate the width/height of that window's dimensions
	int nWindowWidth = rWindow.right - rWindow.left;
	int nWindowHeight = rWindow.bottom - rWindow.top;

	const std::string appName = AppEntryPoint::GetApp()->GetAppName();
	std::string className = GetWindowsClassName(appName);

	//	Create the window
	return CreateWindowExA(WS_EX_APPWINDOW, className.c_str(), appName.c_str(), dwStyleFlags,
						   (GetSystemMetrics(SM_CXSCREEN) / 2) - (nWindowWidth / 2),
						   (GetSystemMetrics(SM_CYSCREEN) / 2) - (nWindowHeight / 2),
						   nWindowWidth, nWindowHeight, NULL, NULL, hInstance, NULL);
}

bool AppWindow_Windows::AlreadyRunning()
{
	const std::string appName = AppEntryPoint::GetApp()->GetAppName();
	std::string className = GetWindowsClassName(appName);

	HWND hWnd = FindWindowA(className.c_str(), appName.c_str());

	// if window was found
	if(hWnd)
	{
		// if it was minimized
		if(IsIconic(hWnd))
			// Restore Window
			ShowWindow(hWnd, SW_RESTORE);

		// bring window to the front
		SetForegroundWindow(hWnd);

		return true;
	}

	return false;
}

LONG WINAPI AppWindow_Windows::WriteDumpFile(_EXCEPTION_POINTERS* exceptions)
{
	HANDLE hFile = ::CreateFileW(L"dumpfile.mdmp", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile != INVALID_HANDLE_VALUE)
	{
		_MINIDUMP_EXCEPTION_INFORMATION ExInfo;

		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = exceptions;
		ExInfo.ClientPointers = 0;
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &ExInfo, NULL, NULL);
		::CloseHandle(hFile);
	}

	return EXCEPTION_EXECUTE_HANDLER;
}

} // namespace recon

#endif // RECON_OS_WINDOWS