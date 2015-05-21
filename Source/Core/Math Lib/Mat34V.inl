
__forceinline Mat34V::Mat34V(const float& fXx, const float& fXy, const float& fXz,
							 const float& fYx, const float& fYy, const float& fYz,
							 const float& fZx, const float& fZy, const float& fZz,
							 const float& fWx, const float& fWy, const float& fWz) :
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
	xAxis(move(mMatrix.xAxis)),
	yAxis(move(mMatrix.yAxis)),
	zAxis(move(mMatrix.zAxis)),
	wAxis(move(mMatrix.wAxis))
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

inline Mat34V::Mat34V(eXRotationInitializer UNUSED_PARAM(eXRotation), const float& fRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	float fSinAngle = sin(fRotationInRadians);
	float fCosAngle = cos(fRotationInRadians);
	yAxis = Vec3V(0.0f, fCosAngle, fSinAngle);
	zAxis = Vec3V(0.0f, -fSinAngle, fCosAngle);
}

inline Mat34V::Mat34V(eYRotationInitializer UNUSED_PARAM(eYRotation), const float& fRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	float fSinAngle = sin(fRotationInRadians);
	float fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3V(fCosAngle, 0.0f, -fSinAngle);
	zAxis = Vec3V(fSinAngle, 0.0f, fCosAngle);
}

inline Mat34V::Mat34V(eZRotationInitializer UNUSED_PARAM(eZRotation), const float& fRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	float fSinAngle = sin(fRotationInRadians);
	float fCosAngle = cos(fRotationInRadians);
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

__forceinline Mat34V_ConstRef Mat34V::operator=(Mat34V_In mMatrix)
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

__forceinline Mat34V_ConstRef Mat34V::operator=(Mat34V&& mMatrix)
{
	if(this != &mMatrix)
	{
		xAxis = move(mMatrix.xAxis);
		yAxis = move(mMatrix.yAxis);
		zAxis = move(mMatrix.zAxis);
		wAxis = move(mMatrix.wAxis);
	}
	return *this;
}

__forceinline Vec3V_Out operator*(Vec3V_ConstRef vPos, Mat34V_In mMatrix)
{
	return ::operator*(Vec4V(vPos, ScalarV(I_ONE)), mMatrix);
}

__forceinline Vec3V_Ref operator*=(Vec3V_Ref vPos, Mat34V_In mMatrix)
{
	vPos = ::operator*(vPos, mMatrix);
}

inline Vec3V_Out operator*(Vec4V_ConstRef vPos, Mat34V_In mMatrix)
{
	Vector tmp1, tmp2;

	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(vPos.GetVector());
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(vPos.GetVector());
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(vPos.GetVector());
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(vPos.GetVector());
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	return Vec3V(tmp2);
}

__forceinline Mat34V_Out Mat34V::operator+(Mat34V_In rhs) const
{
	return Mat34V(xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis, wAxis + rhs.wAxis);
}

__forceinline void Mat34V::operator+=(Mat34V_In rhs)
{
	xAxis += rhs.xAxis; yAxis += rhs.yAxis; zAxis += rhs.zAxis; wAxis += rhs.wAxis;
}

__forceinline Mat34V_Out Mat34V::operator-(Mat34V_In rhs) const
{
	return Mat34V(xAxis - rhs.xAxis, yAxis - rhs.yAxis, zAxis - rhs.zAxis, wAxis - rhs.wAxis);
}

__forceinline void Mat34V::operator-=(Mat34V_In rhs)
{
	xAxis -= rhs.xAxis; yAxis -= rhs.yAxis; zAxis -= rhs.zAxis; wAxis -= rhs.wAxis;
}

__forceinline void Mat34V::Rotate_GlobalX(const float& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44V(I_ROTATION_X, fRadians));
}

__forceinline void Mat34V::Rotate_GlobalY(const float& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44V(I_ROTATION_Y, fRadians));
}

__forceinline void Mat34V::Rotate_GlobalZ(const float& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44V(I_ROTATION_Z, fRadians));
}

__forceinline void Mat34V::Rotate_LocalX(const float& fRadians)
{
	*this = Mat44ToMat34(Mat44V(I_ROTATION_X, fRadians) * Mat34ToMat44(*this));
}

__forceinline void Mat34V::Rotate_LocalY(const float& fRadians)
{
	*this = Mat44ToMat34(Mat44V(I_ROTATION_Y, fRadians) * Mat34ToMat44(*this));
}

__forceinline void Mat34V::Rotate_LocalZ(const float& fRadians)
{
	*this = Mat44ToMat34(Mat44V(I_ROTATION_Z, fRadians) * Mat34ToMat44(*this));
}

__forceinline void Mat34V::Scale(Vec3V_In vScale)
{
	xAxis = xAxis * vScale.GetX();
	yAxis = yAxis * vScale.GetY();
	zAxis = zAxis * vScale.GetZ();
}

__forceinline void Mat34V::SetScale(Vec3V_In vScale)
{
	xAxis = ::Normalize(xAxis) * vScale.GetX();
	yAxis = ::Normalize(yAxis) * vScale.GetY();
	zAxis = ::Normalize(zAxis) * vScale.GetZ();
}

__forceinline Vec3V Mat34V::GetScale() const
{
	Vec3V retVal(Mag(xAxis), Mag(yAxis), Mag(zAxis));
	return retVal;
}

__forceinline void Mat34V::Translate(Vec3V_In vTranslation)
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
	xAxis.Normalize();
	yAxis.Normalize();
	zAxis.Normalize();
}

inline void Mat34V::LookAt(Vec3V_In mPos, Vec3V_In vWorldUp)
{
	Vec3V vecToPos = mPos - wAxis;
	vecToPos.Normalize();

	// zAxis
	zAxis = vecToPos;

	// xAxis;
	xAxis = Cross(vWorldUp, zAxis);
	xAxis.Normalize();

	// yAxis;
	yAxis = Cross(zAxis, xAxis);
	yAxis.Normalize();
}

inline void Mat34V::TurnTo(Vec3V_In vPos, const float& fDeltaTime, float fTurnModifier)
{
	Vec3V vecToPos = vPos - wAxis;
	vecToPos.Normalize();

	float protection = Dot(vecToPos, zAxis);

	if (protection + 1 <= protection || protection != protection)
	{
		// You are already facing that exact direction
		return;
	}

	float fRotation = Dot(vecToPos, xAxis);

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