#ifndef _RECON_HASHSTRING_H_
#define _RECON_HASHSTRING_H_

#include <string>

#include "UtilitiesInclude.h"

namespace recon
{

class HashString
{
protected:
	u32 m_Hash;

protected:
	u32 ComputeHash(const char* szString);

public:
	HashString() : m_Hash(0) {}
	HashString(const HashString& rhs) : m_Hash(rhs.m_Hash) {}
	HashString(HashString&& rhs) : m_Hash(rhs.m_Hash) {}
	explicit HashString(const u32& rhs) : m_Hash(rhs) {}
	explicit HashString(u32&& rhs) : m_Hash(rhs) {}
	explicit HashString(const char* szString);

	HashString& operator=(const HashString& rhs);
	HashString& operator=(const u32& rhs);

	bool operator==(const HashString& rhs) const {return m_Hash == rhs.m_Hash;}
	bool operator==(const u32& rhs) const { return m_Hash == rhs; }

	bool operator!=(const HashString& rhs) const { return m_Hash != rhs.m_Hash; }
	bool operator!=(const u32& rhs) const { return m_Hash != rhs; }

	bool operator<(const HashString& rhs) const { return m_Hash < rhs.m_Hash; }
	bool operator>(const HashString& rhs) const { return m_Hash > rhs.m_Hash; }

	explicit operator u32() {return m_Hash;}
};

class HashWithString : public HashString
{
private:
	std::string m_String;

public:
	HashWithString() {}
	HashWithString(const HashWithString& rhs) : HashString(rhs), m_String(rhs.m_String) {}
	HashWithString(HashWithString&& rhs) : HashString(std::move(rhs)), m_String(std::move(rhs.m_String)) { rhs.m_Hash = 0; }
	explicit HashWithString(const char* szString) : HashString(szString), m_String(szString) {}

	HashWithString& operator=(const HashWithString& rhs);
	HashWithString& operator=(HashWithString&& rhs);
};

#if RECON_DEBUG
typedef HashWithString HashWithDebugString;
#else
typedef HashString HashWithDebugString;
#endif // !RECON_DEBUG

} // namespace recon

#endif // _RECON_HASHSTRING_H_