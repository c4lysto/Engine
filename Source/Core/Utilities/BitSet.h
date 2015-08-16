#ifndef _RECON_BITSET_H_
#define _RECON_BITSET_H_

namespace recon
{

template<u32 numBits>
class BitSet
{
	static_assert(numBits>0, "Bit Set - Invalid Bit Set Size!");

private:
	u8 m_Bits[((numBits-1) >> 3) + 1];

	__forceinline u8& GetAssociatedByte(u32 bit)
	{
		return m_Bits[bit >> 3];
	}

	__forceinline u32 GetLocalBit(u32 bit)
	{
		return (1 << (bit & 0x7));
	}

public:
	BitSet()
	{
		ClearAllBits();
	}

	__forceinline void SetBit(u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		GetAssociatedByte(bit) |= GetLocalBit(bit);
	}

	__forceinline void ClearBit(u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		GetAssociatedByte(bit) &= ~GetLocalBit(bit);
	}

	__forceinline void SetBit(u32 bit, bool bSetBit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		u8& associatedByte = GetAssociatedByte(bit);
		associatedByte = (associatedByte & ~(1 << bit)) | (bSetBit << bit);
	}

	__forceinline bool IsSet(u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		return (GetAssociatedByte(bit) & GetLocalBit(bit)) != 0;
	}

	__forceinline void ToggleBit(u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		GetAssociatedByte(bit) ^= GetLocalBit(bit);
	}

	__forceinline void ClearAllBits()
	{
		memset(m_Bits, 0, sizeof(m_Bits));
	}

	__forceinline void SetAllBits()
	{
		memset(m_Bits, 0xFF, sizeof(m_Bits));
	}
};

}

#endif // _RECON_BITSET_H_