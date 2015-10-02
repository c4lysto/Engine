#ifndef _RECON_INPUT_MANAGER_H_
#define _RECON_INPUT_MANAGER_H_

#include <Windows.h>
#include "Input.h"

#include "../Utilities/Event.h"
#include "../Utilities/SysHook.h"
#include "../Utilities/Mutex.h"
#include "../Utilities/Thread.h"

#include <atomic>
#include <map>
#include <list>
#include <queue>

namespace recon
{

class InputManager
{
	typedef std::list<InputEvent*> InputCurrentEventContainer;
	typedef std::map<InputEvent, InputCallbackfn> InputCallbackContainer;

private:
	struct PendingInputEvent
	{
		WPARAM wParam;
		LPARAM lParam;
	};
	typedef std::queue<PendingInputEvent> PendingInputEventContainer;


private:
	void* m_WindowHandle;
	Thread m_InputThread;
	Event m_NewInputEvent;
	SysCriticalSection m_PendingInputCS;
	SysCriticalSection m_CurrentInputCS;
	SysHook m_InputHook;
	std::atomic_flag m_IsInputThreadRunning;

	unsigned char m_ucModifiers;
	unsigned char m_ucConnectedDevices;

	PendingInputEventContainer m_PendingInputEvents;
	InputCurrentEventContainer m_lCurrentEvents;
	InputCallbackContainer m_mInputCallbacks;

	InputEvent* GetCurrentInputEvent(const InputEvent& inputEvent) const;

	void HandleModifierInput(const InputEvent& inputEvent);
	void SetInputModifier(InputModifier eModifier, bool bSet);

	void CreateKeyboardEvent(PRAWINPUT pInput);
	void CreateMouseEvent(PRAWINPUT pInput);

	void PostButtonEvent(InputEvent& inputEvent, bool bIsDown);
	void PostMouseButtonEvent(RAWMOUSE& rwMouse, InputMouseButtonEvent& newEvent);
	void PostInputEvent(const InputEvent* inputEvent);

	void ClearAllCurrentInput();

	void InputThreadProc(void* pArgs);

#if RECON_DEBUG
	void DisplayCurrentEvents();
#endif

public:
	static InputManager* ms_Instance;

	static void CreateInstance();
	static void DestroyInstance();
	static InputManager* GetInstance() { Assert(ms_Instance); return ms_Instance; }

public:
	InputManager();
	~InputManager();

	void Shutdown();

	bool Initialize(HWND hWnd = NULL);
	void ProcessInputEvent(WPARAM wParam, LPARAM lParam);
	void AddInputRequest(WPARAM wParam, LPARAM lParam);
	void ProcessInput();
	void GetAttachedDevices();

	void OnWindowFocusActivate();
	void OnWindowFocusDeactivate();
	void SetDeviceChange(WPARAM wParam, LPARAM lParam);

	void RegisterEventCallback(InputEvent& inputEvent, InputCallbackfn& fpEventHandler, bool bOverrideCallback = false);

	Vec2f GetMousePosition();

public:
	static LRESULT __stdcall InputHookCallback(int code, WPARAM wParam, LPARAM lParam);
};

} // namespace recon;

extern recon::InputManager g_InputManager;

#endif // _RECON_INPUT_MANAGER_H_
