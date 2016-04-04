
__forceinline Mat33f::Mat33f(const f32& fXx, const f32& fXy, const f32& fXz,
							 const f32& fYx, const f32& fYy, const f32& fYz,
							 const f32& fZx, const f32& fZy, const f32& fZz) :
	xAxis(fXx, fXy, fXz),
	yAxis(fYx, fYy, fYz),
	zAxis(fZx, fZy, fZz)
{
}

__forceinline Mat33f::Mat33f(Mat33f_In mMatrix) : 
	xAxis(mMatrix.xAxis),
	yAxis(mMatrix.yAxis),
	zAxis(mMatrix.zAxis)
{
}

__forceinline Mat33f::Mat33f(Mat33f&& mMatrix) :
	xAxis(std::move(mMatrix.xAxis)),
	yAxis(std::move(mMatrix.yAxis)),
	zAxis(std::move(mMatrix.zAxis))
{
}

__forceinline Mat33f::Mat33f(eIdentityInitializer UNUSED_PARAM(eIdentity)) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS)
{
}

inline Mat33f::Mat33f(eXRotationInitializer UNUSED_PARAM(eXRotation), const f32& fRotationInRadians) :
	xAxis(I_X_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	yAxis = Vec3f(0.0f, fCosAngle, fSinAngle);
	zAxis = Vec3f(0.0f, -fSinAngle, fCosAngle);
}

inline Mat33f::Mat33f(eYRotationInitializer UNUSED_PARAM(eYRotation), const f32& fRotationInRadians) :
	yAxis(I_Y_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3f(fCosAngle, 0.0f, -fSinAngle);
	zAxis = Vec3f(fSinAngle, 0.0f, fCosAngle);
}

inline Mat33f::Mat33f(eZRotationInitializer UNUSED_PARAM(eZRotation), const f32& fRotationInRadians) :
	zAxis(I_Z_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec3f(fCosAngle, fSinAngle, 0.0f);
	yAxis = Vec3f(-fSinAngle, fCosAngle, 0.0f);
}

inline Mat33f_Ref RECON_VEC_CALLCONV Mat33f::operator=(Mat33f_In mMatrix)
{
	if(this != &mMatrix)
	{
		xAxis = mMatrix.GetXAxisRef();
		yAxis = mMatrix.GetYAxisRef();
		zAxis = mMatrix.GetZAxisRef();
	}
	return *this;
}

inline Mat33f_Ref RECON_VEC_CALLCONV Mat33f::operator=(Mat33f&& mMatrix)
{
	if(this != &mMatrix)
	{
		xAxis = std::move(mMatrix.GetXAxisRef());
		yAxis = std::move(mMatrix.GetYAxisRef());
		zAxis = std::move(mMatrix.GetZAxisRef());
	}
	return *this;
}

__forceinline Mat33f_Out RECON_VEC_CALLCONV Mat33f::operator*(Mat33f_In mMatrix) const
{
	Mat33f result(*this);
	result *= mMatrix;
	return result;
}

