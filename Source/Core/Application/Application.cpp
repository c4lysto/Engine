#include "Application.h"

#include "AppEntryPoint.h"

namespace recon
{

IApplication::IApplication(const std::string& appName) :
	m_AppName(appName)
{

}

IApplication::~IApplication()
{

}

void IApplication::ProcessCmdLineArgs(int argc, wchar_t** argv)
{
	(void)argc;
	(void)argv;
}

void IApplication::Run(AppState currState)
{
	switch(currState)
	{
	case AppState::Init:
		{
			AppEntryPoint::SetState(AppState::Pending);
			Init();
		}
		break;

	case AppState::Run:
		{
			RunSingleLoop();
		}
		break;

	case AppState::Shutdown:
		{
			AppEntryPoint::SetState(AppState::Pending);
			Shutdown();
		}
		break;
	}
}

} // namespace recon
