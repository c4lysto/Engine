#include "CmdLineArg.h"

#include "CmdLineManager.h"

namespace recon
{

CmdLineArg::CmdLineArg() :
	m_szArgName(nullptr),
	m_pArgData(nullptr)
{

}

CmdLineArg::CmdLineArg(const char* szArgName)
{
	CmdLineManager::QueryCmdLineArg(*this, szArgName);
}

void CmdLineArg::Init(const char* szArgName)
{
	if(Verifyf(!m_pArgData/*!m_pArgData.expired()*/, "Attempting to initialize an already valid CmdLineArg!"))
	{
		CmdLineManager::QueryCmdLineArg(*this, szArgName);
	}
}

void CmdLineArg::Set(bool boolVal)
{
	CmdLineManager::SetCmdLineArg(m_szArgName.c_str(), boolVal);
}

void CmdLineArg::Set(f32 floatVal)
{
	CmdLineManager::SetCmdLineArg(m_szArgName.c_str(), floatVal);
}

void CmdLineArg::Set(s32 intVal)
{
	CmdLineManager::SetCmdLineArg(m_szArgName.c_str(), intVal);
}

void CmdLineArg::Set(const char* stringVal)
{
	CmdLineManager::SetCmdLineArg(m_szArgName.c_str(), stringVal);
}

void CmdLineArg::Set(const f32* floatArr, u32 arrSize)
{
	CmdLineManager::SetCmdLineArg(m_szArgName.c_str(), floatArr, arrSize);
}

} // namespace recon
