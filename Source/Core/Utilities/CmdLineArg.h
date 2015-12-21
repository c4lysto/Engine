#ifndef _RECON_CMDLINEARG_H_
#define _RECON_CMDLINEARG_H_

#include <memory>
#include <string>

#include "CmdLineArgData.h"
#include "../Math Lib/MathLib.h"

namespace recon
{

class CmdLineArg
{
	friend class CmdLineManager;

private:
	std::string m_szArgName;
	_CmdLineArgData** m_pArgData;

public:
	CmdLineArg();
	explicit CmdLineArg(const char* szArgName);

	void Init(const char* szArgName);

	operator bool() const { return (m_pArgData && (*m_pArgData)); }

	bool Get(bool& bOut) const { return (m_pArgData && (*m_pArgData)) ? (*m_pArgData)->Get(bOut) : false; };
	bool Get(s32& nOut) const { return (m_pArgData && (*m_pArgData)) ? (*m_pArgData)->Get(nOut) : false; }
	bool Get(f32& fOut) const { return (m_pArgData && (*m_pArgData)) ? (*m_pArgData)->Get(fOut) : false; }
	bool Get(std::string& szOut) const { return(m_pArgData && (*m_pArgData)) ? (*m_pArgData)->Get(szOut) : false; }
	bool Get(std::vector<f32>& vOut) const { return (m_pArgData && (*m_pArgData)) ? (*m_pArgData)->Get(vOut) : false; }

	std::string Print() const { return (m_pArgData && (*m_pArgData)) ? (*m_pArgData)->Print() : ""; }

	void Set(bool boolVal);
	void Set(f32 floatVal);
	void Set(s32 intVal);
	void Set(const char* stringVal);
	void Set(const std::string& stringVal)	{ Set(stringVal.c_str()); }
	void Set(const f32* floatArr, u32 arrSize);
	void Set(const std::vector<f32>& floatArr)	{ Set((const float*)floatArr.data(), (u32)floatArr.size());}

	void Set(Vec2f_In vec) { Set(&vec.GetXRef(), 2); }
	void Set(Vec3f_In vec) { Set(&vec.GetXRef(), 3); }
	void Set(Vec4f_In vec) { Set(&vec.GetXRef(), 4); }
	void Set(Vec2V_In vec) { Set(&vec.GetXRef(), 2); }
	void Set(Vec3V_In vec) { Set(&vec.GetXRef(), 3); }
	void Set(Vec4V_In vec) { Set(&vec.GetXRef(), 4); }
};

} // namespace recon

#endif // _RECON_CMDLINEARG_H_