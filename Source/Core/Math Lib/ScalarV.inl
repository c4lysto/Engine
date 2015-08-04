

#if !RECON_OS_64BIT
FORCEINLINE ScalarV::ScalarV(ScalarV&& vVector)
{
	row = move(vVector.row);
}
#endif // !RECON_OS_64BIT

FORCEINLINE ScalarV::ScalarV(Vector_In vVector)
{
	row = vVector;
	Assert(IsValid(), "ScalarV Is Invalid, Components MUST Be Splatted Across The Vector!");
}

FORCEINLINE ScalarV::ScalarV(const float& fVal)
{
	row = VectorSet(fVal);
}

FORCEINLINE ScalarV::ScalarV(const int& iVal)
{
	row = VectorSet(iVal);
}

FORCEINLINE Vector_Out ScalarV::GetVector() const
{
	return row;
}

FORCEINLINE float ScalarV::GetFloat() const
{
	return VectorExtractFloat<VecElem::X>(row);
}

FORCEINLINE float ScalarV::AsFloat() const
{
	return GetFloat();
}

FORCEINLINE int ScalarV::GetInt() const
{
	return VectorExtractInt<VecElem::X>(row);
}

FORCEINLINE int ScalarV::AsInt() const
{
	return GetInt();
}

FORCEINLINE bool ScalarV::IsValid() const
{
	// Checks if all the components are the same value
	return (VectorSignMask(VectorIsEqualInt(VectorSplat<VecElem::X>(row), VectorSplat<VecElem::Y>(row))) & \
			VectorSignMask(VectorIsEqualInt(VectorSplat<VecElem::Z>(row), VectorSplat<VecElem::W>(row))) & \
			VectorSignMask(VectorIsEqualInt(VectorSplat<VecElem::X>(row), VectorSplat<VecElem::Z>(row)))) == 0xF;
}

FORCEINLINE ScalarV_Out ScalarV::operator-() const
{
	return ScalarV(VectorNegate(row));
}

FORCEINLINE ScalarV_Ref ScalarV::operator=(ScalarV_In rhs)
{
	if(this != &rhs)
	{
		row = rhs.row;
		Assert(IsValid(), "ScalarV Is Invalid, Components MUST Be Splatted Across The Vector!");
	}
	return *this;
}

FORCEINLINE ScalarV_Out ScalarV::operator+(ScalarV_In rhs) const
{
	return ScalarV(VectorAdd(row, rhs.row));
}

FORCEINLINE ScalarV_Ref ScalarV::operator+=(ScalarV_In rhs)
{
	row = VectorAdd(row, rhs.row);
	return *this;
}

FORCEINLINE ScalarV_Out ScalarV::operator-(ScalarV_In rhs) const
{
	return ScalarV(VectorSubtract(row, rhs.row));
}

FORCEINLINE ScalarV_Ref ScalarV::operator-=(ScalarV_In rhs)
{
	row = VectorSubtract(row, rhs.row);
	return *this;
}

FORCEINLINE ScalarV_Out ScalarV::operator*(ScalarV_In rhs) const
{
	return ScalarV(VectorMultiply(row, rhs.row));
}

FORCEINLINE ScalarV_Ref ScalarV::operator*=(ScalarV_In rhs)
{
	row = VectorMultiply(row, rhs.row);
	return *this;
}

FORCEINLINE ScalarV_Out ScalarV::operator/(ScalarV_In rhs) const
{
	return ScalarV(VectorDivide(row, rhs.row));
}

FORCEINLINE ScalarV_Ref ScalarV::operator/=(ScalarV_In rhs)
{
	row = VectorDivide(row, rhs.row);
	return *this;
}

// Logical Operators
FORCEINLINE ScalarV_Out ScalarV::operator<<(int nCount) const
{
	return ScalarV(VectorLeftShift(row, nCount));
}

FORCEINLINE ScalarV_Ref ScalarV::operator<<=(int nCount)
{
	row = VectorLeftShift(row, nCount);
	return *this;
}

FORCEINLINE ScalarV_Out ScalarV::operator>>(int nCount) const
{
	return ScalarV(VectorRightShift(row, nCount));
}

FORCEINLINE ScalarV_Ref ScalarV::operator>>=(int nCount)
{
	row = VectorRightShift(row, nCount);
	return *this;
}

FORCEINLINE ScalarV_Out ScalarV::operator&(ScalarV_In rhs) const
{
	return ScalarV(VectorAnd(row, rhs.row));
}

FORCEINLINE ScalarV_Ref ScalarV::operator&=(ScalarV_In rhs)
{
	row = VectorAnd(row, rhs.row);
	return *this;
}

FORCEINLINE ScalarV_Out ScalarV::operator|(ScalarV_In rhs) const
{
	return ScalarV(VectorOr(row, rhs.row));
}

FORCEINLINE ScalarV_Ref ScalarV::operator|=(ScalarV_In rhs)
{
	row = VectorOr(row, rhs.row);
	return *this;
}

FORCEINLINE ScalarV_Out ScalarV::operator~() const
{
	return ScalarV(VectorNot(row));
}

FORCEINLINE bool ScalarV::operator==(ScalarV_In rhs) const
{
	return VectorIsEqualIntX(row, rhs.row);
}

FORCEINLINE bool ScalarV::operator!=(ScalarV_In rhs) const
{
	return VectorIsNotEqualIntX(row, rhs.row);
}

FORCEINLINE bool ScalarV::operator<(ScalarV_In rhs) const
{
	return VectorIsLessThanX(row, rhs.row);
}

FORCEINLINE bool ScalarV::operator<=(ScalarV_In rhs) const
{
	return VectorIsLessThanOrEqualX(row, rhs.row);
}

FORCEINLINE bool ScalarV::operator>(ScalarV_In rhs) const
{
	return VectorIsGreaterThanX(row, rhs.row);
}

FORCEINLINE bool ScalarV::operator>=(ScalarV_In rhs) const
{
	return VectorIsGreaterThanOrEqualX(row, rhs.row);
}

FORCEINLINE ScalarV::operator bool() const
{
	return *this != ScalarV(I_ZERO);
}