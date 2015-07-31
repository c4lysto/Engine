#ifndef ATOMIC_H
#define ATOMIC_H

#include "GlobalDefines.h"

namespace recon
{
s64 AtomicAdd(s64& value, const s64& valueToAdd);
s32 AtomicAdd(s32& value, const s32& valueToAdd);
s16 AtomicAdd(s16& value, const s16& valueToAdd);

s64 AtomicAnd(s64& value, const s64& valueToAnd);
s32 AtomicAnd(s32& value, const s32& valueToAnd);
s16 AtomicAnd(s16& value, const s16& valueToAnd);

s64 AtomicDecrement(s64& value);
s32 AtomicDecrement(s32& value);
s16 AtomicDecrement(s16& value);

void* AtomicSet(void*& ptr, void* const valueToSetTo);
s64 AtomicSet(s64& value, const s64& valueToSetTo);
s32 AtomicSet(s32& value, const s32& valueToSetTo);
s16 AtomicSet(s16& value, const s16& valueToSetTo);

s64 AtomicIncrement(s64& value);
s32 AtomicIncrement(s32& value);
s16 AtomicIncrement(s16& value);

s64 AtomicOr(s64& value, const s64& valueToOr);
s32 AtomicOr(s32& value, const s32& valueToOr);
s16 AtomicOr(s16& value, const s16& valueToOr);

s64 AtomicRead(const s64& value);
s32 AtomicRead(const s32& value);
s16 AtomicRead(const s16& value);

s64 AtomicXor(s64& value, const s64& valueToXor);
s32 AtomicXor(s32& value, const s32& valueToXor);
s16 AtomicXor(s16& value, const s16& valueToXor);

template<class T>
class _Atomic_t
{
private:
	T m_Value;

public:
	_Atomic_t();
	_Atomic_t(const _Atomic_t& rhs);
	explicit _Atomic_t(const T& val);

	T Get() const;

	T operator=(const _Atomic_t& rhs);
	T operator=(const T& rhs);

	T operator+(const _Atomic_t& rhs) const;
	T operator+(const T& rhs) const;

	void operator+=(const _Atomic_t& rhs);
	void operator+=(const T& rhs);

	T operator-(const _Atomic_t& rhs) const;
	T operator-(const T& rhs) const;

	void operator-=(const _Atomic_t& rhs);
	void operator-=(const T& rhs);

	T operator&(const _Atomic_t& rhs) const;
	T operator&(const T& rhs) const;

	void operator&=(const _Atomic_t& rhs);
	void operator&=(const T& rhs);

	T operator|(const _Atomic_t& rhs) const;
	T operator|(const T& rhs) const;

	void operator|=(const _Atomic_t& rhs);
	void operator|=(const T& rhs);

	T operator^(const _Atomic_t& rhs) const;
	T operator^(const T& rhs) const;

	void operator^=(const _Atomic_t& rhs);
	void operator^=(const T& rhs);

	T operator++();
	T operator++(int);

	T operator--();
	T operator--(int);

