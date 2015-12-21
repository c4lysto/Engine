#ifndef _RECON_APPLICATION_H_
#define _RECON_APPLICATION_H_

#include "../Utilities/UtilitiesInclude.h"

#include <string>

namespace recon
{

enum class AppState;

class IApplication
{
private:
	std::string m_AppName;

public:
	explicit IApplication(const std::string& appName);
	virtual ~IApplication();

	const std::string& GetAppName() const { return m_AppName; }
	//void SetAppName(const std::wstring& appName) { if(Verifyf(m_AppName.empty(), "App Name Has Already Been Set, Fuck Off!")) { m_AppName = appName; } }

	virtual void Run(AppState currState) = 0;
	virtual void InitCmdLineArgsConfigType() {}

protected:
	virtual bool Init() = 0;
	virtual void Shutdown() = 0;
};

} // namespace recon

#endif // _RECON_APPLICATION_H_