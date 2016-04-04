
__forceinline Vec3V::Vec3V(const f32& fVal) : row(VectorSet(fVal))
{
	
}

__forceinline Vec3V::Vec3V(const f32& fX, const f32& fY, const f32& fZ) : row(VectorSet(fX, fY, fZ, VEC_FILL_VAL))
{
	
}

__forceinline Vec3V::Vec3V(ScalarV_In vVal) : row(vVal.GetVectorRef())
{
	
}

__forceinline Vec3V::Vec3V(ScalarV_In vX, ScalarV_In vY, ScalarV_In vZ)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(vX.GetVectorRef(), vY.GetVectorRef());
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, vZ.GetVectorRef());
}

__forceinline Vec3V::Vec3V(Vec2V_In vXY, ScalarV_In vZ) :
	row(VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(vXY.GetVectorRef(), vZ.GetVectorRef()))
{
	
}

__forceinline Vec3V::Vec3V(ScalarV_In vX, Vec2V_In vYZ) :
	row(VectorPermute<VecElem::X2, VecElem::X1, VecElem::Y1, VecElem::W2>(vYZ.GetVectorRef(), vX.GetVectorRef()))
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

__forceinline Vec3V::Vec3V(Vector128_In vVector) : row(vVector)
{

}

#if !RECON_OS_64BIT
__forceinline Vec3V::Vec3V(Vector128&& vVector) : row(std::move(vVector))
{
	
}
#endif // !RECON_OS_64BIT

__forceinline void RECON_VEC_CALLCONV Vec3V::SetX(ScalarV_In vX)
{
	row = VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(row, vX.GetVectorRef());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::SetY(ScalarV_In vY)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(row, vY.GetVectorRef());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::SetZ(ScalarV_In vZ)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, vZ.GetVectorRef());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::SetW(ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(row, vW.GetVectorRef());
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
	if(this != &vVector) { row = std::move(vVector.row); }
	return *this;
}
#endif // !RECON_OS_64BIT

__forceinline void RECON_VEC_CALLCONV Vec3V::operator*=(ScalarV_In vScalar)
{
	row = VectorDivide(row, vScalar.GetVectorRef());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator*=(Vec3V_In rhs)
{
	row = VectorMultiply(row, rhs.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator/(ScalarV_In vScalar) const
{
	return Vec3V(VectorDivide(row, vScalar.GetVectorRef()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator/(Vec3V_In rhs) const
{
	return Vec3V(VectorDivide(row, rhs.row));
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator/=(ScalarV_In vScalar)
{
	row = VectorDivide(row, vScalar.GetVectorRef());
}

__forceinline void RECON_VEC_CALLCONV Vec3V::operator/=(Vec3V_In rhs)
{
	row = VectorDivide(row, rhs.row);
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator*(ScalarV_In vScalar) const
{
	return Vec3V(VectorMultiply(row, vScalar.GetVectorRef()));
}

__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3V::operator*(Vec3V_In rhs) const
{
	return Vec3V(VectorMultiply(row, rhs.row));
}

__forceinline Vec3V RECON_VEC_CALLCONV operator*(ScalarV_Ref vScalar, Vec3V_In vVector)
{
	return Vec3V(VectorMultiply(vScalar.GetVectorRef(), vVector.row));
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

template<s32 constantVal>
__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3VConstant()
{
	return Vec3V(VectorSetConstant<constantVal>());
}

template<s32 constantX, s32 constantY>
__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3VConstant()
{
	return Vec3V(VectorSetConstant<constantX, constantY, 0, 0>());
}

template<s32 constantX, s32 constantY, s32 constantZ>
__forceinline Vec3V_Out RECON_VEC_CALLCONV Vec3VConstant()
{
	return Vec3V(VectorSetConstant<constantX, constantY, constantZ, 0>());
}