	explicit operator T() const;
};

typedef _Atomic_t<s64> Atomic64;
typedef _Atomic_t<s32> Atomic32;
typedef _Atomic_t<s16> Atomic16;

template<class T>
__forceinline _Atomic_t<T>::_Atomic_t()
{

}

template<class T>
__forceinline _Atomic_t<T>::_Atomic_t(const _Atomic_t<T>& rhs)
{
	AtomicSet(m_Value, rhs.Get());
}

template<class T>
__forceinline _Atomic_t<T>::_Atomic_t(const T& val)
{
	AtomicSet(m_Value, val);
}

template<class T>
__forceinline T _Atomic_t<T>::Get() const
{
	return AtomicRead(m_Value);
}

template<class T>
__forceinline T _Atomic_t<T>::operator=(const _Atomic_t<T>& rhs)
{
	AtomicSet(m_Value, rhs.Get());
}

template<class T>
__forceinline T _Atomic_t<T>::operator=(const T& rhs)
{
	AtomicSet(m_Value, rhs);
}

template<class T>
__forceinline T _Atomic_t<T>::operator+(const _Atomic_t<T>& rhs) const
{
	return Get() + rhs.Get();
}

template<class T>
__forceinline T _Atomic_t<T>::operator+(const T& rhs) const
{
	return Get() + rhs;
}

template<class T>
__forceinline void _Atomic_t<T>::operator+=(const _Atomic_t<T>& rhs)
{
	AtomicAdd(m_Value, rhs.Get());
}

template<class T>
__forceinline void _Atomic_t<T>::operator+=(const T& rhs)
{
	AtomicAdd(m_Value, rhs);
}

template<class T>
__forceinline T _Atomic_t<T>::operator-(const _Atomic_t<T>& rhs) const
{
	return Get() - rhs.Get();
}

template<class T>
__forceinline T _Atomic_t<T>::operator-(const T& rhs) const
{
	return Get() - rhs;
}

template<class T>
__forceinline void _Atomic_t<T>::operator-=(const _Atomic_t<T>& rhs)
{
	AtomicAdd(m_Value, -rhs.Get());
}

template<class T>
__forceinline void _Atomic_t<T>::operator-=(const T& rhs)
{
	AtomicAdd(m_Value, -rhs);
}

template<class T>
__forceinline T _Atomic_t<T>::operator&(const _Atomic_t<T>& rhs) const
{
	return Get() & rhs.Get();
}

template<class T>
__forceinline T _Atomic_t<T>::operator&(const T& rhs) const
{
	return Get() & rhs;
}

template<class T>
__forceinline void _Atomic_t<T>::operator&=(const _Atomic_t<T>& rhs)
{
	AtomicAnd(m_Value, rhs.Get());
}

template<class T>
__forceinline void _Atomic_t<T>::operator&=(const T& rhs)
{
	AtomicAnd(m_Value, rhs);
}

template<class T>
__forceinline T _Atomic_t<T>::operator|(const _Atomic_t<T>& rhs) const
{
	return Get() | rhs.Get();
}

template<class T>
__forceinline T _Atomic_t<T>::operator|(const T& rhs) const
{
	return Get() | rhs;
}

template<class T>
__forceinline void _Atomic_t<T>::operator|=(const _Atomic_t<T>& rhs)
{
	AtomicOr(m_Value, rhs.Get());
}

template<class T>
__forceinline void _Atomic_t<T>::operator|=(const T& rhs)
{
	AtomicOr(m_Value, rhs);
}

template<class T>
__forceinline T _Atomic_t<T>::operator^(const _Atomic_t<T>& rhs) const
{
	return Get() ^ rhs.Get();
}

template<class T>
__forceinline T _Atomic_t<T>::operator^(const T& rhs) const
{
	return Get() ^ rhs;
}

template<class T>
__forceinline void _Atomic_t<T>::operator^=(const _Atomic_t<T>& rhs)
{
	AtomicXor(m_Value, rhs.Get());
}

template<class T>
__forceinline void _Atomic_t<T>::operator^=(const T& rhs)
{
	AtomicXor(m_Value, rhs);
}

template<class T>
__forceinline T _Atomic_t<T>::operator++()
{
	return AtomicIncrement(m_Value);
}

template<class T>
__forceinline T _Atomic_t<T>::operator++(int)
{
	AtomicIncrement(m_Value);
	return Get();
}

template<class T>
__forceinline T _Atomic_t<T>::operator--()
{
	return AtomicDecrement(m_Value);
}

template<class T>
__forceinline T _Atomic_t<T>::operator--(int)
{
	AtomicDecrement(m_Value);
	return Get();
}

template<class T>
__forceinline _Atomic_t<T>::operator T() const
{
	return Get();
}

#include "Atomic.inl"

#ifndef _Atomic_t
#define _Atomic_t CompileTimeAssert(false, "Do Not Use _Atomic_t Directly! See Atomic.h For Available Implementations");
#endif // _Atomic_t

}

#endif // ATOMIC_H