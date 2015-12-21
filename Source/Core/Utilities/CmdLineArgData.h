#ifndef _RECON_CMDLINEARGDATA_H_
#define _RECON_CMDLINEARGDATA_H_

#include "../Utilities/UtilitiesInclude.h"

#include <string>
#include <vector>

namespace recon
{

class _CmdLineConfigType
{
	friend class _CmdLineArgData;
	friend class CmdLineManager;

private:
	std::string m_vConfigName;
	bool m_bWhenActive;

public:
	_CmdLineConfigType(const std::string& configName, bool bWhenActive) : m_vConfigName(configName), m_bWhenActive(bWhenActive) {}
};

class _CmdLineArgData
{
	friend class CmdLineArg;
	friend class CmdLineManager;

public:
	virtual ~_CmdLineArgData() = 0 {}

protected:
	virtual bool Get(bool& ) const { return false; };
	virtual bool Get(s32& ) const { return false; }
	virtual bool Get(f32& ) const { return false; }
	virtual bool Get(std::string&) const { return false; }
	virtual bool Get(std::vector<f32>& ) const { return false; }

public:
	virtual std::string Print() const = 0;
};

class _CmdLineArgBool : public _CmdLineArgData
{
private:
	bool  m_bool;

public:
	explicit _CmdLineArgBool(bool flag) : m_bool(flag) {}

protected:
	virtual bool Get(bool& bOut) const override { bOut = m_bool; return true; }
	virtual bool Get(s32& nOut) const override { nOut = (s32)m_bool; return true; }
	virtual bool Get(f32& fOut) const override { fOut = (f32)m_bool; return true; }

public:
	virtual std::string Print() const override { return m_bool ? "true" : "false"; }
};

class _CmdLineArgS32 : public _CmdLineArgData
{
private:
	s32 m_val;

public:
	explicit _CmdLineArgS32(s32 val) : m_val(val) {}

protected:
	virtual bool Get(s32& nOut) const override { nOut = m_val; return true; }
	virtual bool Get(f32& fOut) const override { fOut = (f32)m_val; return true; }

public:
	virtual std::string Print() const override { return std::to_string(m_val); }
};

class _CmdLineArgF32 : public _CmdLineArgData
{
private:
	f32 m_val;

public:
	explicit _CmdLineArgF32(f32 val) : m_val(val) {}

protected:
	virtual bool Get(s32& nOut) const override { nOut = (s32)m_val; return true; }
	virtual bool Get(f32& fOut) const override { fOut = m_val; return true;}

public:
	virtual std::string Print() const override { return std::to_string(m_val); }
};

class _CmdLineArgArray : public _CmdLineArgData
{
private:
	std::vector<f32> m_vVals;

public:
	_CmdLineArgArray(const float* pVals, u32 arrSize)
	{
		Assert(pVals);
		Assert(arrSize);

		if(arrSize > 0 && pVals)
		{
			m_vVals.resize(arrSize);
			memcpy(m_vVals.data(), pVals, arrSize * sizeof(*pVals));
		}
	}

	explicit _CmdLineArgArray(const std::vector<f32>& vVals)
	{
		Assert(vVals.size());
		m_vVals = vVals;
	}

	explicit _CmdLineArgArray(std::vector<f32>&& vVals) : 
		m_vVals(std::move(vVals))
	{
		Assert(m_vVals.size());
	}

	virtual ~_CmdLineArgArray() override { m_vVals.clear(); }

protected:
	virtual bool Get(std::vector<f32>& vOut) const override { vOut = m_vVals; return true; }

public:
	virtual std::string Print() const override
	{
		std::string printString;

		for(u32 i = 0; i < m_vVals.size(); ++i)
		{
			printString += std::to_string(m_vVals[i]);

			if(i != m_vVals.size() - 1)
			{
				printString += ", ";
			}
		}

		return printString;
	}
};

class _CmdLineArgString : public _CmdLineArgData
{
private:
	std::string m_string;

public:
	explicit _CmdLineArgString(const std::string& cmdLineString) : m_string(cmdLineString) { Assert(m_string.size()); }
	explicit _CmdLineArgString(std::string&& cmdLineString) : m_string(std::move(cmdLineString)) { Assert(m_string.size()); }

protected:
	virtual bool Get(std::string& szOut) const override { szOut = m_string; return true; }

public:
	virtual std::string Print() const override { return m_string; }
};

} // namespace recon

#endif // _RECON_CMDLINEARGDATA_H_
