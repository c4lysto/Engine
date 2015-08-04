
FORCEINLINE Vec2V::Vec2V(const float& fVal)
{
	row = VectorSet(fVal);
}

FORCEINLINE Vec2V::Vec2V(const float& fX, const float& fY)
{
	row = VectorSet(fX, fY, VEC_FILL_VAL, VEC_FILL_VAL);
}

FORCEINLINE Vec2V::Vec2V(ScalarV_In vVal)
{
	row = vVal.GetVector();
}

FORCEINLINE Vec2V::Vec2V(ScalarV_In vX, ScalarV_In vY)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W2>(vX.GetVector(), vY.GetVector());
}

//FORCEINLINE Vec2V::Vec2V(Vec2V_In vVector)
//{
//	row = vVector.row;
//}

#if !RECON_OS_64BIT
FORCEINLINE Vec2V::Vec2V(Vec2V&& vVector)
{
	row = move(vVector.row);
}
#endif // !RECON_OS_64BIT

FORCEINLINE Vec2V::Vec2V(Vector_In rhs)
{
	row = rhs;
}

#if !RECON_OS_64BIT
FORCEINLINE Vec2V::Vec2V(Vector&& rhs)
{
	row = move(rhs);
}
#endif // !RECON_OS_64BIT

FORCEINLINE void Vec2V::SetX(ScalarV_In xVal)
{
	row = VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(row, xVal.GetVector());
}

FORCEINLINE void Vec2V::SetY(ScalarV_In yVal)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(row, yVal.GetVector());
}

FORCEINLINE void Vec2V::SetZ(ScalarV_In zVal)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, zVal.GetVector());
}

FORCEINLINE void Vec2V::SetW(ScalarV_In wVal)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(row, wVal.GetVector());
}

FORCEINLINE Vec2V_Out Vec2V::operator-() const
{
	return Vec2V(VectorNegate(row));
}

FORCEINLINE Vec2V_Out Vec2V::operator=(Vec2V_In vVector)
{
	if(this != &vVector) { row = vVector.row; }
	return *this;
}

#if !RECON_OS_64BIT
FORCEINLINE Vec2V_Out Vec2V::operator=(Vec2V&& vVector)
{
	if(this != vVector)
		row = move(vVector.row);
	return *this;
}
#endif // !RECON_OS_64BIT

FORCEINLINE Vec2V_Out Vec2V::operator+(Vec2V_In vVector) const
{
	return Vec2V(VectorAdd(row, vVector.row));
}

FORCEINLINE void Vec2V::operator+=(Vec2V_In vVector)
{
	row = VectorAdd(row, vVector.row);
}

FORCEINLINE Vec2V_Out Vec2V::operator-(Vec2V_In vVector) const
{
	return Vec2V(VectorSubtract(row, vVector.row));
}

FORCEINLINE void Vec2V::operator-=(Vec2V_In vVector)
{
	row = VectorSubtract(row, vVector.row);
}

FORCEINLINE Vec2V_Out Vec2V::operator*(Vec2V_In vVector) const
{
	return Vec2V(VectorMultiply(row, vVector.row));
}

FORCEINLINE Vec2V Vec2V::operator*(ScalarV_In vScalar) const
{
	return Vec2V(VectorMultiply(row, vScalar.GetVector()));
}

FORCEINLINE Vec2V_Out operator*(ScalarV_Ref vScalar, Vec2V_In vVector)
{
	return Vec2V(VectorMultiply(vVector.row, vScalar.GetVector()));
}

FORCEINLINE void Vec2V::operator*=(ScalarV_In vScalar)
{
	row = VectorMultiply(row, vScalar.GetVector());
}

FORCEINLINE void Vec2V::operator*=(Vec2V_In vVector)
{
	row = VectorMultiply(row, vVector.row);
}

FORCEINLINE Vec2V_Out Vec2V::operator/(Vec2V_In vVector) const
{
	return Vec2V(VectorDivide(row, vVector.row));
}

