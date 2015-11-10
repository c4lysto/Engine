#ifndef _RECON_ATOMIC_H_
#define _RECON_ATOMIC_H_

#include <atomic>

namespace recon
{

template<typename _StorageType>
class _Atomic
{
private:
	std::atomic<_StorageType> m_atomicVal;

public:
	_Atomic() {}
	_Atomic(_StorageType val) : m_atomicVal(val) {}

	operator _StorageType() const { return m_atomicVal.load(); }


	_StorageType operator=(_StorageType val) { m_atomicVal.exchange(&val); return val; }

	_StorageType operator+(_StorageType val) const { m_atomicVal.load() + val; }
	_StorageType operator+=(_StorageType val) { m_atomicVal += val; }

	_StorageType operator-(_StorageType val) const { return m_atomicVal.load() - val; }
	_StorageType operator-=(_StorageType val) { m_atomicVal -= val; }

	_StorageType operator&(_StorageType val) const { return m_atomicVal.load() & val; }
	_StorageType operator&=(_StorageType val) { m_atomicVal &= val; }

	_StorageType operator|(_StorageType val) const { return m_atomicVal.load() | val; }
	_StorageType operator|=(_StorageType val) { m_atomicVal |= val; }

	_StorageType operator^(_StorageType val) const { return m_atomicVal.load() ^ val; }
	_StorageType operator^=(_StorageType val) { m_atomicVal ^= val; }

	_StorageType operator++() { return ++m_atomicVal; }
	_StorageType operator++(int) { return m_atomicVal++; }

	_StorageType operator--() { return --m_atomicVal; }
	_StorageType operator--(int) { return m_atomicVal--; }
};

typedef _Atomic<bool> AtomicBool;
typedef _Atomic<char> AtomicChar;
typedef _Atomic<wchar_t> AtomicWChar;

typedef _Atomic<s8> AtomicS8;
typedef _Atomic<u8> AtomicU8;
typedef _Atomic<s16> AtomicS16;
typedef _Atomic<u16> AtomicU16;
typedef _Atomic<s32> AtomicS32;
typedef _Atomic<u32> AtomicU32;
typedef _Atomic<s64> AtomicS64;
typedef _Atomic<u64> AtomicU64;


template<typename _StorageType>
class AtomicPtr
{
private:
#if RECON_OS_32BIT
	typedef u32 _PtrSizeType;
#elif RECON_OS_64BIT
	typedef u64 _PtrSizeType;
#endif // RECON_OS_+5BIT

private:
	std::atomic<_StorageType*> m_atomicPtr;

private:
	__forceinline _StorageType* _Get() const { return m_atomicPtr.load(); }

public:
	AtomicPtr() : m_atomicPtr(nullptr) {}
	AtomicPtr(_StorageType* const ptr) : m_atomicPtr(ptr) {}

	operator _StorageType*() const { return _Get(); }

	_StorageType* operator=(_StorageType* val) { m_atomicPtr.exchange(&val); return val; }

	_StorageType* operator+(_PtrSizeType val) const { return _Get() + val; }
	_StorageType* operator+=(_PtrSizeType val) { return m_atomicPtr += val; }

	_StorageType* operator-(_PtrSizeType val) const { return _Get() - val; }
	_StorageType* operator-=(_PtrSizeType val) { return m_atomicPtr -= val; }

	_StorageType* operator&(_PtrSizeType val) const { return _Get() & val; }
	_StorageType* operator&=(_PtrSizeType val) { return m_atomicPtr &= val; }

	_StorageType* operator|(_PtrSizeType val) const { return _Get() | val; }
	_StorageType* operator|=(_PtrSizeType val) { return m_atomicPtr |= val; }

	_StorageType* operator^(_PtrSizeType val) const { return _Get() ^ val; }
	_StorageType* operator^=(_PtrSizeType val) { return m_atomicPtr ^= val; }

	_StorageType* operator++() { return ++m_atomicPtr; }
	_StorageType* operator++(int) { return m_atomicPtr++; }

	_StorageType* operator--() { return --m_atomicPtr; }
	_StorageType* operator--(int) { return m_atomicPtr--; }
};

} // namespace recon

#endif // _RECON_ATOMIC_H_