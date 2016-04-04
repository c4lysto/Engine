#ifndef _RECON_ATOMIC_H_
#define _RECON_ATOMIC_H_

#include <atomic>

namespace recon
{

template<typename _StorageType>
class _Atomic
{
	static_assert(!std::is_pointer<_StorageType>::value, "Atomic Storage Type Is A Pointer, Use AtomicPtr Instead!");

public:
	typedef _StorageType Type;

private:
	std::atomic<_StorageType> m_atomicVal;

public:
	_Atomic() {}
	_Atomic(_StorageType val) : m_atomicVal(val) {}

	__forceinline operator _StorageType() const { return m_atomicVal.load(); }

	__forceinline bool CompareExchange(_StorageType& expectedVal_SetIfFalse, _StorageType valToSet) { return m_atomicVal.compare_exchange_strong(&expectedVal_SetIfFalse, valToSet); }

	__forceinline _StorageType FetchAssign(_StorageType val) { return m_atomicVal.exchange(val); }
	__forceinline _StorageType operator=(_StorageType val) { m_atomicVal.exchange(val); return val; }

	__forceinline _StorageType FetchAdd(_StorageType val) { return m_atomicVal += val; }
	__forceinline _StorageType operator+(_StorageType val) const { return m_atomicVal.load() + val; }
	__forceinline _StorageType operator+=(_StorageType val) { return (m_atomicVal += val) + val; }

	__forceinline _StorageType FetchSub(_StorageType val) { return m_atomicVal -= val; }
	__forceinline _StorageType operator-(_StorageType val) const { return m_atomicVal.load() - val; }
	__forceinline _StorageType operator-=(_StorageType val) { return (m_atomicVal -= val) - val; }

	__forceinline _StorageType FetchAnd(_StorageType& val) { return m_atomicVal &= val; }
	__forceinline _StorageType operator&(_StorageType val) const { return m_atomicVal.load() & val; }
	__forceinline _StorageType operator&=(_StorageType val) { return (m_atomicVal &= val) & val; }

	__forceinline _StorageType FetchOr(_StorageType val) { return m_atomicVal |= val; }
	__forceinline _StorageType operator|(_StorageType val) const { return m_atomicVal.load() | val; }
	__forceinline _StorageType operator|=(_StorageType val) { return (m_atomicVal |= val) | val; }

	__forceinline _StorageType FetchXor(_StorageType val) { return m_atomicVal ^= val; }
	__forceinline _StorageType operator^(_StorageType val) const { return m_atomicVal.load() ^ val; }
	__forceinline _StorageType operator^=(_StorageType val) { return (m_atomicVal ^= val) ^ val; }

	__forceinline _StorageType operator++() { return ++m_atomicVal; }
	__forceinline _StorageType operator++(int) { return m_atomicVal++; }

	__forceinline _StorageType operator--() { return --m_atomicVal; }
	__forceinline _StorageType operator--(int) { return m_atomicVal--; }
};

typedef _Atomic<bool> AtomicBool;
typedef _Atomic<char> AtomicChar;
typedef _Atomic<unsigned char> AtomicUChar;
typedef _Atomic<wchar_t> AtomicWChar;
typedef _Atomic<short> AtomicShort;
typedef _Atomic<unsigned short> AtomicUShort;
typedef _Atomic<int> AtomicInt;
typedef _Atomic<unsigned int> AtomicUInt;
typedef _Atomic<long long> AtomicLongLong;
typedef _Atomic<unsigned long long> AtomicULongLong;
typedef _Atomic<std::size_t> AtomicSizeT;

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
	typedef size_t _PtrSizeType;

private:
	std::atomic<_StorageType*> m_atomicPtr;

private:
	__forceinline _StorageType* _Get() const { return m_atomicPtr.load(); }

public:
	AtomicPtr() : m_atomicPtr(nullptr) {}
	AtomicPtr(_StorageType* const ptr) : m_atomicPtr(ptr) {}

	__forceinline operator _StorageType*() const { return _Get(); }

	__forceinline bool CompareExchange(_StorageType*& expectedVal_SetIfFalse, _StorageType* valToSet) { return m_atomicPtr.compare_exchange_strong(&expectedVal_SetIfFalse, valToSet); }

	__forceinline _StorageType* FetchAssign(_StorageType* val) { return m_atomicPtr.exchange(val); }
	__forceinline _StorageType* operator=(_StorageType* val) { m_atomicPtr.exchange(val); return val; }

	__forceinline _StorageType* FetchAdd(_PtrSizeType val) { return m_atomicPtr += val; }
	__forceinline _StorageType* operator+(_PtrSizeType val) const { return _Get() + val; }
	__forceinline _StorageType* operator+=(_PtrSizeType val) { return (m_atomicPtr += val) + val; }

	__forceinline _StorageType* FetchSub(_PtrSizeType val) { return m_atomicPtr -= val; }
	__forceinline _StorageType* operator-(_PtrSizeType val) const { return _Get() - val; }
	__forceinline _StorageType* operator-=(_PtrSizeType val) { return (m_atomicPtr -= val) - val; }

	__forceinline _StorageType* FetchAnd(_PtrSizeType val) { return m_atomicPtr &= val; }
	__forceinline _StorageType* operator&(_PtrSizeType val) const { return _Get() & val; }
	__forceinline _StorageType* operator&=(_PtrSizeType val) { return (m_atomicPtr &= val) & val; }

	__forceinline _StorageType* FetchOr(_PtrSizeType val) { return m_atomicPtr |= val; }
	__forceinline _StorageType* operator|(_PtrSizeType val) const { return _Get() | val; }
	__forceinline _StorageType* operator|=(_PtrSizeType val) { return (m_atomicPtr |= val) | val; }

	__forceinline _StorageType* FetchXor(_PtrSizeType val) { return m_atomicPtr ^= val; }
	__forceinline _StorageType* operator^(_PtrSizeType val) const { return _Get() ^ val; }
	__forceinline _StorageType* operator^=(_PtrSizeType val) { return (m_atomicPtr ^= val) ^ val; }

	__forceinline _StorageType* operator++() { return ++m_atomicPtr; }
	__forceinline _StorageType* operator++(int) { return m_atomicPtr++; }

	__forceinline _StorageType* operator--() { return --m_atomicPtr; }
	__forceinline _StorageType* operator--(int) { return m_atomicPtr--; }
};

} // namespace recon

#endif // _RECON_ATOMIC_H_