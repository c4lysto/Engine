#ifndef _RECON_INPUT_MANAGER_H_
#define _RECON_INPUT_MANAGER_H_

#include <Windows.h>
#include "Input.h"

#include "../Utilities/SysEvent.h"
#include "../Utilities/SysHook.h"
#include "../Utilities/SysMutex.h"
#include "../Utilities/SysThread.h"

#include <map>
using std::map;
using std::pair;

#include <list>
using std::list;

#include <queue>
using std::queue;

namespace recon
{

class InputManager
{
	typedef list<InputEvent*> InputCurrentEventContainer;
	typedef map<InputEvent, InputCallbackfn> InputCallbackContainer;

private:
	struct PendingInputEvent
	{
		WPARAM wParam;
		LPARAM lParam;
	};
	typedef queue<PendingInputEvent> PendingInputEventContainer;


private:
	void* m_WindowHandle;
	SysThread m_InputThread;
	SysEvent m_NewInputEvent;
	SysCriticalSection m_PendingInputCS;
	SysCriticalSection m_CurrentInputCS;
	SysHook m_InputHook;

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

#if DEBUG
	void DisplayCurrentEvents();
#endif

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