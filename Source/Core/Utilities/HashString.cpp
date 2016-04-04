#include "HashString.h"
#include "Debugging\DebugHelp.h"

namespace recon
{

HashString::HashString(ImplicitConstCharStringWrapper stringWrapper) :
	m_Hash(_ComputeHash(stringWrapper.m_szString))
{
	
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

u32 HashString::_ComputeHash(const char* szString) const
{
	// One-At-A-Time Hash Taken From:
	// http://burtleburtle.net/bob/hash/doobs.html

	u32 hash = 0;

	if(szString)
	{
		do
		{
			hash += *szString;
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		while(++szString);

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