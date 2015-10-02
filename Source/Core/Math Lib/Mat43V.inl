
__forceinline Mat43V::Mat43V(const f32& fXx, const f32& fXy, const f32& fXz,
							 const f32& fYx, const f32& fYy, const f32& fYz,
							 const f32& fZx, const f32& fZy, const f32& fZz,
							 const f32& fWx, const f32& fWy, const f32& fWz) :
	xAxis(fXx, fXy, fXz),
	yAxis(fYx, fYy, fYz),
	zAxis(fZx, fZy, fZz),
	wAxis(fWx, fWy, fWz)
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

inline Mat43V::Mat43V(eXRotationInitializer UNUSED_PARAM(eXRotation), const f32& fRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	yAxis = Vec3V(0.0f, fCosAngle, fSinAngle);
	zAxis = Vec3V(0.0f, -fSinAngle, fCosAngle);
}

inline Mat43V::Mat43V(eYRotationInitializer UNUSED_PARAM(eYRotation), const f32& fRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3V(fCosAngle, 0.0f, -fSinAngle);
	zAxis = Vec3V(fSinAngle, 0.0f, fCosAngle);
}

inline Mat43V::Mat43V(eZRotationInitializer UNUSED_PARAM(eZRotation), const f32& fRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3V(fCosAngle, fSinAngle, 0.0f);
	yAxis = Vec3V(-fSinAngle, fCosAngle, 0.0f);
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
	Vector tmp1, tmp2;
	Vector vPosVec(vPos.GetVector());

	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(vPosVec);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(vPosVec);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(vPosVec);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
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
	Vector tmp1, tmp2;
	Vector vPosVec(vPos.GetVector());

	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(vPosVec);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(vPosVec);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(vPosVec);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(vPosVec);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

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

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateGlobalX(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44V(I_ROTATION_X, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateGlobalY(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44V(I_ROTATION_Y, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateGlobalZ(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44V(I_ROTATION_Z, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateLocalX(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat44V(I_ROTATION_X, fRadians) * Mat43ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateLocalY(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat44V(I_ROTATION_Y, fRadians) * Mat43ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat43V::RotateLocalZ(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat44V(I_ROTATION_Z, fRadians) * Mat43ToMat44(*this));
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