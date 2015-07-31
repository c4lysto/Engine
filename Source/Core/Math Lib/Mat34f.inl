
__forceinline Mat34f::Mat34f(const float& fXx, const float& fXy, const float& fXz,
							 const float& fYx, const float& fYy, const float& fYz,
							 const float& fZx, const float& fZy, const float& fZz,
							 const float& fWx, const float& fWy, const float& fWz) : 
	  xAxis(fXx, fXy, fXz),
	  yAxis(fYx, fYy, fYz),
	  zAxis(fZx, fZy, fZz),
	  wAxis(fWx, fWy, fWz)
{
}

__forceinline Mat34f::Mat34f(Mat34f_In mMatrix) : 
	xAxis(mMatrix.xAxis),
	yAxis(mMatrix.yAxis),
	zAxis(mMatrix.zAxis),
	wAxis(mMatrix.wAxis)
{
}

__forceinline Mat34f::Mat34f(Mat34f&& mMatrix) :
	xAxis(std::move(mMatrix.xAxis)),
	yAxis(std::move(mMatrix.yAxis)),
	zAxis(std::move(mMatrix.zAxis)),
	wAxis(std::move(mMatrix.wAxis))
{
}

__forceinline Mat34f::Mat34f(eIdentityInitializer eIdentity) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
}

inline Mat34f::Mat34f(eXRotationInitializer eXRotation, const float& fRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	float fSinAngle = sin(fRotationInRadians);
	float fCosAngle = cos(fRotationInRadians);
	yAxis = Vec3f(0.0f, fCosAngle, fSinAngle);
	zAxis = Vec3f(0.0f, -fSinAngle, fCosAngle);
}

inline Mat34f::Mat34f(eYRotationInitializer eYRotation, const float& fRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	float fSinAngle = sin(fRotationInRadians);
	float fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3f(fCosAngle, 0.0f, -fSinAngle);
	zAxis = Vec3f(fSinAngle, 0.0f, fCosAngle);
}

inline Mat34f::Mat34f(eZRotationInitializer eZRotation, const float& fRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	float fSinAngle = sin(fRotationInRadians);
	float fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3f(fCosAngle, fSinAngle, 0.0f);
	yAxis = Vec3f(-fSinAngle, fCosAngle, 0.0f);
}

__forceinline Mat34f::Mat34f(eMatrixPositionInitializer eMatrixPos, Vec3f_In vPos) : 
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(vPos)
{

}

__forceinline Mat34f::Mat34f(Vec3f_In vXAxis,
						     Vec3f_In vYAxis,
						     Vec3f_In vZAxis,
						     Vec3f_In vWAxis) :
	xAxis(vXAxis),
	yAxis(vYAxis),
	zAxis(vZAxis),
	wAxis(vWAxis)
{
}

__forceinline Mat34f_Ref Mat34f::operator=(Mat34f_In mMatrix)
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

__forceinline Mat34f_Ref Mat34f::operator=(Mat34f&& mMatrix)
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

__forceinline Vec3f_Out operator*(Vec3f_ConstRef vPos, Mat34f_In mMatrix)
{
	return ::operator*(Vec4f(vPos, 1.0f), mMatrix);
}

__forceinline Vec3f_Ref operator*=(Vec3f_Ref vPos, Mat34f_In mMatrix)
{
	return vPos = ::operator*(vPos, mMatrix);
}

inline Vec3f_Out operator*(Vec4f_In vVector, Mat34f_In mMatrix)
{
	const float& fX = vVector.GetXRef();
	const float& fY = vVector.GetYRef();
	const float& fZ = vVector.GetZRef();
	const float& fW = vVector.GetWRef();

#if SSE_AVAILABLE
	Vector tmp1, tmp2;

	Vec3f_ConstRef vXAxis = mMatrix.xAxis;
	Vec3f_ConstRef vYAxis = mMatrix.yAxis;
	Vec3f_ConstRef vZAxis = mMatrix.zAxis;
	Vec3f_ConstRef vWAxis = mMatrix.wAxis;

	// get the top row
	tmp1 = VectorSet(fX);
	tmp2 = VectorMultiply(VectorLoadU(vXAxis.GetVector()), tmp1);
	tmp1 = VectorSet(fY);
	tmp2 = VectorAdd(VectorMultiply(VectorLoadU(vYAxis.GetVector()), tmp1), tmp2);
	tmp1 = VectorSet(fZ);
	tmp2 = VectorAdd(VectorMultiply(VectorLoadU(vZAxis.GetVector()), tmp1), tmp2);
	tmp1 = VectorSet(fW);
	tmp2 = VectorAdd(VectorMultiply(VectorLoadU(vWAxis.GetVector()), tmp1), tmp2);

	return Vec3f(tmp2);
#else
	return Vec3f(fX * mMatrix.xAxis.GetXRef() + fY * mMatrix.yAxis.GetXRef() + fZ * mMatrix.zAxis.GetXRef() + fW * mMatrix.wAxis.GetXRef(),
				 fX * mMatrix.xAxis.GetYRef() + fY * mMatrix.yAxis.GetYRef() + fZ * mMatrix.zAxis.GetYRef() + fW * mMatrix.wAxis.GetYRef(),
				 fX * mMatrix.xAxis.GetZRef() + fY * mMatrix.yAxis.GetZRef() + fZ * mMatrix.zAxis.GetZRef() + fW * mMatrix.wAxis.GetZRef());
#endif
}

