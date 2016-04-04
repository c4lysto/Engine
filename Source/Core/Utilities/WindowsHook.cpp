#include "WindowsHook.h"

#if RECON_OS_WINDOWS

namespace recon
{

WindowsHook::WindowsHook() : m_Hook(nullptr)
{

}

WindowsHook::~WindowsHook()
{
	Shutdown();
}

void WindowsHook::Init(WindowsHookType hookType, WindowsHookCallback hookCallback)
{
	if(hookCallback)
	{
		void* pModule = nullptr;

		if(Verifyf(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, nullptr, (HMODULE*)&pModule), "SysHook - Failed To Get Module Handle"))
		{
			m_Hook = SetWindowsHookEx((int)hookType, ((HOOKPROC)hookCallback), (HMODULE)nullptr/*pModule*/, GetCurrentThreadId());
			Assertf(m_Hook, "SysHook - Failed To Create Hook!");
		}
	}
}

void WindowsHook::Shutdown()
{
	if(m_Hook)
	{
		Assertf(UnhookWindowsHookEx((HHOOK)m_Hook), "SysHook - Failed To Unhook Windows Hook!\n Error Code: %d", GetLastError());
		m_Hook = nullptr;
	}
}

} // namespace recon

#endif // RECON_OS_WINDOWS
