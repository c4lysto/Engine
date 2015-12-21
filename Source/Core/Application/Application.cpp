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

void IApplication::Run(AppState currState)
{
	switch(currState)
	{
	case AppState::Prologue:
		{
			AppEntryPoint::SetState(AppState::Init);
		}
		break;

	case AppState::Init:
		{
			AppEntryPoint::SetState(AppState::Pending);
			Init();
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

bool IApplication::Init()
{
	recon::AppEntryPoint::SetState(recon::AppState::Run);

	return true;
}

void IApplication::Shutdown()
{
	recon::AppEntryPoint::SetState(recon::AppState::Epilogue);
}

} // namespace recon
