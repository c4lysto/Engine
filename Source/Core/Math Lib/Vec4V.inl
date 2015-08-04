
//FORCEINLINE Vec4V::Vec4V(Vec4V_In vVector)
//{
//	row = vVector.row;
//}

#if !RECON_OS_64BIT
FORCEINLINE Vec4V::Vec4V(Vec4V&& vVector)
{
	row = vVector.row;
}
#endif // !RECON_OS_64BIT

FORCEINLINE Vec4V::Vec4V(Vector_In vVector)
{
	row = vVector;
}

#if !RECON_OS_64BIT
FORCEINLINE Vec4V::Vec4V(Vector&& vVector)
{
	row = move(vVector);
}
#endif // !RECON_OS_64BIT

FORCEINLINE Vec4V::Vec4V(const float& fVal)
{
	row = VectorSet(fVal);
}

FORCEINLINE Vec4V::Vec4V(const float& fX, const float& fY, const float& fZ, const float& fW)
{
	row = VectorSet(fX, fY, fZ, fW);
}

FORCEINLINE Vec4V::Vec4V(ScalarV_In vVal)
{
	row = vVal.GetVector();
}

FORCEINLINE Vec4V::Vec4V(ScalarV_In vX, ScalarV_In vY, ScalarV_In vZ, ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(vX.GetVector(), vY.GetVector());
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, vZ.GetVector());
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(row, vW.GetVector());
}

FORCEINLINE Vec4V::Vec4V(Vec2V_In vXY, Vec2V_In vZW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(vXY.GetVector(), vZW.GetVector());
}

FORCEINLINE Vec4V::Vec4V(ScalarV_In vX, ScalarV_In vY, Vec2V_In vZW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(vX.GetVector(), vY.GetVector());
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(row, vZW.GetVector());
}

FORCEINLINE Vec4V::Vec4V(Vec2V_In vXY, ScalarV_In vZ, ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(vZ.GetVector(), vW.GetVector());
	row = VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z1, VecElem::W1>(row, vXY.GetVector());
}

FORCEINLINE Vec4V::Vec4V(Vec3V_In vXYZ, ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(vXYZ.GetVector(), vW.GetVector());
}

FORCEINLINE Vec4V::Vec4V(ScalarV_In vX, Vec3V_In vYZW)
{
	row = VectorPermute<VecElem::X1, VecElem::X2, VecElem::Y2, VecElem::Z2>(vX.GetVector(), vYZW.GetVector());
}

FORCEINLINE void Vec4V::SetX(ScalarV_In vX)
{
	row = VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(row, vX.GetVector());
}

FORCEINLINE void Vec4V::SetY(ScalarV_In vY)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(row, vY.GetVector());
}

FORCEINLINE void Vec4V::SetZ(ScalarV_In vZ)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, vZ.GetVector());
}

FORCEINLINE void Vec4V::SetW(ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(row, vW.GetVector());
}

FORCEINLINE Vec4V_Out Vec4V::operator-() const
{
	return Vec4V(VectorNegate(row));
}

FORCEINLINE Vec4V_Out Vec4V::operator=(Vec4V_In vVector)
{
	if(this != &vVector) { row = vVector.row; }
	return *this;
}

#if !RECON_OS_64BIT
FORCEINLINE Vec4V_Out Vec4V::operator=(Vec4V&& vVector)
{
	if(this != &vVector)
		row = move(vVector.row);
	return *this;
}
#endif // !RECON_OS_64BIT

FORCEINLINE Vec4V_Out Vec4V::operator-(Vec4V_In vVector) const
{
	return Vec4V(VectorSubtract(row, vVector.row));
}

FORCEINLINE void Vec4V::operator-=(Vec4V_In vVector)
{
	row = VectorSubtract(row, vVector.row);
}

FORCEINLINE Vec4V_Out Vec4V::operator+(Vec4V_In vVector) const
{
	return Vec4V(VectorAdd(row, vVector.row));
}

FORCEINLINE void Vec4V::operator+=(Vec4V_In vVector)
{
	row = VectorAdd(row, vVector.row);
}

