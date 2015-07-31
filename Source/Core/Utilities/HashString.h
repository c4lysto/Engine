#ifndef _RECON_HASHSTRING_H_
#define _RECON_HASHSTRING_H_
#include "GlobalDefines.h"

namespace recon
{

class HashString
{
private:
	u32 m_Hash;

	u32 ComputeHash(const char* szString);

public:
	HashString() : m_Hash(0) {}
	HashString(HashString&& rhs) : m_Hash(rhs.m_Hash) {}
	explicit HashString(const u32& rhs) : m_Hash(rhs) {}
	explicit HashString(u32&& rhs) : m_Hash(rhs) {}
	explicit HashString(const char* szString);

	const HashString& operator=(const HashString& rhs);
	const HashString& operator=(const u32& rhs);

	bool operator==(const HashString& rhs) const {return m_Hash == rhs.m_Hash;}
	bool operator==(const u32& rhs) const { return m_Hash == rhs; }

	bool operator!=(const HashString& rhs) const { return m_Hash != rhs.m_Hash; }
	bool operator!=(const u32& rhs) const { return m_Hash != rhs; }

	bool operator<(const HashString& rhs) const { return m_Hash < rhs.m_Hash; }
	bool operator>(const HashString& rhs) const { return m_Hash > rhs.m_Hash; }

	operator u32() {return m_Hash;}
};

} // namespace recon

#endif // _RECON_HASHSTRING_H_