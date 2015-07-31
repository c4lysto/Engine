
#include <windows.h>

namespace recon
{

__forceinline s64 AtomicAdd(s64& value, const s64& valueToAdd)
{
	return _InterlockedAdd64((long long volatile*)&value, valueToAdd);
}

__forceinline s32 AtomicAdd(s32& value, const s32& valueToAdd)
{
	return _InterlockedAdd((long volatile*)&value, valueToAdd);
}

__forceinline s16 AtomicAdd(s16& value, const s16& valueToAdd)
{
	_InterlockedExchangeAdd16((short volatile*)&value, valueToAdd);
	return value;
}

__forceinline s64 AtomicAnd(s64& value, const s64& valueToAnd)
{
	return _InterlockedAnd64((long long volatile*)&value, valueToAnd);
}

__forceinline s32 AtomicAnd(s32& value, const s32& valueToAnd)
{
	return _InterlockedAnd((long volatile*)&value, valueToAnd);
}

__forceinline s16 AtomicAnd(s16& value, const s16& valueToAnd)
{
	return _InterlockedAnd16((short volatile*)&value, valueToAnd);
}

__forceinline s64 AtomicDecrement(s64& value)
{
	return _InterlockedDecrement64((long long volatile*)&value);
}

__forceinline s32 AtomicDecrement(s32& value)
{
	return _InterlockedDecrement((long volatile*)&value);
}

__forceinline s16 AtomicDecrement(s16& value)
{
	return _InterlockedDecrement16((short volatile*)&value);
}

__forceinline void* AtomicSet(void*& ptr, void* const valueToSetTo)
{
	return _InterlockedExchangePointer((void* volatile*)&ptr, valueToSetTo);
}

__forceinline s64 AtomicSet(s64& value, const s64& valueToSetTo)
{
	return _InterlockedExchange64((long long volatile*)&value, valueToSetTo);
}

__forceinline s32 AtomicSet(s32& value, const s32& valueToSetTo)
{
	return _InterlockedExchange((long volatile*)&value, valueToSetTo);
}

__forceinline s16 AtomicSet(s16& value, const s16& valueToSetTo)
{
	return _InterlockedExchange16((short volatile*)&value, valueToSetTo);
}

__forceinline s64 AtomicIncrement(s64& value)
{
	return _InterlockedIncrement64((long long volatile*)&value);
}

__forceinline s32 AtomicIncrement(s32& value)
{
	return _InterlockedIncrement((long volatile*)&value);
}

__forceinline s16 AtomicIncrement(s16& value)
{
	return _InterlockedIncrement16((short volatile*)&value);
}

__forceinline s64 AtomicOr(s64& value, const s64& valueToOr)
{
	return _InterlockedOr64((long long volatile*)&value, valueToOr);
}

__forceinline s32 AtomicOr(s32& value, const s32& valueToOr)
{
	return _InterlockedOr((long volatile*)&value, valueToOr);
}

__forceinline s16 AtomicOr(s16& value, const s16& valueToOr)
{
	return _InterlockedOr16((short volatile*)&value, valueToOr);
}

__forceinline s64 AtomicRead(const s64& value)
{
	return _InterlockedAdd64((long long volatile*)&value, 0);
}

__forceinline s32 AtomicRead(const s32& value)
{
	return _InterlockedAdd((long volatile*)&value, 0);
}

__forceinline s16 AtomicRead(const s16& value)
{
	return _InterlockedExchangeAdd16((short volatile*)&value, 0);
}

__forceinline s64 AtomicXor(s64& value, const s64& valueToXor)
{
	return _InterlockedXor64((long long volatile*)&value, valueToXor);
}

__forceinline s32 AtomicXor(s32& value, const s32& valueToXor)
{
	return _InterlockedXor((long volatile*)&value, valueToXor);
}

__forceinline s16 AtomicXor(s16& value, const s16& valueToXor)
{
	return _InterlockedXor16((short volatile*)&value, valueToXor);
}

}