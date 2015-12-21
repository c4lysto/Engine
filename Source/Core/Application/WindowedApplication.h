#ifndef _RECON_WINDOWEDAPPLICATION_H_
#define _RECON_WINDOWEDAPPLICATION_H_

#include "Application.h"

namespace recon
{

class IAppWindow;

class IWindowedApplication : public IApplication
{
private:
	IAppWindow* m_pAppWindow;

public:
	explicit IWindowedApplication(const std::string& appName);
	~IWindowedApplication();

	virtual void Run(AppState currState) override;

protected:
	virtual bool Init() override;
	virtual void Shutdown() override;

	IAppWindow* GetWindow() { return m_pAppWindow; }
};

} // namespace recon

#endif // _RECON_WINDOWEDAPPLICATION_H_
