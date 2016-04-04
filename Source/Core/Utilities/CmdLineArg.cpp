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
	if(Verifyf(m_szArgName, "Cannot 'Set' An Invalid CmdLineArg!"))
	{
		CmdLineManager::SetCmdLineArg(m_szArgName, boolVal);
	}
}

void CmdLineArg::Set(f32 floatVal)
{
	if(Verifyf(m_szArgName, "Cannot 'Set' An Invalid CmdLineArg!"))
	{
		CmdLineManager::SetCmdLineArg(m_szArgName, floatVal);
	}
}

void CmdLineArg::Set(s32 intVal)
{
	if(Verifyf(m_szArgName, "Cannot 'Set' An Invalid CmdLineArg!"))
	{
		CmdLineManager::SetCmdLineArg(m_szArgName, intVal);
	}
}

void CmdLineArg::Set(const char* stringVal)
{
	if(Verifyf(m_szArgName, "Cannot 'Set' An Invalid CmdLineArg!"))
	{
		CmdLineManager::SetCmdLineArg(m_szArgName, stringVal);
	}
}

void CmdLineArg::Set(const f32* floatArr, u32 arrSize)
{
	if(Verifyf(m_szArgName, "Cannot 'Set' An Invalid CmdLineArg!"))
	{
		CmdLineManager::SetCmdLineArg(m_szArgName, floatArr, arrSize);
	}
}

} // namespace recon
