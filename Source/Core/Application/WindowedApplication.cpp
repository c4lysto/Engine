#include "WindowedApplication.h"

#include "AppEntryPoint.h"
#include "AppWindow.h"

#include "AppWindow_Windows.h"

namespace recon
{

IWindowedApplication::IWindowedApplication(const std::string& appName) : 
	IApplication(appName),
	m_pAppWindow(nullptr)
{
#if RECON_OS_WINDOWS
	m_pAppWindow = new AppWindow_Windows;
#else
	#error "Unhandled OS Entry Point!"
#endif //
}

IWindowedApplication::~IWindowedApplication()
{
	delete m_pAppWindow;
	m_pAppWindow = nullptr;
}

void IWindowedApplication::Run(AppState currState)
{
	IApplication::Run(currState);

	if(currState != AppState::Epilogue)
	{
		m_pAppWindow->Run(currState);
	}
}

bool IWindowedApplication::Init()
{
	IApplication::Init();

	return true;
}

void IWindowedApplication::Shutdown()
{
	IApplication::Shutdown();
}

} // namespace recon
