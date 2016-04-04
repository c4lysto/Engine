
__forceinline Mat43V::Mat43V(ScalarV_In vXx, ScalarV_In vXy, ScalarV_In vXz,
							 ScalarV_In vYx, ScalarV_In vYy, ScalarV_In vYz,
							 ScalarV_In vZx, ScalarV_In vZy, ScalarV_In vZz,
							 ScalarV_In vWx, ScalarV_In vWy, ScalarV_In vWz) :
	xAxis(vXx, vXy, vXz),
	yAxis(vYx, vYy, vYz),
	zAxis(vZx, vZy, vZz),
	wAxis(vWx, vWy, vWz)
{
}

__forceinline Mat43V::Mat43V(Mat43V_In mMatrix) : 
	xAxis(mMatrix.xAxis),
	yAxis(mMatrix.yAxis),
	zAxis(mMatrix.zAxis),
	wAxis(mMatrix.wAxis)
{
}

__forceinline Mat43V::Mat43V(Mat43V&& mMatrix) : 
	xAxis(std::move(mMatrix.xAxis)),
	yAxis(std::move(mMatrix.yAxis)),
	zAxis(std::move(mMatrix.zAxis)),
	wAxis(std::move(mMatrix.wAxis))
{
}

__forceinline Mat43V::Mat43V(Vec3V_In vXAxis,
							 Vec3V_In vYAxis,
							 Vec3V_In vZAxis,
							 Vec3V_In vWAxis) : 
	xAxis(vXAxis),
	yAxis(vYAxis),
	zAxis(vZAxis),
	wAxis(vWAxis)
{
}

inline Mat43V::Mat43V(eIdentityInitializer UNUSED_PARAM(eIdentity)) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
}

inline Mat43V::Mat43V(eXRotationInitializer UNUSED_PARAM(eXRotation), ScalarV_In vRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	Vec2V vSinCos(SinCos(vRotationInRadians));
	yAxis = Vec3V(ScalarV(I_ZERO), vSinCos.GetY(), vSinCos.GetX());
	zAxis = Vec3V(ScalarV(I_ZERO), -vSinCos.GetX(), vSinCos.GetY());
}

inline Mat43V::Mat43V(eYRotationInitializer UNUSED_PARAM(eYRotation), ScalarV_In vRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	Vec2V vSinCos(SinCos(vRotationInRadians));
	xAxis = Vec3V(vSinCos.GetY(), ScalarV(I_ZERO), -vSinCos.GetX());
	zAxis = Vec3V(vSinCos.GetX(), ScalarV(I_ZERO), vSinCos.GetY());
}

inline Mat43V::Mat43V(eZRotationInitializer UNUSED_PARAM(eZRotation), ScalarV_In vRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	Vec2V vSinCos(SinCos(vRotationInRadians));
	xAxis = Vec3V(vSinCos.GetY(), vSinCos.GetX(), ScalarV(I_ZERO));
	yAxis = Vec3V(-vSinCos.GetX(), vSinCos.GetY(), ScalarV(I_ZERO));
}

__forceinline Mat43V::Mat43V(eMatrixPositionInitializer UNUSED_PARAM(eMatrixPos), Vec3V_In vPos) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(vPos)
{
}

//__forceinline Mat43V::operator XMMATRIX() const
//{
//	return *(XMMATRIX*)this;
//}
//
//__forceinline Mat43V::operator XMMATRIX*() const
//{
//	return (XMMATRIX*)this;
//}

__forceinline Mat43V_ConstRef RECON_VEC_CALLCONV Mat43V::operator=(Mat43V_In mMatrix)
{
	if(this != &mMatrix)
	{
		xAxis = mMatrix.xAxis;
		yAxis = mMatrix.yAxis;
		zAxis = mMatrix.zAxis;
		wAxis = mMatrix.wAxis;
	}
	return *this;
}

__forceinline Mat43V_ConstRef RECON_VEC_CALLCONV Mat43V::operator=(Mat43V&& mMatrix)
{
	if(this != &mMatrix)
	{
		xAxis = std::move(mMatrix.xAxis);
		yAxis = std::move(mMatrix.yAxis);
		zAxis = std::move(mMatrix.zAxis);
		wAxis = std::move(mMatrix.wAxis);
	}
	return *this;
}