FORCEINLINE Vec4V_Out Vec4V::operator/(ScalarV_In vScalar) const
{
	return Vec4V(VectorDivide(row, vScalar.GetVector()));
}

FORCEINLINE void Vec4V::operator/=(ScalarV_In vScalar)
{
	row = VectorDivide(row, vScalar.GetVector());
}

FORCEINLINE Vec4V_Out Vec4V::operator/(Vec4V_In vVector) const
{
	return Vec4V(VectorDivide(row, vVector.row));
}

FORCEINLINE void Vec4V::operator/=(Vec4V_In vVector)
{
	row = VectorDivide(row, vVector.row);
}

FORCEINLINE Vec4V_Out Vec4V::operator*(Vec4V_In vVector) const
{
	return Vec4V(VectorMultiply(row, vVector.row));
}

FORCEINLINE void Vec4V::operator*=(Vec4V_In vVector)
{
	row = VectorMultiply(row, vVector.row);
}

FORCEINLINE Vec4V_Out Vec4V::operator*(ScalarV_In vScalar) const
{
	return Vec4V(VectorMultiply(row, vScalar.GetVector()));
}

FORCEINLINE void Vec4V::operator*=(ScalarV_In vScalar)
{
	row = VectorMultiply(row, vScalar.GetVector());
}

FORCEINLINE Vec4V_Out operator*(ScalarV_Ref vScalar, Vec4V_In vVector)
{
	return Vec4V(VectorMultiply(vVector.GetVector(), vScalar.GetVector()));
}

FORCEINLINE bool Vec4V::operator==(Vec4V_In vVector) const
{
	return VectorIsEqualXYZW(row, vVector.row);
}

FORCEINLINE bool Vec4V::operator!=(Vec4V_In vVector) const
{
	return VectorIsNotEqualXYZW(row, vVector.row);
}

FORCEINLINE Vec4V_Out Vec4V::operator&(Vec4V_In vVector) const
{
	return Vec4V(VectorAnd(row, vVector.row));
}

FORCEINLINE void Vec4V::operator&=(Vec4V_In vVector)
{
	row = VectorAnd(row, vVector.row);
}

FORCEINLINE Vec4V_Out Vec4V::operator|(Vec4V_In vVector) const
{
	return Vec4V(VectorOr(row, vVector.row));
}

FORCEINLINE void Vec4V::operator|=(Vec4V_In vVector)
{
	row = VectorOr(row, vVector.row);
}

FORCEINLINE Vec4V_Out Vec4V::operator^(Vec4V_In vVector) const
{
	return Vec4V(VectorXOr(row, vVector.row));
}

FORCEINLINE void Vec4V::operator^=(Vec4V_In vVector)
{
	row = VectorXOr(row, vVector.row);
}

FORCEINLINE Vec4V_Out Vec4V::operator~() const
{
	return Vec4V(VectorNot(row));
}

FORCEINLINE const float& Vec4V::operator[](int index) const
{
	return floatArr[index];
}

FORCEINLINE float& Vec4V::operator[](int index)
{
	return floatArr[index];
}

FORCEINLINE Vec4V_Out Vec4V::Normalize()
{
	ScalarV mag = Mag(*this);
	if(mag) { row = VectorDivide(row, mag.GetVector()); }
	return *this;
}

FORCEINLINE Vec4V_Out Vec4VInt(int intVal)
{
	return Vec4V(VectorSet(intVal));
}

FORCEINLINE Vec4V_Out Vec4VInt(int intX, int intY, int intZ, int intW)
{
	return Vec4V(VectorSet(intX, intY, intZ, intW));
}

FORCEINLINE Vec4V_Out Vec4VIntToFloat(Vec4V_In vec)
{
	return Vec4V(VectorIntToFloat(vec.GetVector()));
}

FORCEINLINE Vec4V_Out Vec4VFloatToInt(Vec4V_In vec)
{
	return Vec4V(VectorFloatToInt(vec.GetVector())); 
}
