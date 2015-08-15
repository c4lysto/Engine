
__forceinline Vec2V::Vec2V(const float& fVal)
{
	row = VectorSet(fVal);
}

__forceinline Vec2V::Vec2V(const float& fX, const float& fY)
{
	row = VectorSet(fX, fY, VEC_FILL_VAL, VEC_FILL_VAL);
}

__forceinline Vec2V::Vec2V(ScalarV_In vVal)
{
	row = vVal.GetVector();
}

__forceinline Vec2V::Vec2V(ScalarV_In vX, ScalarV_In vY)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W2>(vX.GetVector(), vY.GetVector());
}

//__forceinline Vec2V::Vec2V(Vec2V_In vVector)
//{
//	row = vVector.row;
//}

#if !RECON_OS_64BIT
__forceinline Vec2V::Vec2V(Vec2V&& vVector)
{
	row = move(vVector.row);
}
#endif // !RECON_OS_64BIT

__forceinline Vec2V::Vec2V(Vector_In rhs)
{
	row = rhs;
}

#if !RECON_OS_64BIT
__forceinline Vec2V::Vec2V(Vector&& rhs)
{
	row = move(rhs);
}
#endif // !RECON_OS_64BIT

__forceinline void RECON_VEC_CALLCONV Vec2V::SetX(ScalarV_In xVal)
{
	row = VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(row, xVal.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec2V::SetY(ScalarV_In yVal)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(row, yVal.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec2V::SetZ(ScalarV_In zVal)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, zVal.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec2V::SetW(ScalarV_In wVal)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(row, wVal.GetVector());
}

__forceinline Vec2V_Out Vec2V::operator-() const
{
	return Vec2V(VectorNegate(row));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator=(Vec2V_In vVector)
{
	if(this != &vVector) { row = vVector.row; }
	return *this;
}

#if !RECON_OS_64BIT
__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator=(Vec2V&& vVector)
{
	if(this != vVector)
		row = move(vVector.row);
	return *this;
}
#endif // !RECON_OS_64BIT

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator+(Vec2V_In vVector) const
{
	return Vec2V(VectorAdd(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator+=(Vec2V_In vVector)
{
	row = VectorAdd(row, vVector.row);
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator-(Vec2V_In vVector) const
{
	return Vec2V(VectorSubtract(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator-=(Vec2V_In vVector)
{
	row = VectorSubtract(row, vVector.row);
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator*(Vec2V_In vVector) const
{
	return Vec2V(VectorMultiply(row, vVector.row));
}

__forceinline Vec2V RECON_VEC_CALLCONV Vec2V::operator*(ScalarV_In vScalar) const
{
	return Vec2V(VectorMultiply(row, vScalar.GetVector()));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV operator*(ScalarV_Ref vScalar, Vec2V_In vVector)
{
	return Vec2V(VectorMultiply(vVector.row, vScalar.GetVector()));
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator*=(ScalarV_In vScalar)
{
	row = VectorMultiply(row, vScalar.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator*=(Vec2V_In vVector)
{
	row = VectorMultiply(row, vVector.row);
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator/(Vec2V_In vVector) const
{
	return Vec2V(VectorDivide(row, vVector.row));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator/(ScalarV_In vScalar) const
{
	return Vec2V(VectorDivide(row, vScalar.GetVector()));
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator/=(Vec2V_In vVector)
{
	row = VectorDivide(row, vVector.row);
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator/=(ScalarV_In vScalar)
{
	row = VectorDivide(row, vScalar.GetVector());
}

__forceinline bool RECON_VEC_CALLCONV Vec2V::operator==(Vec2V_In vVector) const
{
	return VectorIsEqualXY(row, vVector.row);
}

__forceinline bool RECON_VEC_CALLCONV Vec2V::operator!=(Vec2V_In vVector) const
{
	return VectorIsNotEqualXY(row, vVector.row);
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator&(Vec2V_In vVector) const
{
	return Vec2V(VectorAnd(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator&=(Vec2V_In vVector)
{
	row = VectorAnd(row, vVector.row);
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator|(Vec2V_In vVector) const
{
	return Vec2V(VectorOr(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator|=(Vec2V_In vVector)
{
	row = VectorOr(row, vVector.row);
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator^(Vec2V_In vVector) const
{
	return Vec2V(VectorXOr(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec2V::operator^=(Vec2V_In vVector)
{
	row = VectorXOr(row, vVector.row);
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2V::operator~() const
{
	return Vec2V(VectorNot(row));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2VInt(int intVal)
{
	return Vec2V(VectorSet(intVal));
}

__forceinline Vec2V_Out RECON_VEC_CALLCONV Vec2VInt(int intX, int intY)
{
	return Vec2V(VectorSet(intX, intY, (int)VEC_FILL_VAL, (int)VEC_FILL_VAL));
}

__forceinline const float& Vec2V::operator[](int index) const
{
	return floatArr[index];
}

__forceinline float& Vec2V::operator[](int index)
{
	return floatArr[index];
}
