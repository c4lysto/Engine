
__forceinline Mat43f::Mat43f(const f32& fXx, const f32& fXy, const f32& fXz,
							 const f32& fYx, const f32& fYy, const f32& fYz,
							 const f32& fZx, const f32& fZy, const f32& fZz,
							 const f32& fWx, const f32& fWy, const f32& fWz) : 
	  xAxis(fXx, fXy, fXz),
	  yAxis(fYx, fYy, fYz),
	  zAxis(fZx, fZy, fZz),
	  wAxis(fWx, fWy, fWz)
{
}

__forceinline Mat43f::Mat43f(Mat43f_In mMatrix) : 
	xAxis(mMatrix.xAxis),
	yAxis(mMatrix.yAxis),
	zAxis(mMatrix.zAxis),
	wAxis(mMatrix.wAxis)
{
}

__forceinline Mat43f::Mat43f(Mat43f&& mMatrix) :
	xAxis(std::move(mMatrix.xAxis)),
	yAxis(std::move(mMatrix.yAxis)),
	zAxis(std::move(mMatrix.zAxis)),
	wAxis(std::move(mMatrix.wAxis))
{
}

__forceinline Mat43f::Mat43f(eIdentityInitializer eIdentity) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
}

inline Mat43f::Mat43f(eXRotationInitializer eXRotation, const f32& fRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	yAxis = Vec3f(0.0f, fCosAngle, fSinAngle);
	zAxis = Vec3f(0.0f, -fSinAngle, fCosAngle);
}

inline Mat43f::Mat43f(eYRotationInitializer eYRotation, const f32& fRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3f(fCosAngle, 0.0f, -fSinAngle);
	zAxis = Vec3f(fSinAngle, 0.0f, fCosAngle);
}

inline Mat43f::Mat43f(eZRotationInitializer eZRotation, const f32& fRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3f(fCosAngle, fSinAngle, 0.0f);
	yAxis = Vec3f(-fSinAngle, fCosAngle, 0.0f);
}

__forceinline Mat43f::Mat43f(eMatrixPositionInitializer eMatrixPos, Vec3f_In vPos) : 
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(vPos)
{

}

__forceinline Mat43f::Mat43f(Vec3f_In vXAxis,
						     Vec3f_In vYAxis,
						     Vec3f_In vZAxis,
						     Vec3f_In vWAxis) :
	xAxis(vXAxis),
	yAxis(vYAxis),
	zAxis(vZAxis),
	wAxis(vWAxis)
{
}

__forceinline Mat43f_Ref RECON_VEC_CALLCONV Mat43f::operator=(Mat43f_In mMatrix)
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

__forceinline Mat43f_Ref RECON_VEC_CALLCONV Mat43f::operator=(Mat43f&& mMatrix)
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

__forceinline Vec3f_Out RECON_VEC_CALLCONV operator*(Vec3f_ConstRef vPos, Mat43f_In mMatrix)
{
	return ::operator*(Vec4f(vPos, 1.0f), mMatrix);
}

__forceinline Vec3f_Ref RECON_VEC_CALLCONV operator*=(Vec3f_Ref vPos, Mat43f_In mMatrix)
{
	return vPos = ::operator*(vPos, mMatrix);
}

inline Vec3f_Out RECON_VEC_CALLCONV operator*(Vec4f_In vVector, Mat43f_In mMatrix)
{
	const f32& fX = vVector.GetXRef();
	const f32& fY = vVector.GetYRef();
	const f32& fZ = vVector.GetZRef();
	const f32& fW = vVector.GetWRef();

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

__forceinline Mat43f_Out RECON_VEC_CALLCONV Mat43f::operator+(Mat43f_In rhs) const
{
	return Mat43f(xAxis + rhs.xAxis, yAxis + rhs.yAxis,  zAxis + rhs.zAxis, wAxis + rhs.wAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat43f::operator+=(Mat43f_In rhs)
{
	xAxis += rhs.xAxis; yAxis += rhs.yAxis; zAxis += rhs.zAxis; wAxis += rhs.wAxis;
}

__forceinline void Mat43f::MakeIdentity3x3()
{
	xAxis = Vec3f(I_X_AXIS);
	yAxis = Vec3f(I_Y_AXIS);
	zAxis = Vec3f(I_Z_AXIS);
}

__forceinline Mat43f_Out RECON_VEC_CALLCONV Mat43f::operator-(Mat43f_In rhs) const
{
	return Mat43f(xAxis - rhs.xAxis, yAxis - rhs.yAxis,  zAxis - rhs.zAxis, wAxis - rhs.wAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat43f::operator-=(Mat43f_In rhs)
{
	xAxis -= rhs.xAxis; yAxis -= rhs.yAxis; zAxis -= rhs.zAxis; wAxis -= rhs.wAxis;
}

__forceinline void RECON_VEC_CALLCONV Mat43f::RotateGlobalX(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44f(I_ROTATION_X, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43f::RotateGlobalY(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44f(I_ROTATION_Y, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43f::RotateGlobalZ(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat43ToMat44(*this) * Mat44f(I_ROTATION_Z, fRadians));
}

__forceinline void RECON_VEC_CALLCONV Mat43f::RotateLocalX(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat44f(I_ROTATION_X, fRadians) * Mat43ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat43f::RotateLocalY(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat44f(I_ROTATION_Y, fRadians) * Mat43ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat43f::RotateLocalZ(const f32& fRadians)
{
	*this = Mat44ToMat43(Mat44f(I_ROTATION_Z, fRadians) * Mat43ToMat44(*this));
}

__forceinline void RECON_VEC_CALLCONV Mat43f::Scale(Vec3f_In vScale)
{
	xAxis = xAxis * vScale.GetX();
	yAxis = yAxis * vScale.GetY();
	zAxis = zAxis * vScale.GetZ();
}

__forceinline void RECON_VEC_CALLCONV Mat43f::SetScale(Vec3f_In vScale)
{
	xAxis = ::Normalize(xAxis) * vScale.GetX();
	yAxis = ::Normalize(yAxis) * vScale.GetY();
	zAxis = ::Normalize(zAxis) * vScale.GetZ();
}

__forceinline Vec3f_Out Mat43f::GetScale() const
{
	Vec3f retVal(Mag(xAxis), Mag(yAxis), Mag(zAxis));
	return retVal;
}

__forceinline void RECON_VEC_CALLCONV Mat43f::Translate(Vec3f vTranslation)
{
	wAxis = wAxis + vTranslation;
}