FORCEINLINE Vec2V_Out Vec2V::operator/(ScalarV_In vScalar) const
{
	return Vec2V(VectorDivide(row, vScalar.GetVector()));
}

FORCEINLINE void Vec2V::operator/=(Vec2V_In vVector)
{
	row = VectorDivide(row, vVector.row);
}

FORCEINLINE void Vec2V::operator/=(ScalarV_In vScalar)
{
	row = VectorDivide(row, vScalar.GetVector());
}

FORCEINLINE bool Vec2V::operator==(Vec2V_In vVector) const
{
	return VectorIsEqualXY(row, vVector.row);
}

FORCEINLINE bool Vec2V::operator!=(Vec2V_In vVector) const
{
	return VectorIsNotEqualXY(row, vVector.row);
}

FORCEINLINE Vec2V_Out Vec2V::operator&(Vec2V_In vVector) const
{
	return Vec2V(VectorAnd(row, vVector.row));
}

FORCEINLINE void Vec2V::operator&=(Vec2V_In vVector)
{
	row = VectorAnd(row, vVector.row);
}

FORCEINLINE Vec2V_Out Vec2V::operator|(Vec2V_In vVector) const
{
	return Vec2V(VectorOr(row, vVector.row));
}

FORCEINLINE void Vec2V::operator|=(Vec2V_In vVector)
{
	row = VectorOr(row, vVector.row);
}

FORCEINLINE Vec2V_Out Vec2V::operator^(Vec2V_In vVector) const
{
	return Vec2V(VectorXOr(row, vVector.row));
}

FORCEINLINE void Vec2V::operator^=(Vec2V_In vVector)
{
	row = VectorXOr(row, vVector.row);
}

FORCEINLINE Vec2V_Out Vec2V::operator~() const
{
	return Vec2V(VectorNot(row));
}

FORCEINLINE Vec2V_Out Vec2V::Normalize()
{
	ScalarV mag = Mag(*this);

	// protection against divide by zero
	if(mag)	{ row = VectorDivide(row, mag.GetVector()); }
	return *this;
}

FORCEINLINE Vec2V_Out Vec2VInt(int intVal)
{
#if SSE_AVAILABLE
	return Vec2V(VectorSet(intVal));
#else // if !SSE_AVAILABLE
	return Vec2V(*reinterpret_cast<float*>(&intVal), *reinterpret_cast<float*>(&intVal));
#endif // !SSE_AVAILABLE
}

FORCEINLINE Vec2V_Out Vec2VInt(int intX, int intY)
{
#if SSE_AVAILABLE
	return Vec2V(VectorSet(intX, intY, (int)VEC_FILL_VAL, (int)VEC_FILL_VAL));
#else // if !SSE_AVAILABLE
	return Vec2V(*reinterpret_cast<float*>(&intX), *reinterpret_cast<float*>(&intY));
#endif // !SSE_AVAILABLE
}

FORCEINLINE Vec2V_Out Vec2VIntToFloat(Vec2V_In vec)
{
#if SSE_AVAILABLE
	return Vec2V(VectorIntToFloat(vec.GetVector()));
#else // if !SSE_AVAILABLE
	int intX = *reinterpret_cast<int*>(&vec.GetXRef());
	int intY = *reinterpret_cast<int*>(&vec.GetYRef());
	return Vec2V((float)intX, (float)intY);
#endif // !SSE_AVAILABLE 
}

FORCEINLINE Vec2V_Out Vec2VFloatToInt(Vec2V_In vec)
{
#if SSE_AVAILABLE
	return Vec2V(VectorFloatToInt(vec.GetVector()));
#else // if !SSE_AVAILABLE
	int intX = (int)vec.GetXRef();
	int intY = (int)vec.GetYRef();
	return Vec2V(*reinterpret_cast<float*>(&intX), *reinterpret_cast<float*>(&intY));
#endif // !SSE_AVAILABLE 
}

FORCEINLINE const float& Vec2V::operator[](int index) const
{
	return floatArr[index];
}

FORCEINLINE float& Vec2V::operator[](int index)
{
	return floatArr[index];
}
