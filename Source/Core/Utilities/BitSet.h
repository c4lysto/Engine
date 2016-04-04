#ifndef _RECON_BITSET_H_
#define _RECON_BITSET_H_

namespace recon
{

class _BitSetBase
{
protected:
	__forceinline u8& _GetAssociatedByte(u8*& bitset, u32 bit) const
	{
		return bitset[bit >> 3];
	}

	__forceinline u32 _GetLocalBit(u32 bit) const
	{
		return (1 << (bit & 0x7));
	}

	__forceinline void _SetBit(u8*& bitset, u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		_GetAssociatedByte(bitset, bit) |= _GetLocalBit(bit);
	}

	__forceinline void _ClearBit(u8*& bitset, u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		_GetAssociatedByte(bitset, bit) &= ~_GetLocalBit(bit);
	}

	__forceinline void _SetBit(u8*& bitset, u32 bit, bool bSetBit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		u8& associatedByte = _GetAssociatedByte(bitset, bit);
		const u32 localBit = bit & 0x7;
		associatedByte = (associatedByte & ~(1 << localBit)) | (bSetBit << localBit);
	}

	__forceinline bool _IsSet(u8*& bitset, u32 bit) const
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		return (_GetAssociatedByte(bitset, bit) & _GetLocalBit(bit)) != 0;
	}

	__forceinline void _ToggleBit(u8*& bitset, u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		_GetAssociatedByte(bitset, bit) ^= _GetLocalBit(bit);
	}

	__forceinline void _ClearAllBits(u8*& bitset, u32 numBytes)
	{
		memset(bitset, 0, numBytes);
	}

	__forceinline void _SetAllBits(u8*& bitset, u32 numBytes)
	{
		memset(bitset, 0xFF, numBytes);
	}

};

template<u32 numBits>
class FixedBitSet : public _BitSetBase
{
	static_assert(numBits > 0, "Bit Set - Invalid Bit Set Size!");

private:
	u8 m_Bits[((numBits-1) >> 3) + 1];	
	

public:
	FixedBitSet()
	{
		ClearAllBits();
	}

	__forceinline void SetBit(u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		return _SetBit(m_Bits, bit);
	}

	__forceinline void ClearBit(u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		return _ClearBit(m_Bits, bit);
	}

	__forceinline void SetBit(u32 bit, bool bSetBit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		return _SetBit(m_Bits, bit, bSetBit);
	}

	__forceinline bool IsSet(u32 bit) const
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		return _IsSet(m_Bits, bit);
	}

	__forceinline void ToggleBit(u32 bit)
	{
		Assertf(bit < numBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, numBits);
		return _ToggleBit(m_Bits, bit);
	}

	__forceinline void ClearAllBits()
	{
		return _ClearAllBits(m_Bits, sizeof(m_Bits));
	}

	__forceinline void SetAllBits()
	{
		return _SetAllBits(m_Bits, sizeof(m_Bits));
	}

	__forceinline bool operator[](u32 bit) const
	{
		return IsSet(bit);
	}
};

class BitSet : public _BitSetBase
{
private:
	u8* m_Bits;
	u32 m_NumBits;
	u32 m_BitFieldSize;

public:
	BitSet() :
		m_Bits(nullptr),
		m_NumBits(0),
		m_BitFieldSize(0)
	{
		
	}

	BitSet(u32 numBits)
	{
		Init(numBits);
	}

	~BitSet()
	{
		Reset();
	}

	inline void Init(u32 numBits)
	{
		if(Verify(!m_NumBits, "Bit Field Has Already Been Initialized!"))
		{
			m_NumBits = numBits;
			if(m_NumBits > 0)
			{
				m_BitFieldSize = ((numBits-1) >> 3) + 1;
				m_Bits = new u8[m_BitFieldSize];
			}
		}
	}

	inline void Reset()
	{
		delete[] m_Bits;
		m_Bits = nullptr;
		m_NumBits = 0;
		m_BitFieldSize;
	}

	__forceinline void SetBit(u32 bit)
	{
		Assertf(bit < m_NumBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, m_NumBits);
		if(m_Bits && bit < m_NumBits) { return _SetBit(m_Bits, bit); }
	}

	__forceinline void ClearBit(u32 bit)
	{
		Assertf(bit < m_NumBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, m_NumBits);
		if(m_Bits && bit < m_NumBits) { return _ClearBit(m_Bits, bit); }
	}

	__forceinline void SetBit(u32 bit, bool bSetBit)
	{
		Assertf(bit < m_NumBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, m_NumBits);
		if(m_Bits && bit < m_NumBits) { return _SetBit(m_Bits, bit, bSetBit); }
	}

	__forceinline bool IsSet(u32 bit) const
	{
		Assertf(bit < m_NumBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, m_NumBits);
		return (m_Bits && bit < m_NumBits) ? _IsSet(m_Bits, bit) : false;
	}

	__forceinline void ToggleBit(u32 bit)
	{
		Assertf(bit < m_NumBits, "Bit Field - Trying to Set An Invalid Bit (%d), Max Bits: %d", bit, m_NumBits);
		if(m_Bits && bit < m_NumBits) { _ToggleBit(m_Bits, bit); }
	}

	__forceinline void ClearAllBits()
	{
		if(m_Bits && m_BitFieldSize > 0) { return _ClearAllBits(m_Bits, m_BitFieldSize); }
	}

	__forceinline void SetAllBits()
	{
		if(m_Bits && m_BitFieldSize > 0) { return _SetAllBits(m_Bits, m_BitFieldSize); }
	}

	__forceinline bool operator[](u32 bit) const
	{
		return IsSet(bit);
	}
};

} // namespace recon

#endif // _RECON_BITSET_H_