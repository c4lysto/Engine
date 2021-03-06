#include "GraphicsApp.h"

#include "../Source/Core/Application/AppEntryPoint.h"

RECON_REGISTER_APPLICATION(GraphicsApp, Graphics Test App)

GraphicsApp::GraphicsApp(const std::string& appName) :
	IDefaultGameApp(appName)
{

}

GraphicsApp::~GraphicsApp()
{

}

bool GraphicsApp::Init()
{
	IDefaultGameApp::Init();

	recon::AppEntryPoint::SetState(recon::AppState::Run);

	return true;
}

void GraphicsApp::RunSingleLoop()
{
	IDefaultGameApp::RunSingleLoop();


}

void GraphicsApp::Shutdown()
{
	IDefaultGameApp::Shutdown();

	recon::AppEntryPoint::SetState(recon::AppState::Epilogue);
}