__forceinline Mat34f_Out Mat34f::operator+(Mat34f_In rhs) const
{
	return Mat34f(xAxis + rhs.xAxis, yAxis + rhs.yAxis,  zAxis + rhs.zAxis, wAxis + rhs.wAxis);
}

__forceinline void Mat34f::operator+=(Mat34f_In rhs)
{
	xAxis += rhs.xAxis; yAxis += rhs.yAxis; zAxis += rhs.zAxis; wAxis += rhs.wAxis;
}

__forceinline void Mat34f::MakeIdentity3x3()
{
	xAxis = g_IdentityX3;
	yAxis = g_IdentityY3;
	zAxis = g_IdentityZ3;
}

__forceinline Mat34f_Out Mat34f::operator-(Mat34f_In rhs) const
{
	return Mat34f(xAxis - rhs.xAxis, yAxis - rhs.yAxis,  zAxis - rhs.zAxis, wAxis - rhs.wAxis);
}

__forceinline void Mat34f::operator-=(Mat34f_In rhs)
{
	xAxis -= rhs.xAxis; yAxis -= rhs.yAxis; zAxis -= rhs.zAxis; wAxis -= rhs.wAxis;
}

__forceinline void Mat34f::Rotate_GlobalX(const float& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44f(I_ROTATION_X, fRadians));
}

__forceinline void Mat34f::Rotate_GlobalY(const float& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44f(I_ROTATION_Y, fRadians));
}

__forceinline void Mat34f::Rotate_GlobalZ(const float& fRadians)
{
	*this = Mat44ToMat34(Mat34ToMat44(*this) * Mat44f(I_ROTATION_Z, fRadians));
}

__forceinline void Mat34f::Rotate_LocalX(const float& fRadians)
{
	*this = Mat44ToMat34(Mat44f(I_ROTATION_X, fRadians) * Mat34ToMat44(*this));
}

__forceinline void Mat34f::Rotate_LocalY(const float& fRadians)
{
	*this = Mat44ToMat34(Mat44f(I_ROTATION_Y, fRadians) * Mat34ToMat44(*this));
}

__forceinline void Mat34f::Rotate_LocalZ(const float& fRadians)
{
	*this = Mat44ToMat34(Mat44f(I_ROTATION_Z, fRadians) * Mat34ToMat44(*this));
}

__forceinline void Mat34f::Scale(Vec3f_In vScale)
{
	xAxis = xAxis * vScale.GetX();
	yAxis = yAxis * vScale.GetY();
	zAxis = zAxis * vScale.GetZ();
}

__forceinline void Mat34f::SetScale(Vec3f_In vScale)
{
	xAxis = ::Normalize(xAxis) * vScale.GetX();
	yAxis = ::Normalize(yAxis) * vScale.GetY();
	zAxis = ::Normalize(zAxis) * vScale.GetZ();
}

__forceinline Vec3f_Out Mat34f::GetScale() const
{
	Vec3f retVal(Mag(xAxis), Mag(yAxis), Mag(zAxis));
	return retVal;
}

__forceinline void Mat34f::Translate(Vec3f vTranslation)
{
	wAxis = wAxis + vTranslation;
}

__forceinline void Mat34f::Transpose3x3()
{
	std::swap(xAxis.GetYRef(), yAxis.GetXRef());
	std::swap(xAxis.GetZRef(), zAxis.GetXRef());
	std::swap(yAxis.GetZRef(), zAxis.GetYRef());
}

__forceinline void Mat34f::Normalize()
{
	xAxis = ::Normalize(xAxis);
	yAxis = ::Normalize(yAxis);
	zAxis = ::Normalize(zAxis);
}

__forceinline void Mat34f::LookAt(Vec3f_In mPos, Vec3f_In vWorldUp)
{
	zAxis = ::Normalize(mPos - wAxis);
	xAxis = ::Normalize(Cross(vWorldUp, zAxis));
	yAxis = ::Normalize(Cross(zAxis, xAxis));
}

inline void Mat34f::TurnTo(Vec3f_In vPos, const float& fDeltaTime, float fTurnModifier)
{
	Vec3f vecToPos = ::Normalize(vPos - wAxis);

	float protection = Dot(vecToPos, zAxis);

	if (protection != protection)
	{
		// You are already facing that exact direction
		return;
	}

	float fRotation = Dot(vecToPos, xAxis);

	if(fRotation > FLT_EPSILON || fRotation < -FLT_EPSILON)
	{
		// protection to keep the matrix from turning slowly
		// if the position is behind the matrix
		if(Dot(vecToPos, zAxis) < 0.0f)
			fRotation = (fRotation < 0.0f) ? -1.0f : 1.0f;

		Rotate_LocalY(fRotation * fTurnModifier * fDeltaTime);
	}

	fRotation = Dot(vecToPos, yAxis);

	if(fRotation > FLT_EPSILON || fRotation < -FLT_EPSILON)
		Rotate_LocalX(-fRotation * fTurnModifier * fDeltaTime);

	xAxis = ::Normalize(Cross(g_WorldUp, zAxis));
	yAxis = ::Normalize(Cross(zAxis, xAxis));
}
