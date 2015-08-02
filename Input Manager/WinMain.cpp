#include <Windows.h>
#include <stdio.h>
#include <DbgHelp.h>
#pragma comment(lib,"dbghelp.lib")
#include <tchar.h>
#include <crtdbg.h>
#include <iostream>
using namespace std;

#include "../Source/Core/Utilities/UtilitiesInclude.h"
#include "../Source/Core/Utilities/Debugging/DebugWindow.h"
#include "../Source/Core/Input/InputManager.h"

const TCHAR* CLASS_NAME = _T("Input Manager");
const TCHAR* WINDOW_NAME = _T("Input Manager");

const bool WINDOWED = true;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;


BOOL AlreadyRunning();
BOOL RegisterWindow(HINSTANCE hInstance);
HWND MakeWindow(HINSTANCE hInstance);
WPARAM RunMessageLoop();
bool RunSingleLoop(WPARAM& quitCode);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LONG WINAPI WriteDumpFile(_EXCEPTION_POINTERS* exceptions);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);

//#ifndef _DEBUG
	SetUnhandledExceptionFilter(WriteDumpFile);
//#endif

	if(!hPrevInstance && AlreadyRunning())
		return FALSE;

	if(!RegisterWindow(hInstance))
		return FALSE;

	HWND hWnd = MakeWindow(hInstance);

	if(!hWnd)
	{
		int tmp = GetLastError();
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

#ifdef _DEBUG
	if(!DebugWindow::Initialize())
	{
		MessageBox(hWnd, _T("Failed To Create Debug Window"), _T(""), MB_OK | MB_ICONERROR);

		return 0;
	}
#endif

	g_InputManager.Initialize(hWnd);

	WPARAM retVal = RunMessageLoop();

	DebugWindow::Shutdown();

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)(retVal);
}

WPARAM RunMessageLoop()
{
	WPARAM retVal = 0;

	while(RunSingleLoop(retVal))
	{
		Sleep(2);
	}

	return retVal;
}

bool RunSingleLoop(WPARAM& quitCode)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if(msg.message == WM_QUIT)
		{
			quitCode = msg.wParam;
			// Shutdown Code Here!
			g_InputManager.Shutdown();
			return false;
		}
	}

	g_InputManager.ProcessInput();

	return true;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		// Alt+F4
	case WM_CLOSE:
		{
			DestroyWindow(hWnd);
		}
		break;

		// Window Creation
	case WM_CREATE:
		{
			
		}
		break;

	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

	case WM_ACTIVATE:
		{
			if(wParam != WA_INACTIVE)
			{
				g_InputManager.OnWindowFocusActivate();
				//cout << "ACTIVE\n";
			}
			else
			{
				g_InputManager.OnWindowFocusDeactivate();
				//cout << "INACTIVE\n";
			}
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL RegisterWindow(HINSTANCE hInstance)
{
	WNDCLASSEX window = {};

	window.cbSize			= sizeof(WNDCLASSEX);
	window.style			= CS_HREDRAW | CS_VREDRAW;
	window.lpfnWndProc		= WindowProc;
	window.cbClsExtra		= 0;
	window.cbWndExtra		= 0;
	window.hInstance		= hInstance;
	window.hCursor			= NULL;
	window.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	window.lpszMenuName		= NULL;
	window.lpszClassName	= CLASS_NAME;

	return RegisterClassEx(&window);
}

HWND MakeWindow(HINSTANCE hInstance)
{
	// Setup window style flags
	DWORD dwStyleFlags = WS_VISIBLE;

	if(!WINDOWED)
		// Window without border
		dwStyleFlags |= WS_POPUP;
	else
		// Window with border
		dwStyleFlags |= WS_OVERLAPPEDWINDOW;

	RECT rWindow = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	
	AdjustWindowRectEx(&rWindow, dwStyleFlags, FALSE, WS_EX_APPWINDOW);
	
	// Calculate the width/height of that window's dimensions
	int nWindowWidth	= rWindow.right - rWindow.left;
	int nWindowHeight	= rWindow.bottom - rWindow.top;

	//	Create the window
	return CreateWindowEx(WS_EX_APPWINDOW, CLASS_NAME, WINDOW_NAME,	dwStyleFlags,												
						  (GetSystemMetrics(SM_CXSCREEN)/2) - (nWindowWidth/2),		
						  (GetSystemMetrics(SM_CYSCREEN)/2) - (nWindowHeight/2),	
						  nWindowWidth,	nWindowHeight, NULL, NULL, hInstance, NULL);
}

BOOL AlreadyRunning()
{
	HWND hWnd = FindWindow(CLASS_NAME, WINDOW_NAME);

	// if window was found
	if(hWnd)
	{
		// if it was minimized
		if(IsIconic(hWnd))
			// Restore Window
			ShowWindow(hWnd, SW_RESTORE);

		// bring window to the front
		SetForegroundWindow(hWnd);

		return TRUE;
	}

	return FALSE;
}

LONG WINAPI WriteDumpFile(_EXCEPTION_POINTERS* exceptions)
{
	HANDLE hFile = ::CreateFile(_T("dumpfile.mdmp"), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL );

	if(hFile != INVALID_HANDLE_VALUE)
	{
		_MINIDUMP_EXCEPTION_INFORMATION ExInfo;

		ExInfo.ThreadId = ::GetCurrentThreadId();
		ExInfo.ExceptionPointers = exceptions;
		ExInfo.ClientPointers = 0;
		MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), hFile, MiniDumpWithFullMemory, &ExInfo, NULL, NULL );
		::CloseHandle(hFile);
	}

	return EXCEPTION_EXECUTE_HANDLER;
}