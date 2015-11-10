#include "DefaultGameApp.h"

#if RECON_OS_WINDOWS
#include "AppWindow_Windows.h"
#endif // RECON_OS_WINDOWS

#include "AppEntryPoint.h"
#include "../Graphics/GraphicsDevice.h"
#include "../Input/InputManager.h"
#include "../Utilities/Function.h"
#include "../Utilities/Timer.h"

namespace recon
{

IDefaultGameApp::IDefaultGameApp(const std::string& appName) :
	IApplication(appName)
{

}

IDefaultGameApp::~IDefaultGameApp()
{

}

bool IDefaultGameApp::Init()
{
	bool bSuccessfullyInitialized = false;

	bSuccessfullyInitialized = IApplication::Init();

	if(bSuccessfullyInitialized)
	{
		AppEntryPoint::GetWindow()->SetWindowMessageHandler(WindowMessageHandler(GameApp_WindowMessageHandler));

		GameClock::Init();

		InputManager::CreateInstance();

		GraphicsDevice::CreateInstance();
		GraphicsDevice::GetInstance()->Init(1280, 720);
	}

	return bSuccessfullyInitialized;
}

void IDefaultGameApp::RunSingleLoop()
{
	IApplication::RunSingleLoop();

	GameClock::Update();

	GraphicsDevice* pDevice = GraphicsDevice::GetInstance();
	pDevice->PreBuildCommandLists();
	pDevice->PostBuildCommandLists();

	pDevice->BeginFrame();
	pDevice->ExecuteFrame();
	pDevice->EndFrame();
}

void IDefaultGameApp::Shutdown()
{
	IApplication::Shutdown();

	InputManager::DestroyInstance();

	GraphicsDevice::DestroyInstance();
}

#if RECON_OS_WINDOWS
WindowMessageHandlerReturn IDefaultGameApp::GameApp_WindowMessageHandler(WindowMessageHandlerArgs args)
{
	WindowMessageHandlerReturn allowDefaultMessageHandling = true;
	AppWindow_Windows::WindowsMessageArgs& messageArgs = *(AppWindow_Windows::WindowsMessageArgs*)args;

	switch(messageArgs.msg)
	{
		case WM_ACTIVATE:
		{
			if(messageArgs.wParam != WA_INACTIVE)
			{
				InputManager::GetInstance()->OnWindowFocusActivate();
			}
			else
			{
				InputManager::GetInstance()->OnWindowFocusDeactivate();
			}
		}
		break;
	}

	return allowDefaultMessageHandling;
}

} // namespace recon

#endif
