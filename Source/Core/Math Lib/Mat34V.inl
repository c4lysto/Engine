
__forceinline Mat34V::Mat34V(const f32& fXx, const f32& fXy, const f32& fXz,
							 const f32& fYx, const f32& fYy, const f32& fYz,
							 const f32& fZx, const f32& fZy, const f32& fZz,
							 const f32& fWx, const f32& fWy, const f32& fWz) :
	xAxis(fXx, fXy, fXz),
	yAxis(fYx, fYy, fYz),
	zAxis(fZx, fZy, fZz),
	wAxis(fWx, fWy, fWz)
{
}

__forceinline Mat34V::Mat34V(Mat34V_In mMatrix) : 
	xAxis(mMatrix.xAxis),
	yAxis(mMatrix.yAxis),
	zAxis(mMatrix.zAxis),
	wAxis(mMatrix.wAxis)
{
}

__forceinline Mat34V::Mat34V(Mat34V&& mMatrix) : 
	xAxis(std::move(mMatrix.xAxis)),
	yAxis(std::move(mMatrix.yAxis)),
	zAxis(std::move(mMatrix.zAxis)),
	wAxis(std::move(mMatrix.wAxis))
{
}

__forceinline Mat34V::Mat34V(Vec3V_In vXAxis,
							 Vec3V_In vYAxis,
							 Vec3V_In vZAxis,
							 Vec3V_In vWAxis) : 
	xAxis(vXAxis),
	yAxis(vYAxis),
	zAxis(vZAxis),
	wAxis(vWAxis)
{
}

inline Mat34V::Mat34V(eIdentityInitializer UNUSED_PARAM(eIdentity)) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
}

inline Mat34V::Mat34V(eXRotationInitializer UNUSED_PARAM(eXRotation), const f32& fRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	yAxis = Vec3V(0.0f, fCosAngle, fSinAngle);
	zAxis = Vec3V(0.0f, -fSinAngle, fCosAngle);
}

inline Mat34V::Mat34V(eYRotationInitializer UNUSED_PARAM(eYRotation), const f32& fRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3V(fCosAngle, 0.0f, -fSinAngle);
	zAxis = Vec3V(fSinAngle, 0.0f, fCosAngle);
}

inline Mat34V::Mat34V(eZRotationInitializer UNUSED_PARAM(eZRotation), const f32& fRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3V(fCosAngle, fSinAngle, 0.0f);
	yAxis = Vec3V(-fSinAngle, fCosAngle, 0.0f);
}

__forceinline Mat34V::Mat34V(eMatrixPositionInitializer UNUSED_PARAM(eMatrixPos), Vec3V_In vPos) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(vPos)
{
}

//__forceinline Mat34V::operator XMMATRIX() const
//{
//	return *(XMMATRIX*)this;
//}
//
//__forceinline Mat34V::operator XMMATRIX*() const
//{
//	return (XMMATRIX*)this;
//}

__forceinline Mat34V_ConstRef RECON_VEC_CALLCONV Mat34V::operator=(Mat34V_In mMatrix)
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

__forceinline Mat34V_ConstRef RECON_VEC_CALLCONV Mat34V::operator=(Mat34V&& mMatrix)
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

inline Vec3V_Out RECON_VEC_CALLCONV operator*(Vec3V_ConstRef vPos, Mat34V_In mMatrix)
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

__forceinline Vec3V_Ref RECON_VEC_CALLCONV operator*=(Vec3V_Ref vPos, Mat34V_In mMatrix)
{
	vPos = ::operator*(vPos, mMatrix);
}

inline Vec3V_Out RECON_VEC_CALLCONV operator*(Vec4V_ConstRef vPos, Mat34V_In mMatrix)
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

