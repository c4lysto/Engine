#ifndef _RECON_DEFAULTGAMEAPP_H_
#define _RECON_DEFAULTGAMEAPP_H_

#include "Application.h"
#include "AppWindow.h"

namespace recon
{

class IDefaultGameApp : public IApplication
{
private:

public:
	IDefaultGameApp(const std::string& appName);
	virtual ~IDefaultGameApp() override;

protected:
	virtual bool Init() override;
	virtual void RunSingleLoop() override;
	virtual void Shutdown() override;

public:
	static WindowMessageHandlerReturn GameApp_WindowMessageHandler(WindowMessageHandlerArgs);
};

} // namespace recon

#endif // _RECON_DEFAULTGAMEAPP_H_
