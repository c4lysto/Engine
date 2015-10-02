#include "HashString.h"
#include "Debugging\DebugHelp.h"

namespace recon
{

HashString::HashString(const char* szString)
{
	m_Hash = ComputeHash(szString);
}

HashString& HashString::operator=(const HashString& rhs)
{
	if(this != &rhs)
	{
		if(m_Hash == 0)
		{
			m_Hash = rhs.m_Hash;
		}
	}
	return *this;
}

HashString& HashString::operator=(const u32& rhs)
{
	if(m_Hash == 0)
	{
		m_Hash = rhs;
	}
	return *this;
}

u32 HashString::ComputeHash(const char* szString)
{
	// One-At-A-Time Hash Taken From:
	// http://burtleburtle.net/bob/hash/doobs.html

	u32 hash = 0;

	if(szString)
	{
		for(u32 i = 0; szString[i]; ++i)
		{
			hash += szString[i];
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
	}

	return hash;
}

HashWithString& HashWithString::operator=(const HashWithString& rhs)
{
	if(this != &rhs)
	{
		m_Hash = rhs.m_Hash;
		m_String = rhs.m_String;
	}

	return *this;
}

HashWithString& HashWithString::operator=(HashWithString&& rhs)
{
	if(this != &rhs)
	{
		m_Hash = rhs.m_Hash;
		m_String = std::move(rhs.m_String);
	}

	return *this;
}

} // namespace recon