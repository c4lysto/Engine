#include "CmdLineManager.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

#include "CmdLineArg.h"
#include "CmdLineArgData.h"

namespace recon
{

std::vector<_CmdLineConfigType> CmdLineManager::ms_ConfigTypeNames;
u32 CmdLineManager::ms_ExtArgsParsingDepth = 0;
bool CmdLineManager::ms_bAlreadyParsedCmdLine = false;
const char CmdLineManager::ms_ExtArgsName[] = "extargs";

void CmdLineManager::ProcessCmdLineArgs(int argc, char** argv)
{
	if(Verify(!ms_bAlreadyParsedCmdLine))
	{
		for(int i = 0; i < argc; ++i)
		{
			char* argDataBlockStart = argv[i];
			char* argDataBlockIter = argDataBlockStart;

			while(*argDataBlockIter != '\0')
			{
				if(*argDataBlockIter == '-')
				{
					// Add 1 for the '-' character
					argDataBlockIter += ProcessCmdLineArg(argDataBlockIter + 1) + 1;
				}

				argDataBlockIter = GetNextCmdLineDataBlockPtr(argDataBlockIter);
			}
		}

		ms_bAlreadyParsedCmdLine = true;
	}
}

void CmdLineManager::ShutdownCmdLineArgs()
{
	ArgsMap& argsMap = GetCmdLineArgsMap();

	for(ArgsMap::iterator iter = argsMap.begin(); iter != argsMap.end(); ++iter)
	{
		delete iter->second;
	}

	argsMap.clear();

	ms_ConfigTypeNames.clear();

	// Is dynamically allocated!
	delete &argsMap;
}

void CmdLineManager::ProcessCmdLineArgsFromFile(const char* szFilename)
{
	if(szFilename)
	{
		std::fstream cmdLineArgsFile(szFilename, std::ios_base::in | std::ios_base::binary);

		if(cmdLineArgsFile.is_open())
		{
			cmdLineArgsFile.seekg(0, std::ios_base::end);

			u64 fileSize = (u64)cmdLineArgsFile.tellg();

			cmdLineArgsFile.seekg(0, std::ios_base::beg);

			char* fileContents = new char[fileSize + 1];

			cmdLineArgsFile.read(fileContents, fileSize);
			fileContents[fileSize] = '\0';

			if(cmdLineArgsFile.good())
			{
				++ms_ExtArgsParsingDepth;

				ProcessCmdLineArgs(1, &fileContents);

				--ms_ExtArgsParsingDepth;
			}

			delete[] fileContents;
		}
	}
}

char* CmdLineManager::GetNextCmdLineDataBlockPtr(char* cmdLineIter)
{
	char* pNextDataBlock = cmdLineIter;

	while(*pNextDataBlock != '-' && *pNextDataBlock != '\0')
	{
		// if we're in a file and we see a '#' char, then
		// ignore everything until we hit a new line
		if(*pNextDataBlock == '#' && ms_ExtArgsParsingDepth)
		{
			while(*pNextDataBlock != '\n' && *pNextDataBlock != '\0')
			{
				++pNextDataBlock;
			}
		}

		++pNextDataBlock;
	}

	return pNextDataBlock;
}

std::string CmdLineManager::ConvertArgName(const char* szArgName)
{
	std::string lowercaseArgName(szArgName);
	for(int i = 0; i < lowercaseArgName.size(); ++i)
	{
		lowercaseArgName[i] = std::tolower(lowercaseArgName[i]);
	}
	return lowercaseArgName;
}

bool CmdLineManager::IsArgValidForConfigType(const std::vector<_CmdLineConfigType>& vArgConfigTypes)
{
	for(const _CmdLineConfigType& argConfig : vArgConfigTypes)
	{
		bool bFoundConfigType = false;
		bool bMustFindConfig = argConfig.m_bWhenActive;

		for(const _CmdLineConfigType& configType : ms_ConfigTypeNames)
		{
			bool bSameConfigType = argConfig.m_vConfigName == configType.m_vConfigName;
			bFoundConfigType |= bSameConfigType;
		}

		if(bFoundConfigType == bMustFindConfig)
		{
			return true;
		}
	}

	return false;
}

void CmdLineManager::QueryCmdLineArg(CmdLineArg& arg, const char* szArgName)
{
	HashWithString hashName(ConvertArgName(szArgName).c_str());

	ArgsMap& argsMap = GetCmdLineArgsMap();

	ArgsMap::iterator iter = argsMap.find(hashName);
	if(iter == argsMap.end())
	{
		argsMap[hashName] = nullptr;

		iter = argsMap.find(hashName);
	}

	arg.m_szArgName = hashName.GetString();
	arg.m_pArgData = &argsMap[hashName];
}

void CmdLineManager::RemoveCmdLineArg(const char* szArgName)
{
	HashWithString hashName(ConvertArgName(szArgName).c_str());

	ArgsMap& argsMap = GetCmdLineArgsMap();

	ArgsMap::iterator iter = argsMap.find(hashName);
	if(iter != argsMap.end())
	{
		_CmdLineArgData*& pMapEntry = argsMap[hashName];
		delete pMapEntry;
		pMapEntry = nullptr;
	}
}

void CmdLineManager::SetCmdLineArg(const char* szArgName, bool boolVal)
{
	HashWithString hashName(ConvertArgName(szArgName).c_str());
	_CmdLineArgData*& pMapEntry = GetCmdLineArgsMap()[hashName];
	delete pMapEntry;
	pMapEntry = new _CmdLineArgBool(boolVal);
}

void CmdLineManager::SetCmdLineArg(const char* szArgName, float floatVal)
{
	HashWithString hashName(ConvertArgName(szArgName).c_str());
	_CmdLineArgData*& pMapEntry = GetCmdLineArgsMap()[hashName];
	delete pMapEntry;
	pMapEntry = new _CmdLineArgF32(floatVal);
}

void CmdLineManager::SetCmdLineArg(const char* szArgName, s32 intVal)
{
	HashWithString hashName(ConvertArgName(szArgName).c_str());
	_CmdLineArgData*& pMapEntry = GetCmdLineArgsMap()[hashName];
	delete pMapEntry;
	pMapEntry = new _CmdLineArgS32(intVal);
}

void CmdLineManager::SetCmdLineArg(const char* szArgName, const char* stringVal)
{
	HashWithString hashName(ConvertArgName(szArgName).c_str());
	_CmdLineArgData*& pMapEntry = GetCmdLineArgsMap()[hashName];
	delete pMapEntry;
	pMapEntry = new _CmdLineArgString(stringVal);
}

void CmdLineManager::SetCmdLineArg(const char* szArgName, const float* floatArr, u32 arrSize)
{
	HashWithString hashName(ConvertArgName(szArgName).c_str());
	_CmdLineArgData*& pMapEntry = GetCmdLineArgsMap()[hashName];
	delete pMapEntry;
	pMapEntry = new _CmdLineArgArray(floatArr, arrSize);
}

void CmdLineManager::PrintCmdLineArgs()
{
	ArgsMap& argsMap = GetCmdLineArgsMap();

	//DisplayDebugString("Command Line Arguments: \n");
	std::cout << "Command Line Arguments: \n";

	for(ArgsMap::const_iterator iter = argsMap.begin(); iter != argsMap.end(); ++iter)
	{
		std::string val = iter->second ? iter->second->Print() : "";
		std::cout << "arg: " << iter->first.GetString() << ",\t value: '" << val << "'\n";

		//DisplayDebugString("arg: '-%s', value: '%s'\n", iter->first.GetString(), iter->second ? iter->second->Print() : "");
	}
}

u64 CmdLineManager::ProcessCmdLineArg(char* arg)
{
	u64 cmdLineArgBlockSize = 0;

	char* argStart = arg;
	char* argName = arg;

	u64 argNameLength = 0;

	std::vector<_CmdLineConfigType> vArgConfigTypes;

	char* argVal = nullptr;

	while(true)
	{
		if(*arg == '\0')
		{
			cmdLineArgBlockSize = u64(arg - argStart);
			argNameLength = u64(arg - argName);
			break;
		}
		else if(*arg == ':')
		{
			bool bWhenActive = *argName != '!';
			if(bWhenActive)
			{
				vArgConfigTypes.push_back(_CmdLineConfigType(std::string(argName, (arg - argName)), bWhenActive));
			}
			else
			{
				vArgConfigTypes.push_back(_CmdLineConfigType(std::string(argName + 1, (arg - argName) - 1), bWhenActive));
			}

			argName = arg + 1;
		}

		if(std::isspace(*arg) || *arg == '=')
		{
			cmdLineArgBlockSize = u64(arg - argStart);
			argNameLength = u64(arg - argName);

			if(!std::isspace(*arg))
			{
				cmdLineArgBlockSize += 1;
				argVal = arg + 1;
			}
			break;
		}

		++arg;
	}

	if(argNameLength > 0)
	{
		// Ignore Via Config Types
		if(vArgConfigTypes.size() == 0 || IsArgValidForConfigType(vArgConfigTypes))
		{
			u64 argValLength = 0;

			_CmdLineArgData* pArgData = DetermineCmdLineArgData(argVal, argValLength);
			cmdLineArgBlockSize += argValLength;

			if(pArgData)
			{
				char* argumentName = new char[argNameLength + 1];
				memcpy(argumentName, argName, argNameLength);
				argumentName[argNameLength] = '\0';

				for(int i = 0; i < argNameLength; ++i)
				{
					argumentName[i] = std::tolower(argumentName[i]);
				}

				if(strncmp(argumentName, ms_ExtArgsName, NUMELEM(ms_ExtArgsName)))
				{
					RegisterCmdLineArg(pArgData, argumentName);
				}
				else
				{
					std::string extArgsFileName;
					if(pArgData->Get(extArgsFileName))
					{
						ProcessCmdLineArgsFromFile(extArgsFileName.c_str());
					}
					else
					{
						Assertf(false, "Failed To Get Commandline External Args File Name!");
					}

					delete pArgData;
				}

				delete[] argumentName;
			}
		}
	}	

	Assert(cmdLineArgBlockSize);

	return cmdLineArgBlockSize;
}

void CmdLineManager::RegisterCmdLineArg(_CmdLineArgData* pArgData, const char* szArgName)
{
	HashWithString hashName(ConvertArgName(szArgName).c_str());

	ArgsMap& argsMap = GetCmdLineArgsMap();

	ArgsMap::iterator iter = argsMap.find(hashName);
	if(Verifyf(!(iter != argsMap.end() && hashName.GetString() != iter->first.GetString()), "Command line already exists or there is a hash collision!"))
	{
		argsMap[hashName] = pArgData;
	}
}

_CmdLineArgData* CmdLineManager::DetermineCmdLineArgData(char* argVal, u64& argValLength)
{
	_CmdLineArgData* pArgData(nullptr);

	if(argVal && !std::isspace(*argVal))
	{
		// First Check For A String and make sure it's NOT a negative number
		if(!std::isdigit(*argVal) && (*argVal != '-' || !std::isdigit(*(argVal + 1))))
		{
			pArgData = CreateCmdLineArgData_String(argVal, argValLength);
		}
		// Then Numbers
		else
		{
			// First Check For Array
			if(IsCmdLineArgAnArray(argVal))
			{
				pArgData = CreateCmdLineArgData_Array(argVal, argValLength);
			}
			// First Check For Float
			else if(DoesCmdLineArgContainFloat(argVal))
			{
				pArgData = CreateCmdLineArgData_F32(argVal, argValLength);
			}
			// Then Integer
			else
			{	
				pArgData = CreateCmdLineArgData_S32(argVal, argValLength);
			}
		}
	}

	// Cannot Determine Arg Type, Resort to bool (S32 1 or 0)
	if(!pArgData)
	{
		pArgData = new _CmdLineArgBool(true);
	}

	return pArgData;
}

bool CmdLineManager::IsCmdLineArgAnArray(char* argVal)
{
	while(!std::isspace(*argVal) && *argVal != '\0')
	{
		if(*argVal == ',')
		{
			return true;
		}
		else if(!std::isdigit(*argVal) && *argVal != '.')
		{
			return false;
		}

		++argVal;
	}

	return false;
}

bool CmdLineManager::DoesCmdLineArgContainFloat(char* argVal)
{
	while(!std::isspace(*argVal) && *argVal != '\0')
	{
		if(*argVal == '.')
		{
			return true;
		}
		else if(!std::isdigit(*argVal))
		{
			return false;
		}

		++argVal;
	}

	return false;
}

_CmdLineArgData* CmdLineManager::CreateCmdLineArgData_Array(char* argVal, u64& argValLength)
{
	char* argIter = argVal;
	char* valEnd = nullptr;

	std::vector<f32> floatVec;

	while(true)
	{
		floatVec.push_back(strtof(argIter, &valEnd));

		if(*valEnd == ',' && std::isdigit(*(valEnd + 1)))
		{
			++valEnd;
		}
		else
		{
			break;
		}

		argIter = valEnd;
	}

	if(floatVec.size() > 0)
	{
		return new _CmdLineArgArray(floatVec);
	}

	return nullptr;
}

_CmdLineArgData* CmdLineManager::CreateCmdLineArgData_String(char* argVal, u64& argValLength)
{
	char* stringStart = argVal;

	// first Check for bool
	if(std::tolower(*argVal) == 't')
	{
		const char trueString[] = "true";
		int i = 0;
		for(; i < NUMELEM(trueString)-1; ++i, ++argVal)
		{
			if(std::tolower(*argVal) != trueString[i])
				break;
		}

		if(i + 1 == NUMELEM(trueString) && (std::isspace(*argVal) || *argVal == '\0'))
		{
			argValLength = NUMELEM(trueString);
			return new _CmdLineArgBool(true);
		}

		argVal = stringStart;
	}
	else if(std::tolower(*argVal) == 'f')
	{
		const char falseString[] = "false";
		int i = 0;
		for(; i < NUMELEM(falseString)-1; ++i, ++argVal)
		{
			if(std::tolower(*argVal) != falseString[i])
				break;
		}

		if(i + 1 == NUMELEM(falseString) && (std::isspace(*argVal) || *argVal == '\0'))
		{
			argValLength = NUMELEM(falseString);
			return new _CmdLineArgBool(false);
		}

		argVal = stringStart;
	}

	// if it doesn't contain quotes then read until the first whitespace
	if(*argVal != '"' && ms_ExtArgsParsingDepth)
	{
		while(!std::isspace(*argVal) && *argVal != '\0')
		{
			++argVal;
		}

		argValLength = argVal - stringStart;
		return new _CmdLineArgString(std::string(stringStart, argValLength));
	}
	// else read until the next quotation marks/newline/null delimiter
	else
	{
		// Skip The Beginning Quotation Mark
		if(*argVal == '"')
		{
			++stringStart;
			++argVal;
		}

		while(*argVal != '"' && *argVal != '\0' && *argVal != '\n')
		{
			++argVal;
		}

		argValLength = argVal - stringStart;
		return new _CmdLineArgString(std::string(stringStart, argValLength));
	}

	return nullptr;
}

_CmdLineArgData* CmdLineManager::CreateCmdLineArgData_F32(char* argVal, u64& argValLength)
{
	char* pEndPtr;
	f32 floatVal = (f32)strtof(argVal, &pEndPtr);

	argValLength = pEndPtr - argVal;

	return new _CmdLineArgF32(floatVal);
}

_CmdLineArgData* CmdLineManager::CreateCmdLineArgData_S32(char* argVal, u64& argValLength)
{
	bool bIsHexVal = false;

	if(*argVal == '0' && std::tolower(*(argVal + 1)) == 'x')
	{
		bIsHexVal = true;
	}

	int radix = bIsHexVal ? 16 : 10;

	char* pEndPtr;
	s32 intVal = (s32)strtol(argVal, &pEndPtr, radix);

	argValLength = pEndPtr - argVal;

	return new _CmdLineArgS32(intVal);
}

void CmdLineManager::_SetCmdLineArg(_CmdLineArgData* pArgPtr, _CmdLineArgData* pNewArg)
{
	/*_CmdLineArgData* pOldData = pArgPtr;

	pArgPtr.CompareExchange();*/
}

} // namespace recon