inline Vec3V_Out RECON_VEC_CALLCONV operator*(Vec3V_ConstRef vPos, Mat43V_In mMatrix)
{
	Vector128 tmp1, tmp2;
	Vector128 vPosVec(vPos.GetVectorRef());

	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(vPosVec);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(vPosVec);
	tmp2 = VectorMad(mMatrix.row2, tmp1, tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(vPosVec);
	tmp2 = VectorMad(mMatrix.row3, tmp1, tmp2);
	// Add on mMatrix.row4 since, vPos.w is expected to be 1
	tmp2 = VectorAdd(mMatrix.row4, tmp2);

	return Vec3V(tmp2);
}

__forceinline Vec3V_Ref RECON_VEC_CALLCONV operator*=(Vec3V_Ref vPos, Mat43V_In mMatrix)
{
	vPos = ::operator*(vPos, mMatrix);
}

inline Vec3V_Out RECON_VEC_CALLCONV operator*(Vec4V_ConstRef vPos, Mat43V_In mMatrix)
{
	Vector128 tmp1, tmp2;
	Vector128 vPosVec(vPos.GetVectorRef());

	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(vPosVec);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(vPosVec);
	tmp2 = VectorMad(mMatrix.row2, tmp1, tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(vPosVec);
	tmp2 = VectorMad(mMatrix.row3, tmp1, tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(vPosVec);
	tmp2 = VectorMad(mMatrix.row4, tmp1, tmp2);

	return Vec3V(tmp2);
}

__forceinline Mat43V_Out RECON_VEC_CALLCONV Mat43V::operator+(Mat43V_In rhs) const
{
	return Mat43V(xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis, wAxis + rhs.wAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat43V::operator+=(Mat43V_In rhs)
{
	xAxis += rhs.xAxis; yAxis += rhs.yAxis; zAxis += rhs.zAxis; wAxis += rhs.wAxis;
}

__forceinline Mat43V_Out RECON_VEC_CALLCONV Mat43V::operator-(Mat43V_In rhs) const
{
	return Mat43V(xAxis - rhs.xAxis, yAxis - rhs.yAxis, zAxis - rhs.zAxis, wAxis - rhs.wAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat43V::operator-=(Mat43V_In rhs)
{
	xAxis -= rhs.xAxis; yAxis -= rhs.yAxis; zAxis -= rhs.zAxis; wAxis -= rhs.wAxis;
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateGlobalX(ScalarV_In vRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44V(I_ROTATION_X, vRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateGlobalY(ScalarV_In vRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44V(I_ROTATION_Y, vRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateGlobalZ(ScalarV_In vRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44V(I_ROTATION_Z, vRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateLocalX(ScalarV_In vRadians)
{
	*this = Mat44ToMat43(Mat44V(I_ROTATION_X, vRadians) * Mat43ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateLocalY(ScalarV_In vRadians)
{
	*this = Mat44ToMat43(Mat44V(I_ROTATION_Y, vRadians) * Mat43ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateLocalZ(ScalarV_In vRadians)
{
	*this = Mat44ToMat43(Mat44V(I_ROTATION_Z, vRadians) * Mat43ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::Scale(Vec3V_In vScale)
{
	xAxis = xAxis * vScale.GetX();
	yAxis = yAxis * vScale.GetY();
	zAxis = zAxis * vScale.GetZ();
}

__forceinline void RECON_VEC_CALLCONV Mat43V::SetScale(Vec3V_In vScale)
{
	xAxis = ::Normalize(xAxis) * vScale.GetX();
	yAxis = ::Normalize(yAxis) * vScale.GetY();
	zAxis = ::Normalize(zAxis) * vScale.GetZ();
}

__forceinline Vec3V_Out Mat43V::GetScale() const
{
	Vec3V retVal(Mag(xAxis), Mag(yAxis), Mag(zAxis));
	return retVal;
}

__forceinline void RECON_VEC_CALLCONV Mat43V::Translate(Vec3V_In vTranslation)
{
	wAxis = wAxis + vTranslation;
}