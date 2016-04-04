#ifndef _RECON_CMDLINEMANAGER_H_
#define _RECON_CMDLINEMANAGER_H_

#include <map>
#include <memory>

#include "CmdLineArgData.h"
#include "../Math Lib/MathLib.h"
#include "Function.h"

namespace recon
{

class CmdLineArg;

class CmdLineManager
{
	typedef std::map<std::string, _CmdLineArgData*> ArgsMap;
	typedef Function<void(void)> CmdLineConfigTypeCallback;

private:
	static std::vector<_CmdLineConfigType> ms_ConfigTypeNames;
	static u32 ms_ExtArgsParsingDepth;
	static bool ms_bAlreadyParsedCmdLine;
	static const char ms_ExtArgsName[];

public:
	static void ProcessCmdLineArgs(int argc, char** argv);

	static void ShutdownCmdLineArgs();

	static void ProcessCmdLineArgsFromFile(const char* szFilename);

	template<typename... _ConfigTypes>
	static void AddCmdLineArgConfigTypes(_ConfigTypes... configTypes);

	static void QueryCmdLineArg(CmdLineArg& arg, const char* szArgName);
	static void RemoveCmdLineArg(const char* szArgName);

	static void SetCmdLineArg(const char* szArgName, bool boolVal);
	static void SetCmdLineArg(const char* szArgName, float floatVal);
	static void SetCmdLineArg(const char* szArgName, s32 intVal);
	static void SetCmdLineArg(const char* szArgName, const char* stringVal);
	static void SetCmdLineArg(const char* szArgName, const float* floatArr, u32 arrSize);

	static inline void SetCmdLineArg(const char* szArgName, Vec2f_In vec) { SetCmdLineArg(szArgName, &vec.GetXRef(), 2); }
	static inline void SetCmdLineArg(const char* szArgName, Vec3f_In vec) { SetCmdLineArg(szArgName, &vec.GetXRef(), 3); }
	static inline void SetCmdLineArg(const char* szArgName, Vec4f_In vec) { SetCmdLineArg(szArgName, &vec.GetXRef(), 4); }
	static inline void SetCmdLineArg(const char* szArgName, Vec2V_In vec) { SetCmdLineArg(szArgName, &vec.GetXRef(), 2); }
	static inline void SetCmdLineArg(const char* szArgName, Vec3V_In vec) { SetCmdLineArg(szArgName, &vec.GetXRef(), 3); }
	static inline void SetCmdLineArg(const char* szArgName, Vec4V_In vec) { SetCmdLineArg(szArgName, &vec.GetXRef(), 4); }

	static void PrintCmdLineArgs();

private:
	// Used To Guarantee that any global CmdLineArg's won't crash due to static initialization order
	static ArgsMap& GetCmdLineArgsMap()
	{
		static ArgsMap* ms_pArgsMap = new ArgsMap;
		return *ms_pArgsMap;
	}

	static char* GetNextCmdLineDataBlockPtr(char* cmdLineIter);

	static std::string ConvertArgName(const char* szArgName);

	static bool IsArgValidForConfigType(const std::vector<_CmdLineConfigType>& vArgConfigTypes);

	static u64 ProcessCmdLineArg(char* arg);
	static void RegisterCmdLineArg(_CmdLineArgData* pArgData, const char* szArgName);

	static _CmdLineArgData* DetermineCmdLineArgData(char* argVal, u64& argValLength);

	static bool IsCmdLineACommentLine(const char* cmdLine);
	static bool IsCmdLineArgAnArray(char* argVal);
	static bool DoesCmdLineArgContainFloat(char* argVal);

	static _CmdLineArgData* CreateCmdLineArgData_Array(char* argVal, u64& argValLength);
	static _CmdLineArgData* CreateCmdLineArgData_String(char* argVal, u64& argValLength);
	static _CmdLineArgData* CreateCmdLineArgData_F32(char* argVal, u64& argValLength);
	static _CmdLineArgData* CreateCmdLineArgData_S32(char* argVal, u64& argValLength);

	static void _SetCmdLineArg(const char* szArgName, _CmdLineArgData* pNewArgData);
};

template<typename... _ConfigTypes>
void CmdLineManager::AddCmdLineArgConfigTypes(_ConfigTypes... configTypes)
{
	if(Verify(!ms_bAlreadyParsedCmdLine))
	{
		std::vector<std::string> vConfigTypeNames = { configTypes... };

		// sanity check
		for(size_t i = 0; i < vConfigTypeNames.size(); ++i)
		{
			if(vConfigTypeNames.size() == 0)
			{
				vConfigTypeNames.erase(vConfigTypeNames.begin() + i--);
			}
		}

		// Add them to the list
		for(std::string& configName : vConfigTypeNames)
		{
			bool bAlreadyAdded = false;

			for(const _CmdLineConfigType& addedConfigType : ms_ConfigTypeNames)
			{
				if(configName == addedConfigType.m_vConfigName)
				{
					bAlreadyAdded = true;
					break;
				}
			}

			if(!bAlreadyAdded)
			{
				if(configName[0] != '!')
				{
					ms_ConfigTypeNames.push_back(_CmdLineConfigType(configName, true));
				}
				else
				{
					configName.erase(configName.begin());
					ms_ConfigTypeNames.push_back(_CmdLineConfigType(configName, false));
				}
			}
		}
	}
}

} // namespace recon

#endif // _RECON_CMDLINEMANAGER_H_
