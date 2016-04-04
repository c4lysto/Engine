#ifndef _RECON_DEBUGWINDOW_H_
#define _RECON_DEBUGWINDOW_H_

#include "../Windows_Inc.h"
#include <tchar.h>

#define BUFFER_SIZE 100

namespace recon
{

class DebugWindow
{
private:
	static HANDLE m_hOutput;

public:
	static bool Initialize();

	static BOOL Shutdown()
	{
		return FreeConsole();
	}
};

} // namespace recon

#endif // _RECON_DEBUGWINDOW_H_