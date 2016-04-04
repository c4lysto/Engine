#ifndef _RECON_WINDOWSHOOK_H_
#define _RECON_WINDOWSHOOK_H_

#include "UtilitiesInclude.h"

#if RECON_OS_WINDOWS

typedef LRESULT (__stdcall *WindowsHookCallback)(int, WPARAM, LPARAM);


namespace recon
{

enum class WindowsHookType
{
	CallWnd_Hook = 4,			// Hooks before the system sends them to the destination window procedure: See "CallWndProc" hook procedure on msdn for details on callback
	CallWndRet_Hook = 12,		// Hook that monitors messages after they have been processed by the destination window procedure.
								// See "CallWndRetProc" hook procedure on msdn for details on callback
	CBT_Hook = 5,				// Hook procedure that receives notifications useful to a CBT application: See "CBTProc" hook procedure on msdn for details on callback
	Debug_Hook = 9,				// Hook procedure useful for debugging other hook procedures: See "DebugProc" hook procedure on msdn for details on callback
	ForegroundIdle_Hook = 11,	// Hook procedure that will be called when the application's foreground thread is about to become idle.
								// See "ForegroundIdleProc" hook procedure on msdn for details on callback
	GetMessage_Hook = 3,		// Hook procedure that monitors messages posted to a message queue: See "GetMsgProc" hook procedure on msdn for details on callback
	JournalPlayback_Hook = 1,	// Hook procedure that posts messages previously recorded by a HOOK_JOURNALPLAYBACK hook procedure.
								// See "JournalPlaybackProc" hook procedure on msdn for details on callback
	JournalRecord_Hook = 0,		// Hook procedure that records input messages posted to the system message queue. This hook is useful for recording macros.
								// See "JournalRecordProc" hook procedure on msdn for details on callback
	Keyboard_Hook = 2,			// Hook procedure that monitors keystroke messages: See "KeyboardProc" hook procedure on msdn for details on callback.
	LowLevelKeyboard_Hook = 13,	// Hook procedure that monitors low-level keyboard input events: See "LowLevelKeyboardProc" hook procedure on msdn for details on callback.
	Mouse_Hook = 7,				// Hook procedure that monitors mouse messages: See "MouseProc" hook procedure on msdn for details on callback.
	LowLevelMouse_Hook = 14,	// Hook procedure that monitors low-level mouse input events: See "LowLevelMouseProc" hook procedure on msdn for details on callback.
	MsgFilter_Hook = -1,		// Hook procedure that monitors messages generated as a result of an input event in a dialog box, message box, menu, or scroll bar:
								// See "MessageProc" hook procedure on msdn for details on callback.
	Shell_Hook = 10,			// Hook procedure that receives notifications useful to shell applications: See "ShellProc" hook procedure on msdn for details on callback.
	SysMsg_Hook = 6				// Hook procedure that monitors messages generated as a result of an input event in a dialog box, message box, menu, or scroll bar. 
								// The hook procedure monitors these messages for all applications in the same desktop as the calling thread.
								// See "SysMsgProc" hook procedure on msdn for details on callback.
};

class WindowsHook
{
public:
	typedef void* Handle;

private:
	Handle m_Hook;

public:
	WindowsHook();
	~WindowsHook();

	void Init(WindowsHookType hookType, WindowsHookCallback hookCallback);
	void Shutdown();
};

} // namespace recon

#endif // RECON_OS_WINDOWS

#endif // _RECON_WINDOWSHOOK_H_
