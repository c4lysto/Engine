#ifndef _RECON_HASHSTRING_H_
#define _RECON_HASHSTRING_H_

#include <string>

#include "UtilitiesInclude.h"

#define USE_COMPILE_TIME_HASH_STRING (0)

namespace recon
{

class HashString
{
private:
	class ImplicitConstCharStringWrapper
	{
	public:
		ImplicitConstCharStringWrapper(const char* szString) : m_szString(szString){}
		const char* m_szString;
	};

protected:
	u32 m_Hash;

	u32 _ComputeHash(const char* szString) const;

#if USE_COMPILE_TIME_HASH_STRING
	template<size_t arrSize>
	constexpr u32 _ComputeHash_Const(const char (&szString)[arrSize]) const
	{
		return _ComputeHash(szString);
	}
#endif // USE_COMPILE_TIME_HASH_STRING

public:
	HashString() : m_Hash(0) {}
	HashString(const HashString& rhs) : m_Hash(rhs.m_Hash) {}
	HashString(HashString&& rhs) : m_Hash(rhs.m_Hash) {}
	explicit HashString(const u32& rhs) : m_Hash(rhs) {}
	explicit HashString(u32&& rhs) : m_Hash(rhs) {}
	HashString(ImplicitConstCharStringWrapper stringWrapper);

#if USE_COMPILE_TIME_HASH_STRING
	template<size_t arrSize>
	__forceinline explicit HashString(const char (&szString)[arrSize]);
#endif // USE_COMPILE_TIME_HASH_STRING

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


#if USE_COMPILE_TIME_HASH_STRING
template<size_t arrSize>
__forceinline HashString::HashString(const char (&szString)[arrSize]) :
	m_Hash(_ComputeHash_Const(szString))
{
}
#endif // USE_COMPILE_TIME_HASH_STRING

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

	const std::string& GetString() const { return m_String; }
};

#if RECON_DEBUG
typedef HashWithString HashWithDebugString;
#else
typedef HashString HashWithDebugString;
#endif // !RECON_DEBUG

} // namespace recon

#endif // _RECON_HASHSTRING_H_