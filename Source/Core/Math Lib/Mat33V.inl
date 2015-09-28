
__forceinline Mat33V::Mat33V(const f32& fXx, const f32& fXy, const f32& fXz,
							 const f32& fYx, const f32& fYy, const f32& fYz,
							 const f32& fZx, const f32& fZy, const f32& fZz) :
	xAxis(fXx, fXy, fXz),
	yAxis(fYx, fYy, fYz),
	zAxis(fZx, fZy, fZz)
{
}

__forceinline Mat33V::Mat33V(Mat33V_In mMatrix) : 
	xAxis(mMatrix.xAxis),
	yAxis(mMatrix.yAxis),
	zAxis(mMatrix.zAxis)
{
}

__forceinline Mat33V::Mat33V(Mat33V&& mMatrix) :
	xAxis(std::move(mMatrix.xAxis)),
	yAxis(std::move(mMatrix.yAxis)),
	zAxis(std::move(mMatrix.zAxis))
{
}

__forceinline Mat33V::Mat33V(eIdentityInitializer UNUSED_PARAM(eIdentity)) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS)
{
}

inline Mat33V::Mat33V(eXRotationInitializer UNUSED_PARAM(eXRotation), ScalarV_In vRotationInRadians) :
	xAxis(I_X_AXIS)
{
	f32 fRotInRads = vRotationInRadians.AsFloat();
	f32 fSinAngle = sin(fRotInRads);
	f32 fCosAngle = cos(fRotInRads);
	yAxis = Vec3V(0.0f, fCosAngle, fSinAngle);
	zAxis = Vec3V(0.0f, -fSinAngle, fCosAngle);
}

inline Mat33V::Mat33V(eYRotationInitializer UNUSED_PARAM(eYRotation), ScalarV_In vRotationInRadians) :
	yAxis(I_Y_AXIS)
{
	f32 fRotInRads = vRotationInRadians.AsFloat();
	f32 fSinAngle = sin(fRotInRads);
	f32 fCosAngle = cos(fRotInRads);
	xAxis = Vec3V(fCosAngle, 0.0f, -fSinAngle);
	zAxis = Vec3V(fSinAngle, 0.0f, fCosAngle);
}

inline Mat33V::Mat33V(eZRotationInitializer UNUSED_PARAM(eZRotation), ScalarV_In vRotationInRadians) :
	zAxis(I_Z_AXIS)
{
	f32 fRotInRads = vRotationInRadians.AsFloat();
	f32 fSinAngle = sin(fRotInRads);
	f32 fCosAngle = cos(fRotInRads);
	xAxis = Vec3V(fCosAngle, fSinAngle, 0.0f);
	yAxis = Vec3V(-fSinAngle, fCosAngle, 0.0f);
}

inline Mat33V_Ref RECON_VEC_CALLCONV Mat33V::operator=(Mat33V_In mMatrix)
{
	if(this != &mMatrix)
	{
		xAxis = mMatrix.GetXAxisRef();
		yAxis = mMatrix.GetYAxisRef();
		zAxis = mMatrix.GetZAxisRef();
	}
	return *this;
}

inline Mat33V_Ref RECON_VEC_CALLCONV Mat33V::operator=(Mat33V&& mMatrix)
{
	if(this != &mMatrix)
	{
		xAxis = std::move(mMatrix.GetXAxisRef());
		yAxis = std::move(mMatrix.GetYAxisRef());
		zAxis = std::move(mMatrix.GetZAxisRef());
	}
	return *this;
}

__forceinline Mat33V_Out RECON_VEC_CALLCONV Mat33V::operator*(Mat33V_In mMatrix) const
{
	Mat33V result(*this);
	result *= mMatrix;
	return result;
}

