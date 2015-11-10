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
	IApplication(const std::string& appName);
	virtual ~IApplication();

	const std::string& GetAppName() const { return m_AppName; }
	//void SetAppName(const std::wstring& appName) { if(Verifyf(m_AppName.empty(), "App Name Has Already Been Set, Fuck Off!")) { m_AppName = appName; } }

	virtual void ProcessCmdLineArgs(int argc, wchar_t** argv);
	void Run(AppState currState);

protected:
	virtual bool Init() = 0 { return true; }
	virtual void RunSingleLoop() = 0 {}
	virtual void Shutdown() = 0 {}
};

} // namespace recon

#endif // _RECON_APPLICATION_H_