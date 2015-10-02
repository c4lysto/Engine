#include "AppWindow.h"

#include "AppEntryPoint.h"

namespace recon
{

WindowMessageHandler IAppWindow::ms_WindowMessageHandler(nullptr);

void IAppWindow::Run(AppState currState)
{
	switch(currState)
	{
		case AppState::Prologue:
		{
			Init();

			AppEntryPoint::SetState(AppState::Init);
		}
		break;

		case AppState::Epilogue:
		{
			Shutdown();
		}
		break;
	}

	RunSingleLoop();
}

} // namespace recon
