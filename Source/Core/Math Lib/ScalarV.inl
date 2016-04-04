

#if !RECON_OS_64BIT
__forceinline ScalarV::ScalarV(ScalarV&& vVector) : row(std::move(vVector.row))
{
	Assertf(IsValid(), "ScalarV Is Invalid, Components MUST Be Splatted Across The Vector128!");
}
#endif // !RECON_OS_64BIT

__forceinline ScalarV::ScalarV(Vector128_In vVector) : row(vVector)
{
	Assertf(IsValid(), "ScalarV Is Invalid, Components MUST Be Splatted Across The Vector128!");
}

__forceinline ScalarV::ScalarV(const f32& fVal) : row(VectorSet(fVal))
{
	
}

__forceinline ScalarV::ScalarV(const s32& iVal) : row(VectorSet(iVal))
{
	
}

__forceinline Vector128_Out ScalarV::GetVector() const
{
	return row;
}

__forceinline Vector128_Ref ScalarV::GetVectorRef()
{
	return row;
}

__forceinline Vector128_ConstRef ScalarV::GetVectorRef() const
{
	return row;
}

__forceinline f32 ScalarV::GetFloat() const
{
	return VectorExtractFloat<VecElem::X>(row);
}

__forceinline f32 ScalarV::AsFloat() const
{
	return GetFloat();
}

__forceinline s32 ScalarV::GetInt() const
{
	return VectorExtractS32<VecElem::X>(row);
}

__forceinline s32 ScalarV::AsInt() const
{
	return GetInt();
}

__forceinline bool ScalarV::IsValid() const
{
	// Checks if all the components are the same value
	return (VectorMoveMask(VectorIsEqualS32(VectorSplat<VecElem::X>(row), VectorSplat<VecElem::Y>(row))) & \
			VectorMoveMask(VectorIsEqualS32(VectorSplat<VecElem::Z>(row), VectorSplat<VecElem::W>(row))) & \
			VectorMoveMask(VectorIsEqualS32(VectorSplat<VecElem::X>(row), VectorSplat<VecElem::Z>(row)))) == 0xF;
}

__forceinline ScalarV_Out ScalarV::operator-() const
{
	return ScalarV(VectorNegate(row));
}

__forceinline ScalarV_Ref ScalarV::operator=(ScalarV_In rhs)
{
	if(this != &rhs)
	{
		row = rhs.row;
		Assertf(IsValid(), "ScalarV Is Invalid, Components MUST Be Splatted Across The Vector128!");
	}
	return *this;
}

__forceinline ScalarV_Out ScalarV::operator+(ScalarV_In rhs) const
{
	return ScalarV(VectorAdd(row, rhs.row));
}

__forceinline ScalarV_Ref ScalarV::operator+=(ScalarV_In rhs)
{
	row = VectorAdd(row, rhs.row);
	return *this;
}

__forceinline ScalarV_Out ScalarV::operator-(ScalarV_In rhs) const
{
	return ScalarV(VectorSubtract(row, rhs.row));
}

__forceinline ScalarV_Ref ScalarV::operator-=(ScalarV_In rhs)
{
	row = VectorSubtract(row, rhs.row);
	return *this;
}

__forceinline ScalarV_Out ScalarV::operator*(ScalarV_In rhs) const
{
	return ScalarV(VectorMultiply(row, rhs.row));
}

__forceinline ScalarV_Ref ScalarV::operator*=(ScalarV_In rhs)
{
	row = VectorMultiply(row, rhs.row);
	return *this;
}

__forceinline ScalarV_Out ScalarV::operator/(ScalarV_In rhs) const
{
	return ScalarV(VectorDivide(row, rhs.row));
}

__forceinline ScalarV_Ref ScalarV::operator/=(ScalarV_In rhs)
{
	row = VectorDivide(row, rhs.row);
	return *this;
}

// Logical Operators
__forceinline ScalarV_Out ScalarV::operator<<(s32 nCount) const
{
	return ScalarV(VectorLeftShift(row, nCount));
}

__forceinline ScalarV_Ref ScalarV::operator<<=(s32 nCount)
{
	row = VectorLeftShift(row, nCount);
	return *this;
}

__forceinline ScalarV_Out ScalarV::operator>>(s32 nCount) const
{
	return ScalarV(VectorRightShift(row, nCount));
}

__forceinline ScalarV_Ref ScalarV::operator>>=(s32 nCount)
{
	row = VectorRightShift(row, nCount);
	return *this;
}

__forceinline ScalarV_Out ScalarV::operator&(ScalarV_In rhs) const
{
	return ScalarV(VectorAnd(row, rhs.row));
}

__forceinline ScalarV_Ref ScalarV::operator&=(ScalarV_In rhs)
{
	row = VectorAnd(row, rhs.row);
	return *this;
}

__forceinline ScalarV_Out ScalarV::operator|(ScalarV_In rhs) const
{
	return ScalarV(VectorOr(row, rhs.row));
}

__forceinline ScalarV_Ref ScalarV::operator|=(ScalarV_In rhs)
{
	row = VectorOr(row, rhs.row);
	return *this;
}

__forceinline ScalarV_Out ScalarV::operator~() const
{
	return ScalarV(VectorNot(row));
}

__forceinline bool ScalarV::operator==(ScalarV_In rhs) const
{
	return VectorIsEqualS32X(row, rhs.row);
}

__forceinline bool ScalarV::operator!=(ScalarV_In rhs) const
{
	return VectorIsNotEqualS32X(row, rhs.row);
}

__forceinline bool ScalarV::operator<(ScalarV_In rhs) const
{
	return VectorIsLessThanX(row, rhs.row);
}

__forceinline bool ScalarV::operator<=(ScalarV_In rhs) const
{
	return VectorIsLessThanOrEqualX(row, rhs.row);
}

__forceinline bool ScalarV::operator>(ScalarV_In rhs) const
{
	return VectorIsGreaterThanX(row, rhs.row);
}

__forceinline bool ScalarV::operator>=(ScalarV_In rhs) const
{
	return VectorIsGreaterThanOrEqualX(row, rhs.row);
}

__forceinline ScalarV::operator bool() const
{
	return *this != ScalarV(I_ZERO);
}

__forceinline ScalarV_Out ScalarVInt(s32 scalar)
{
	return ScalarV(VectorSet(scalar));
}

template<s32 constantVal>
__forceinline ScalarV_Out ScalarVConstant()
{
	return ScalarV(VectorSetConstant<constantVal>());
}