__forceinline Mat34V_Out RECON_VEC_CALLCONV Mat34V::operator+(Mat34V_In rhs) const
{
	return Mat34V(xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis, wAxis + rhs.wAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat34V::operator+=(Mat34V_In rhs)
{
	xAxis += rhs.xAxis; yAxis += rhs.yAxis; zAxis += rhs.zAxis; wAxis += rhs.wAxis;
}

__forceinline Mat34V_Out RECON_VEC_CALLCONV Mat34V::operator-(Mat34V_In rhs) const
{
	return Mat34V(xAxis - rhs.xAxis, yAxis - rhs.yAxis, zAxis - rhs.zAxis, wAxis - rhs.wAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat34V::operator-=(Mat34V_In rhs)
{
	xAxis -= rhs.xAxis; yAxis -= rhs.yAxis; zAxis -= rhs.zAxis; wAxis -= rhs.wAxis;
}

__forceinline void RECON_VEC_CALLCONV Mat34V::Rotate_GlobalX(const f32& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44V(I_ROTATION_X, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat34V::Rotate_GlobalY(const f32& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44V(I_ROTATION_Y, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat34V::Rotate_GlobalZ(const f32& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44V(I_ROTATION_Z, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat34V::Rotate_LocalX(const f32& fRadians)
{
	*this = Mat44ToMat34(Mat44V(I_ROTATION_X, fRadians) * Mat34ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat34V::Rotate_LocalY(const f32& fRadians)
{
	*this = Mat44ToMat34(Mat44V(I_ROTATION_Y, fRadians) * Mat34ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat34V::Rotate_LocalZ(const f32& fRadians)
{
	*this = Mat44ToMat34(Mat44V(I_ROTATION_Z, fRadians) * Mat34ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat34V::Scale(Vec3V_In vScale)
{
	xAxis = xAxis * vScale.GetX();
	yAxis = yAxis * vScale.GetY();
	zAxis = zAxis * vScale.GetZ();
}

__forceinline void RECON_VEC_CALLCONV Mat34V::SetScale(Vec3V_In vScale)
{
	xAxis = ::Normalize(xAxis) * vScale.GetX();
	yAxis = ::Normalize(yAxis) * vScale.GetY();
	zAxis = ::Normalize(zAxis) * vScale.GetZ();
}

__forceinline Vec3V_Out Mat34V::GetScale() const
{
	Vec3V retVal(Mag(xAxis), Mag(yAxis), Mag(zAxis));
	return retVal;
}

__forceinline void RECON_VEC_CALLCONV Mat34V::Translate(Vec3V_In vTranslation)
{
	wAxis = wAxis + vTranslation;
}

__forceinline void Mat34V::Transpose3x3()
{
	std::swap(xAxis.GetYRef(), yAxis.GetXRef());
	std::swap(xAxis.GetZRef(), zAxis.GetXRef());
	std::swap(yAxis.GetZRef(), zAxis.GetYRef());
}

__forceinline void Mat34V::Normalize()
{
	xAxis = ::Normalize(xAxis);
	yAxis = ::Normalize(yAxis);
	zAxis = ::Normalize(zAxis);
}

inline void RECON_VEC_CALLCONV Mat34V::LookAt(Vec3V_In mPos, Vec3V_In vWorldUp)
{
	Vec3V vecToPos = ::Normalize(mPos - wAxis);

	// zAxis
	zAxis = vecToPos;

	// xAxis;
	xAxis = ::Normalize(Cross(vWorldUp, zAxis));

	// yAxis;
	yAxis = ::Normalize(Cross(zAxis, xAxis));
}

inline void RECON_VEC_CALLCONV Mat34V::TurnTo(Vec3V_In vPos, const f32& fDeltaTime, f32 fTurnModifier)
{
	Vec3V vecToPos = ::Normalize(vPos - wAxis);

	f32 protection = Dot(vecToPos, zAxis);

	if (protection + 1 <= protection || protection != protection)
	{
		// You are already facing that exact direction
		return;
	}

	f32 fRotation = Dot(vecToPos, xAxis);

	if(fRotation > FLT_EPSILON || fRotation < -FLT_EPSILON)
	{
		// protection to keep the matrix from turning slowly
		// if the position is behind the matrix
		if(Dot(vecToPos, zAxis) < ScalarV(I_ZERO))
			fRotation = (fRotation < 0.0f) ? -1.0f : 1.0f;

		Rotate_LocalY(fRotation * fTurnModifier * fDeltaTime);
	}

	fRotation = Dot(vecToPos, yAxis);

	if(fRotation > FLT_EPSILON || fRotation < -FLT_EPSILON)
		Rotate_LocalX(-fRotation * fTurnModifier * fDeltaTime);

	xAxis = ::Normalize(Cross(g_WorldUp3V, zAxis));
	yAxis = ::Normalize(Cross(zAxis, xAxis));
}