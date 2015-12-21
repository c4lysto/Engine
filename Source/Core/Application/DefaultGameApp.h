#ifndef _RECON_DEFAULTGAMEAPP_H_
#define _RECON_DEFAULTGAMEAPP_H_

#include "WindowedApplication.h"
#include "AppWindow.h"

namespace recon
{

class IDefaultGameApp : public IWindowedApplication
{
private:

public:
	IDefaultGameApp(const std::string& appName);
	virtual ~IDefaultGameApp() override;

	virtual void Run(AppState currState) override;

protected:
	virtual bool Init() override;
	virtual void RunSingleLoop() = 0;
	virtual void Shutdown() override;

public:
	static WindowMessageHandlerReturn GameApp_WindowMessageHandler(WindowMessageHandlerArgs);
};

} // namespace recon

#endif // _RECON_DEFAULTGAMEAPP_H_