inline void RECON_VEC_CALLCONV Mat33V::operator*=(Mat33V_In mMatrix)
{
#if SSE_AVAILABLE
	const Vector otherX = VectorSet(mMatrix.xAxis.GetXRef(), mMatrix.xAxis.GetYRef(), mMatrix.xAxis.GetZRef(), 0.0f);
	const Vector otherY = VectorSet(mMatrix.yAxis.GetXRef(), mMatrix.yAxis.GetYRef(), mMatrix.yAxis.GetZRef(), 0.0f);
	const Vector otherZ = VectorSet(mMatrix.zAxis.GetXRef(), mMatrix.zAxis.GetYRef(), mMatrix.zAxis.GetZRef(), 0.0f);

	Vector tmp1, tmp2;

	// get the top row
	tmp1 = VectorSet(xAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(xAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(xAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);

	xAxis = Vec3V(tmp2);

	// get 2nd row
	tmp1 = VectorSet(yAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(yAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(yAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);

	yAxis = Vec3V(tmp2);

	// get 3rd row
	tmp1 = VectorSet(zAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(zAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(zAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);

	zAxis = Vec3V(tmp2);
#else
	Vec3V_ConstRef otherX = mMatrix.xAxis;
	Vec3V_ConstRef otherY = mMatrix.yAxis;
	Vec3V_ConstRef otherZ = mMatrix.zAxis;

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

inline Vec3V_Out RECON_VEC_CALLCONV operator*(Vec3V_ConstRef vVector, Mat33V_In mMatrix)
{
#if SSE_AVAILABLE
	const Vector otherX = VectorSet(mMatrix.xAxis.GetXRef(), mMatrix.xAxis.GetYRef(), mMatrix.xAxis.GetZRef(), 0.0f);
	const Vector otherY = VectorSet(mMatrix.yAxis.GetXRef(), mMatrix.yAxis.GetYRef(), mMatrix.yAxis.GetZRef(), 0.0f);
	const Vector otherZ = VectorSet(mMatrix.zAxis.GetXRef(), mMatrix.zAxis.GetYRef(), mMatrix.zAxis.GetZRef(), 0.0f);

	Vector tmp1, tmp2;
	tmp1 = VectorSet(vVector.GetXRef());
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(vVector.GetYRef());
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(vVector.GetZRef());
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);

	return Vec3V(tmp2);
#else
	Vec3V_ConstRef otherX = mMatrix.xAxis;
	Vec3V_ConstRef otherY = mMatrix.yAxis;
	Vec3V_ConstRef otherZ = mMatrix.zAxis;

	return Vec3V(	vVector.x * otherX.GetXRef() + vVector.y * otherY.GetXRef() + vVector.z * otherZ.GetXRef(),
					vVector.x * otherX.GetYRef() + vVector.y * otherY.GetYRef() + vVector.z * otherZ.GetYRef(),
					vVector.x * otherX.GetZRef() + vVector.y * otherY.GetZRef() + vVector.z * otherZ.GetZRef());
#endif
}

__forceinline Vec3V_Ref RECON_VEC_CALLCONV operator*=(Vec3V_Ref vVector, Mat33V_In mMatrix)
{
	vVector = vVector * mMatrix;
	return vVector;
}

__forceinline Mat33V_Out RECON_VEC_CALLCONV Mat33V::operator+(Mat33V_In rhs) const
{
	return Mat33V(xAxis + rhs.xAxis, yAxis + rhs.yAxis, zAxis + rhs.zAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat33V::operator+=(Mat33V_In rhs)
{
	xAxis += rhs.xAxis; yAxis += rhs.yAxis; zAxis += rhs.zAxis;
}

__forceinline Mat33V_Out Mat33V::operator-(Mat33V_In rhs) const
{
	return Mat33V(xAxis - rhs.xAxis, yAxis - rhs.yAxis, zAxis - rhs.zAxis);
}

__forceinline void RECON_VEC_CALLCONV Mat33V::operator-=(Mat33V_In rhs)
{
	xAxis -= rhs.xAxis; yAxis -= rhs.yAxis; zAxis -= rhs.zAxis;
}

inline void RECON_VEC_CALLCONV Mat33V::RotateLocalX(ScalarV_In vRadians)
{
	Mat33V tmp(I_ROTATION_X, vRadians);
	*this = tmp * (*this);
}

inline void RECON_VEC_CALLCONV Mat33V::RotateLocalY(ScalarV_In vRadians)
{
	Mat33V tmp(I_ROTATION_Y, vRadians);
	*this = tmp * (*this);
}

inline void RECON_VEC_CALLCONV Mat33V::RotateLocalZ(ScalarV_In vRadians)
{
	Mat33V tmp(I_ROTATION_Z, vRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat33V::Scale(Vec3V_In vScale)
{
	xAxis *= vScale.GetX();
	yAxis *= vScale.GetY();
	zAxis *= vScale.GetZ();
}

__forceinline void RECON_VEC_CALLCONV Mat33V::SetScale(Vec3V_In vScale)
{
	xAxis = ::Normalize(xAxis) * vScale.GetX();
	yAxis = ::Normalize(yAxis) * vScale.GetY();
	zAxis = ::Normalize(zAxis) * vScale.GetZ();
}

__forceinline Vec3V_Out Mat33V::GetScale() const
{
	return Vec3V(Mag(xAxis), Mag(yAxis), Mag(zAxis));
}