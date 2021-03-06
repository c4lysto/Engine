
__forceinline Vec3V::Vec3V(const f32& fVal) : row(VectorSet(fVal))
{
	
}

__forceinline Vec3V::Vec3V(const f32& fX, const f32& fY, const f32& fZ) : row(VectorSet(fX, fY, fZ, VEC_FILL_VAL))
{
	
}

__forceinline Vec3V::Vec3V(ScalarV_In vVal) : row(vVal.GetVector())
{
	
}

__forceinline Vec3V::Vec3V(ScalarV_In vX, ScalarV_In vY, ScalarV_In vZ)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(vX.GetVector(), vY.GetVector());
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, vZ.GetVector());
}

__forceinline Vec3V::Vec3V(Vec2V_In vXY, ScalarV_In vZ) :
	row(VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(vXY.GetVector(), vZ.GetVector()))
{
	
}

__forceinline Vec3V::Vec3V(ScalarV_In vX, Vec2V_In vYZ) :
	row(VectorPermute<VecElem::X2, VecElem::X1, VecElem::Y1, VecElem::W2>(vYZ.GetVector(), vX.GetVector()))
{
	
}

//__forceinline Vec3V::Vec3V(Vec3V_In vVector)
//{
//	row = vVector.row;
//}

#if !RECON_OS_64BIT
__forceinline Vec3V::Vec3V(Vec3V&& vVector) :
	row(std::move(vVector.row))
{

}
#endif // !RECON_OS_64BIT

__forceinline Vec3V::Vec3V(Vector_In vVector) : row(vVector)
{

}

#if !RECON_OS_64BIT
__forceinline Vec3V::Vec3V(Vector&& vVector) : row(std::move(vVector))
{
	
}
#endif // !RECON_OS_64BIT

__forceinline void RECON_VEC_CALLCONV Vec3V::SetX(ScalarV_In vX)
{
	row = VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(row, vX.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::SetY(ScalarV_In vY)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(row, vY.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::SetZ(ScalarV_In vZ)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, vZ.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::SetW(ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(row, vW.GetVector());
}

__forceinline Vec3V_Out Vec3V::operator-() const
{
	return Vec3V(VectorNegate(row));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator=(Vec3V_In vVector)
{
	if(this != &vVector) { row = vVector.row; }
	return *this;
}

#if !RECON_OS_64BIT
__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator=(Vec3V&& vVector)
{
	if(this != &vVector)
		row = move(vVector.row);
	return *this;
}
#endif // !RECON_OS_64BIT

__forceinline void RECON_VEC_CALLCONV Vec3V::operator*=(ScalarV_In vScalar)
{
	row = VectorDivide(row, vScalar.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator*=(Vec3V_In rhs)
{
	row = VectorMultiply(row, rhs.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator/(ScalarV_In vScalar) const
{
	return Vec3V(VectorDivide(row, vScalar.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator/(Vec3V_In rhs) const
{
	return Vec3V(VectorDivide(row, rhs.row));
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator/=(ScalarV_In vScalar)
{
	row = VectorDivide(row, vScalar.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator/=(Vec3V_In rhs)
{
	row = VectorDivide(row, rhs.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator*(ScalarV_In vScalar) const
{
	return Vec3V(VectorMultiply(row, vScalar.GetVector()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator*(Vec3V_In rhs) const
{
	return Vec3V(VectorMultiply(row, rhs.row));
}

__forceinline Vec3V RECON_VEC_CALLCONV operator*(ScalarV_Ref vScalar, Vec3V_In vVector)
{
	return Vec3V(VectorMultiply(vScalar.GetVector(), vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator+=(Vec3V_In vVector)
{
	row = VectorAdd(row, vVector.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator+(Vec3V_In vVector) const
{
	return Vec3V(VectorAdd(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator-=(Vec3V_In vVector)
{
	row = VectorSubtract(row, vVector.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator-(Vec3V_In vVector) const
{
	return Vec3V(VectorSubtract(row, vVector.row));
}

__forceinline bool RECON_VEC_CALLCONV Vec3V::operator==(Vec3V_In vVector) const
{
	return VectorIsEqualXYZ(row, vVector.row);
}

__forceinline bool RECON_VEC_CALLCONV Vec3V::operator!=(Vec3V_In vVector) const
{
	return VectorIsNotEqualXYZ(row, vVector.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator&(Vec3V_In vVector) const
{
	return Vec3V(VectorAnd(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator&=(Vec3V_In vVector)
{
	row = VectorAnd(row, vVector.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator|(Vec3V_In vVector) const
{
	return Vec3V(VectorOr(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator|=(Vec3V_In vVector)
{
	row = VectorOr(row, vVector.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator^(Vec3V_In vVector) const
{
	return Vec3V(VectorXOr(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator^=(Vec3V_In vVector)
{
	row = VectorXOr(row, vVector.row);
}

__forceinline Vec3V_Out Vec3V::operator~() const
{
	return Vec3V(VectorNot(row));
}

__forceinline const f32& Vec3V::operator[](s32 index) const
{
	return floatArr[index];
}

__forceinline f32& Vec3V::operator[](s32 index)
{
	return floatArr[index];
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3VInt(s32 intVal)
{
	return Vec3V(VectorSet(intVal));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3VInt(s32 intX, s32 intY, s32 intZ)
{
	return Vec3V(VectorSet(intX, intY, intZ, (s32)VEC_FILL_VAL));
}
