#include "SysHook.h"
#include "Debugging\DebugHelp.h"

namespace recon
{

SysHook::SysHook() : m_pHook(nullptr)
{

}

SysHook::~SysHook()
{
	Shutdown();
}

void SysHook::Init(sysHookType hookType, SysHookCallback hookCallback)
{
	if(hookCallback)
	{
		void* pModule = nullptr;

		if(Verifyf(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_PIN, nullptr, (HMODULE*)&pModule), "SysHook - Failed To Get Module Handle"))
		{
			m_pHook = SetWindowsHookEx((int)hookType, ((HOOKPROC)hookCallback), (HMODULE)nullptr/*pModule*/, GetCurrentThreadId());
			Assertf(m_pHook, "SysHook - Failed To Create Hook!");
		}
	}
}

void SysHook::Shutdown()
{
	if(m_pHook)
	{
		Assertf(UnhookWindowsHookEx((HHOOK)m_pHook), "SysHook - Failed To Unhook Windows Hook!\n Error Code: %d", GetLastError());
		m_pHook = nullptr;
	}
}

} // namespace recon
