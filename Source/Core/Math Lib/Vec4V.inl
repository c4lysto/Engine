
//__forceinline Vec4V::Vec4V(Vec4V_In vVector)
//{
//	row = vVector.row;
//}

#if !RECON_OS_64BIT
__forceinline Vec4V::Vec4V(Vec4V&& vVector) : row(vVector.row)
{

}
#endif // !RECON_OS_64BIT

__forceinline Vec4V::Vec4V(Vector_In vVector) : row(vVector)
{
	
}

#if !RECON_OS_64BIT
__forceinline Vec4V::Vec4V(Vector&& vVector) : row(std::move(vVector))
{
	
}
#endif // !RECON_OS_64BIT

__forceinline Vec4V::Vec4V(const f32& fVal) : row(VectorSet(fVal))
{
	
}

__forceinline Vec4V::Vec4V(const f32& fX, const f32& fY, const f32& fZ, const f32& fW) :
	row(VectorSet(fX, fY, fZ, fW))
{
	
}

__forceinline Vec4V::Vec4V(ScalarV_In vVal) : row(vVal.GetVector())
{
	
}

__forceinline Vec4V::Vec4V(ScalarV_In vX, ScalarV_In vY, ScalarV_In vZ, ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(vX.GetVector(), vY.GetVector());
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, vZ.GetVector());
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(row, vW.GetVector());
}

__forceinline Vec4V::Vec4V(Vec2V_In vXY, Vec2V_In vZW) :
	row(VectorPermute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(vXY.GetVector(), vZW.GetVector()))
{
	
}

__forceinline Vec4V::Vec4V(ScalarV_In vX, ScalarV_In vY, Vec2V_In vZW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(vX.GetVector(), vY.GetVector());
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::X2, VecElem::Y2>(row, vZW.GetVector());
}

__forceinline Vec4V::Vec4V(Vec2V_In vXY, ScalarV_In vZ, ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(vZ.GetVector(), vW.GetVector());
	row = VectorPermute<VecElem::X2, VecElem::Y2, VecElem::Z1, VecElem::W1>(row, vXY.GetVector());
}

__forceinline Vec4V::Vec4V(Vec3V_In vXYZ, ScalarV_In vW) : 
	row(VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(vXYZ.GetVector(), vW.GetVector()))
{
	
}

__forceinline Vec4V::Vec4V(ScalarV_In vX, Vec3V_In vYZW) :
	row(VectorPermute<VecElem::X1, VecElem::X2, VecElem::Y2, VecElem::Z2>(vX.GetVector(), vYZW.GetVector()))
{
	
}

__forceinline void RECON_VEC_CALLCONV Vec4V::SetX(ScalarV_In vX)
{
	row = VectorPermute<VecElem::X2, VecElem::Y1, VecElem::Z1, VecElem::W1>(row, vX.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec4V::SetY(ScalarV_In vY)
{
	row = VectorPermute<VecElem::X1, VecElem::Y2, VecElem::Z1, VecElem::W1>(row, vY.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec4V::SetZ(ScalarV_In vZ)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z2, VecElem::W1>(row, vZ.GetVector());
}

__forceinline void RECON_VEC_CALLCONV Vec4V::SetW(ScalarV_In vW)
{
	row = VectorPermute<VecElem::X1, VecElem::Y1, VecElem::Z1, VecElem::W2>(row, vW.GetVector());
}

__forceinline Vec4V_Out Vec4V::operator-() const
{
	return Vec4V(VectorNegate(row));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator=(Vec4V_In vVector)
{
	if(this != &vVector) { row = vVector.row; }
	return *this;
}

#if !RECON_OS_64BIT
__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator=(Vec4V&& vVector)
{
	if(this != &vVector)
		row = move(vVector.row);
	return *this;
}
#endif // !RECON_OS_64BIT

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator-(Vec4V_In vVector) const
{
	return Vec4V(VectorSubtract(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator-=(Vec4V_In vVector)
{
	row = VectorSubtract(row, vVector.row);
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator+(Vec4V_In vVector) const
{
	return Vec4V(VectorAdd(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator+=(Vec4V_In vVector)
{
	row = VectorAdd(row, vVector.row);
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator/(ScalarV_In vScalar) const
{
	return Vec4V(VectorDivide(row, vScalar.GetVector()));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator/=(ScalarV_In vScalar)
{
	row = VectorDivide(row, vScalar.GetVector());
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator/(Vec4V_In vVector) const
{
	return Vec4V(VectorDivide(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator/=(Vec4V_In vVector)
{
	row = VectorDivide(row, vVector.row);
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator*(Vec4V_In vVector) const
{
	return Vec4V(VectorMultiply(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator*=(Vec4V_In vVector)
{
	row = VectorMultiply(row, vVector.row);
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator*(ScalarV_In vScalar) const
{
	return Vec4V(VectorMultiply(row, vScalar.GetVector()));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator*=(ScalarV_In vScalar)
{
	row = VectorMultiply(row, vScalar.GetVector());
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV operator*(ScalarV_Ref vScalar, Vec4V_In vVector)
{
	return Vec4V(VectorMultiply(vVector.GetVector(), vScalar.GetVector()));
}

__forceinline bool RECON_VEC_CALLCONV Vec4V::operator==(Vec4V_In vVector) const
{
	return VectorIsEqualXYZW(row, vVector.row);
}

__forceinline bool RECON_VEC_CALLCONV Vec4V::operator!=(Vec4V_In vVector) const
{
	return VectorIsNotEqualXYZW(row, vVector.row);
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator&(Vec4V_In vVector) const
{
	return Vec4V(VectorAnd(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator&=(Vec4V_In vVector)
{
	row = VectorAnd(row, vVector.row);
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator|(Vec4V_In vVector) const
{
	return Vec4V(VectorOr(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator|=(Vec4V_In vVector)
{
	row = VectorOr(row, vVector.row);
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4V::operator^(Vec4V_In vVector) const
{
	return Vec4V(VectorXOr(row, vVector.row));
}

__forceinline void RECON_VEC_CALLCONV Vec4V::operator^=(Vec4V_In vVector)
{
	row = VectorXOr(row, vVector.row);
}

__forceinline Vec4V_Out Vec4V::operator~() const
{
	return Vec4V(VectorNot(row));
}

__forceinline const f32& Vec4V::operator[](s32 index) const
{
	return floatArr[index];
}

__forceinline f32& Vec4V::operator[](s32 index)
{
	return floatArr[index];
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4VInt(s32 intVal)
{
	return Vec4V(VectorSet(intVal));
}

__forceinline Vec4V_Out RECON_VEC_CALLCONV Vec4VInt(s32 intX, s32 intY, s32 intZ, s32 intW)
{
	return Vec4V(VectorSet(intX, intY, intZ, intW));
}
