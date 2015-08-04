#ifndef BITSET_H
#define BITSET_H

template<u32 numBits>
class BitSet
{
	CompileTimeAssert(numBits>0, "Bit Set - Invalid Bit Set Size!");

private:
	u8 m_Bits[((numBits-1) >> 3) + 1];

	FORCEINLINE u8& GetAssociatedByte(u32 bit)
	{
		return m_Bits[bit >> 3];
	}

	FORCEINLINE u32 GetLocalBit(u32 bit)
	{
		return (1 << (bit & 0x7));
	}

public:
	BitSet()
	{
		ClearAllBits();
	}

	FORCEINLINE void SetBit(u32 bit)
	{
		Assert(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		GetAssociatedByte(bit) |= GetLocalBit(bit);
	}

	FORCEINLINE void ClearBit(u32 bit)
	{
		Assert(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		GetAssociatedByte(bit) &= ~GetLocalBit(bit);
	}

	FORCEINLINE void SetBit(u32 bit, bool bSetBit)
	{
		Assert(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		bSetBit ? SetBit(bit) : ClearBit(bit);
	}

	FORCEINLINE bool IsSet(u32 bit)
	{
		Assert(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		GetAssociatedByte(bit) & GetLocalBit(bit);
	}

	FORCEINLINE void ToggleBit(u32 bit)
	{
		Assert(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		GetAssociatedByte(bit) ^= GetLocalBit(bit);
	}

	FORCEINLINE void ClearAllBits()
	{
		memset(m_Bits, 0, sizeof(m_Bits));
	}

	FORCEINLINE void SetAllBits()
	{
		memset(m_Bits, 0xFF, sizeof(m_Bits));
	}
};

#endif // BITSET_H