inline void RECON_VEC_CALLCONV Mat33f::operator*=(Mat33f_In mMatrix)
{
#if RECON_SSE_VERSION
	const Vector128 otherX = VectorSet(mMatrix.xAxis.GetXRef(), mMatrix.xAxis.GetYRef(), mMatrix.xAxis.GetZRef(), 0.0f);
	const Vector128 otherY = VectorSet(mMatrix.yAxis.GetXRef(), mMatrix.yAxis.GetYRef(), mMatrix.yAxis.GetZRef(), 0.0f);
	const Vector128 otherZ = VectorSet(mMatrix.zAxis.GetXRef(), mMatrix.zAxis.GetYRef(), mMatrix.zAxis.GetZRef(), 0.0f);

	Vector128 tmp1, tmp2;

	// get the top row
	tmp1 = VectorSet(xAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(xAxis.y);
	tmp2 = VectorMad(otherY, tmp1, tmp2);
	tmp1 = VectorSet(xAxis.z);
	tmp2 = VectorMad(otherZ, tmp1, tmp2);

	xAxis = Vec3f(tmp2);

	// get 2nd row
	tmp1 = VectorSet(yAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(yAxis.y);
	tmp2 = VectorMad(otherY, tmp1, tmp2);
	tmp1 = VectorSet(yAxis.z);
	tmp2 = VectorMad(otherZ, tmp1, tmp2);

	yAxis = Vec3f(tmp2);

	// get 3rd row
	tmp1 = VectorSet(zAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(zAxis.y);
	tmp2 = VectorMad(otherY, tmp1, tmp2);
	tmp1 = VectorSet(zAxis.z);
	tmp2 = VectorMad(otherZ, tmp1, tmp2);

	zAxis = Vec3f(tmp2);
#else
	Vec3f_ConstRef otherX = mMatrix.xAxis;
	Vec3f_ConstRef otherY = mMatrix.yAxis;
	Vec3f_ConstRef otherZ = mMatrix.zAxis;

	Xx = xAxis.x * otherX.x + xAxis.y * mMatrix.Yx + xAxis.z * mMatrix.Zx;
	Xy = xAxis.x * otherX.y + xAxis.y * mMatrix.Yy + xAxis.z * mMatrix.Zy;
	Xz = xAxis.x * otherX.z + xAxis.y * mMatrix.Yz + xAxis.z * mMatrix.Zz;

	Yx = yAxis.x * otherX.x + yAxis.y * mMatrix.Yx + yAxis.z * mMatrix.Zx;
	Yy = yAxis.x * otherX.y + yAxis.y * mMatrix.Yy + yAxis.z * mMatrix.Zy;
	Yz = yAxis.x * otherX.z + yAxis.y * mMatrix.Yz + yAxis.z * mMatrix.Zz;

	Zx = zAxis.x * otherX.x + zAxis.y * mMatrix.Yx + zAxis.z * mMatrix.Zx;
	Zy = zAxis.x * otherX.y + zAxis.y * mMatrix.Yy + zAxis.z * mMatrix.Zy;
	Zz = zAxis.x * otherX.z + zAxis.y * mMatrix.Yz + zAxis.z * mMatrix.Zz;
#endif
}

inline Vec3f_Out RECON_VEC_CALLCONV operator*(Vec3f_ConstRef vVector, Mat33f_In mMatrix)
{
#if RECON_SSE_VERSION
	const Vector128 otherX = VectorSet(mMatrix.xAxis.GetXRef(), mMatrix.xAxis.GetYRef(), mMatrix.xAxis.GetZRef(), 0.0f);
	const Vector128 otherY = VectorSet(mMatrix.yAxis.GetXRef(), mMatrix.yAxis.GetYRef(), mMatrix.yAxis.GetZRef(), 0.0f);
	const Vector128 otherZ = VectorSet(mMatrix.zAxis.GetXRef(), mMatrix.zAxis.GetYRef(), mMatrix.zAxis.GetZRef(), 0.0f);

	Vector128 tmp1, tmp2;
	tmp1 = VectorSet(vVector.GetXRef());
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(vVector.GetYRef());
	tmp2 = VectorMad(otherY, tmp1, tmp2);
	tmp1 = VectorSet(vVector.GetZRef());
	tmp2 = VectorMad(otherZ, tmp1, tmp2);

	return Vec3f(tmp2);
#else
	Vec3f_ConstRef otherX = mMatrix.xAxis;
	Vec3f_ConstRef otherY = mMatrix.yAxis;
	Vec3f_ConstRef otherZ = mMatrix.zAxis;

	return Vec3f(	vVector.x * otherX.GetXRef() + vVector.y * otherY.GetXRef() + vVector.z * otherZ.GetXRef(),
					vVector.x * otherX.GetYRef() + vVector.y * otherY.GetYRef() + vVector.z * otherZ.GetYRef(),
					vVector.x * otherX.GetZRef() + vVector.y * otherY.GetZRef() + vVector.z * otherZ.GetZRef());
#endif // RECON_SSE_VERSION
}

__forceinline Vec3f_Ref RECON_VEC_CALLCONV operator*=(Vec3f_Ref vVector, Mat33f_In mMatrix)
{
	return vVector = vVector * mMatrix;
}

__forceinline Mat33f_Out RECON_VEC_CALLCONV Mat33f::operator+(Mat33f_In rhs) const
{
	return Mat33f(xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat33f::operator+=(Mat33f_In rhs)
{
	xAxis += rhs.xAxis; yAxis += rhs.yAxis; zAxis += rhs.zAxis;
}

__forceinline Mat33f_Out RECON_VEC_CALLCONV Mat33f::operator-(Mat33f_In rhs) const
{
	return Mat33f(xAxis - rhs.xAxis, yAxis - rhs.yAxis, zAxis - rhs.zAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat33f::operator-=(Mat33f_In rhs)
{
	xAxis -= rhs.xAxis; yAxis -= rhs.yAxis; zAxis -= rhs.zAxis;
}

inline void RECON_VEC_CALLCONV Mat33f::RotateLocalX(const f32& fRadians)
{
	Mat33f tmp(I_ROTATION_X, fRadians);
	*this = tmp * (*this);
}

inline void RECON_VEC_CALLCONV Mat33f::RotateLocalY(const f32& fRadians)
{
	Mat33f tmp(I_ROTATION_Y, fRadians);
	*this = tmp * (*this);
}

inline void RECON_VEC_CALLCONV Mat33f::RotateLocalZ(const f32& fRadians)
{
	Mat33f tmp(I_ROTATION_Z, fRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat33f::Scale(Vec3f_In vScale)
{
	xAxis *= vScale.GetXRef();
	yAxis *= vScale.GetYRef();
	zAxis *= vScale.GetZRef();
}

__forceinline void RECON_VEC_CALLCONV Mat33f::SetScale(Vec3f_In vScale)
{
	xAxis = ::Normalize(xAxis) * vScale.GetXRef();
	yAxis = ::Normalize(yAxis) * vScale.GetYRef();
	zAxis = ::Normalize(zAxis) * vScale.GetZRef();
}

__forceinline Vec3f_Out Mat33f::GetScale() const
{
	return Vec3f(Mag(xAxis), Mag(yAxis), Mag(zAxis));
}