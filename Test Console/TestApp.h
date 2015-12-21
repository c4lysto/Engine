#ifndef _TESTAPP_H_
#define _TESTAPP_H_

#include "../Source/Core/Application/WindowedApplication.h"

class TestApp : public recon::IApplication
{
private:
	virtual void Run(recon::AppState currState) override;
	virtual void InitCmdLineArgsConfigType();

protected:
	virtual bool Init() override;
	virtual void Shutdown() override;

public:
	explicit TestApp(const std::string& appName);
	~TestApp();
};

#endif // _TESTAPP_H_
