
__forceinline Mat44f::Mat44f(const f32& fXx, const f32& fXy, const f32& fXz, const f32& fXw,
							 const f32& fYx, const f32& fYy, const f32& fYz, const f32& fYw,
							 const f32& fZx, const f32& fZy, const f32& fZz, const f32& fZw,
							 const f32& fWx, const f32& fWy, const f32& fWz, const f32& fWw) :
	xAxis(fXx, fXy, fXz, fXw),
	yAxis(fYx, fYy, fYz, fYw),
	zAxis(fZx, fZy, fZz, fZw),
	wAxis(fWx, fWy, fWz, fWw)
{
}

__forceinline Mat44f::Mat44f(Mat44f_In mMatrix) : 
	xAxis(mMatrix.xAxis),
	yAxis(mMatrix.yAxis),
	zAxis(mMatrix.zAxis),
	wAxis(mMatrix.wAxis)
{
}

__forceinline Mat44f::Mat44f(Mat44f&& mMatrix) :
	xAxis(std::move(mMatrix.xAxis)),
	yAxis(std::move(mMatrix.yAxis)),
	zAxis(std::move(mMatrix.zAxis)),
	wAxis(std::move(mMatrix.wAxis))
{
}

__forceinline Mat44f::Mat44f(eIdentityInitializer UNUSED_PARAM(eIdentity)) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
}

inline Mat44f::Mat44f(eXRotationInitializer UNUSED_PARAM(eXRotation), const f32& fRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	yAxis = Vec4f(0.0f, fCosAngle, fSinAngle, 0.0f);
	zAxis = Vec4f(0.0f, -fSinAngle, fCosAngle, 0.0f);
}

inline Mat44f::Mat44f(eYRotationInitializer UNUSED_PARAM(eYRotation), const f32& fRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec4f(fCosAngle, 0.0f, -fSinAngle, 0.0f);
	zAxis = Vec4f(fSinAngle, 0.0f, fCosAngle, 0.0f);
}

inline Mat44f::Mat44f(eZRotationInitializer UNUSED_PARAM(eZRotation), const f32& fRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec4f(fCosAngle, fSinAngle, 0.0f, 0.0f);
	yAxis = Vec4f(-fSinAngle, fCosAngle, 0.0f, 0.0f);
}

__forceinline Mat44f::Mat44f(eMatrixPositionInitializer UNUSED_PARAM(eMatrixPos), Vec3f_In vPos) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(vPos, 1.0f)
{

}

__forceinline Mat44f::Mat44f(Vec4f_In vXAxis,
						     Vec4f_In vYAxis,
						     Vec4f_In vZAxis,
						     Vec4f_In vWAxis) :
	xAxis(vXAxis),
	yAxis(vYAxis),
	zAxis(vZAxis),
	wAxis(vWAxis)
{
}

__forceinline Mat44f_Ref RECON_VEC_CALLCONV Mat44f::operator=(Mat44f_In mMatrix)
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

__forceinline Mat44f_Ref RECON_VEC_CALLCONV Mat44f::operator=(Mat44f&& mMatrix)
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

inline Mat44f_Out RECON_VEC_CALLCONV Mat44f::operator*(Mat44f_In mMatrix) const
{
	Mat44f result;

#if SSE_AVAILABLE
	const Vector otherX = VectorLoadU(mMatrix.xAxis.GetVector());
	const Vector otherY = VectorLoadU(mMatrix.yAxis.GetVector());
	const Vector otherZ = VectorLoadU(mMatrix.zAxis.GetVector());
	const Vector otherW = VectorLoadU(mMatrix.wAxis.GetVector());

	Vector tmp1, tmp2;

	// get the top row
	tmp1 = VectorSet(xAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(xAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(xAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);
	tmp1 = VectorSet(xAxis.w);
	tmp2 = VectorAdd(VectorMultiply(otherW, tmp1), tmp2);

	VectorStoreU(tmp2, result.xAxis.GetVector());

	// get 2nd row
	tmp1 = VectorSet(yAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(yAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(yAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);
	tmp1 = VectorSet(yAxis.w);
	tmp2 = VectorAdd(VectorMultiply(otherW, tmp1), tmp2);

	VectorStoreU(tmp2, result.yAxis.GetVector());

	// get 3rd row
	tmp1 = VectorSet(zAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(zAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(zAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);
	tmp1 = VectorSet(zAxis.w);
	tmp2 = VectorAdd(VectorMultiply(otherW, tmp1), tmp2);

	VectorStoreU(tmp2, result.zAxis.GetVector());

	// get bottom row
	tmp1 = VectorSet(wAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(wAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(wAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);
	tmp1 = VectorSet(wAxis.w);
	tmp2 = VectorAdd(VectorMultiply(otherW, tmp1), tmp2);

	VectorStoreU(tmp2, result.wAxis.GetVector());
#else
	const Vec4f& otherX = mMatrix.xAxis;
	const Vec4f& otherY = mMatrix.yAxis;
	const Vec4f& otherZ = mMatrix.zAxis;
	const Vec4f& otherW = mMatrix.wAxis;

	result.Xx = xAxis.x * otherX.x + xAxis.y * mMatrix.Yx + xAxis.z * mMatrix.Zx + xAxis.w * mMatrix.Wx;
	result.Xy = xAxis.x * otherX.y + xAxis.y * mMatrix.Yy + xAxis.z * mMatrix.Zy + xAxis.w * mMatrix.Wy;
	result.Xz = xAxis.x * otherX.z + xAxis.y * mMatrix.Yz + xAxis.z * mMatrix.Zz + xAxis.w * mMatrix.Wz;
	result.Xw = xAxis.x * otherX.w + xAxis.y * mMatrix.Yw + xAxis.z * mMatrix.Zw + xAxis.w * mMatrix.Ww;
	
	result.Yx = yAxis.x * otherX.x + yAxis.y * mMatrix.Yx + yAxis.z * mMatrix.Zx + yAxis.w * mMatrix.Wx;
	result.Yy = yAxis.x * otherX.y + yAxis.y * mMatrix.Yy + yAxis.z * mMatrix.Zy + yAxis.w * mMatrix.Wy;
	result.Yz = yAxis.x * otherX.z + yAxis.y * mMatrix.Yz + yAxis.z * mMatrix.Zz + yAxis.w * mMatrix.Wz;
	result.Yw = yAxis.x * otherX.w + yAxis.y * mMatrix.Yw + yAxis.z * mMatrix.Zw + yAxis.w * mMatrix.Ww;
	
	result.Zx = zAxis.x * otherX.x + zAxis.y * mMatrix.Yx + zAxis.z * mMatrix.Zx + zAxis.w * mMatrix.Wx;
	result.Zy = zAxis.x * otherX.y + zAxis.y * mMatrix.Yy + zAxis.z * mMatrix.Zy + zAxis.w * mMatrix.Wy;
	result.Zz = zAxis.x * otherX.z + zAxis.y * mMatrix.Yz + zAxis.z * mMatrix.Zz + zAxis.w * mMatrix.Wz;
	result.Zw = zAxis.x * otherX.w + zAxis.y * mMatrix.Yw + zAxis.z * mMatrix.Zw + zAxis.w * mMatrix.Ww;
	
	result.Wx = wAxis.x * otherX.x + wAxis.y * mMatrix.Yx + wAxis.z * mMatrix.Zx + wAxis.w * mMatrix.Wx;
	result.Wy = wAxis.x * otherX.y + wAxis.y * mMatrix.Yy + wAxis.z * mMatrix.Zy + wAxis.w * mMatrix.Wy;
	result.Wz = wAxis.x * otherX.z + wAxis.y * mMatrix.Yz + wAxis.z * mMatrix.Zz + wAxis.w * mMatrix.Wz;
	result.Ww = wAxis.x * otherX.w + wAxis.y * mMatrix.Yw + wAxis.z * mMatrix.Zw + wAxis.w * mMatrix.Ww;
#endif

	return result;
}

inline void RECON_VEC_CALLCONV Mat44f::operator*=(Mat44f_In mMatrix)
{
#if SSE_AVAILABLE
	const Vector otherX = VectorLoadU(mMatrix.xAxis.GetVector());
	const Vector otherY = VectorLoadU(mMatrix.yAxis.GetVector());
	const Vector otherZ = VectorLoadU(mMatrix.zAxis.GetVector());
	const Vector otherW = VectorLoadU(mMatrix.wAxis.GetVector());

	Vector tmp1, tmp2;

	// get the top row
	tmp1 = VectorSet(xAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(xAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(xAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);
	tmp1 = VectorSet(xAxis.w);
	tmp2 = VectorAdd(VectorMultiply(otherW, tmp1), tmp2);

	VectorStoreU(tmp2, xAxis.GetVector());

	// get 2nd row
	tmp1 = VectorSet(yAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(yAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(yAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);
	tmp1 = VectorSet(yAxis.w);
	tmp2 = VectorAdd(VectorMultiply(otherW, tmp1), tmp2);

	VectorStoreU(tmp2, yAxis.GetVector());

	// get 3rd row
	tmp1 = VectorSet(zAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(zAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(zAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);
	tmp1 = VectorSet(zAxis.w);
	tmp2 = VectorAdd(VectorMultiply(otherW, tmp1), tmp2);

	VectorStoreU(tmp2, zAxis.GetVector());

	// get bottom row
	tmp1 = VectorSet(wAxis.x);
	tmp2 = VectorMultiply(otherX, tmp1);
	tmp1 = VectorSet(wAxis.y);
	tmp2 = VectorAdd(VectorMultiply(otherY, tmp1), tmp2);
	tmp1 = VectorSet(wAxis.z);
	tmp2 = VectorAdd(VectorMultiply(otherZ, tmp1), tmp2);
	tmp1 = VectorSet(wAxis.w);
	tmp2 = VectorAdd(VectorMultiply(otherW, tmp1), tmp2);

	VectorStoreU(tmp2, wAxis.GetVector());
#else
	const Vec4f& otherX = mMatrix.xAxis;
	const Vec4f& otherY = mMatrix.yAxis;
	const Vec4f& otherZ = mMatrix.zAxis;
	const Vec4f& otherW = mMatrix.wAxis;

	Vec4f currAxis = xAxis;

	xAxis.x = currAxis.x * otherX.x + currAxis.y * otherY.x + currAxis.z * otherZ.x + currAxis.w * otherW.x;
	xAxis.y = currAxis.x * otherX.y + currAxis.y * otherY.y + currAxis.z * otherZ.y + currAxis.w * otherW.y;
	xAxis.z = currAxis.x * otherX.z + currAxis.y * otherY.z + currAxis.z * otherZ.z + currAxis.w * otherW.z;
	xAxis.w = currAxis.x * otherX.w + currAxis.y * otherY.w + currAxis.z * otherZ.w + currAxis.w * otherW.w;

	currAxis = yAxis;
	yAxis.x = currAxis.x * otherX.x + currAxis.y * otherY.x + currAxis.z * otherZ.x + currAxis.w * otherW.x;
	yAxis.y = currAxis.x * otherX.y + currAxis.y * otherY.y + currAxis.z * otherZ.y + currAxis.w * otherW.y;
	yAxis.z = currAxis.x * otherX.z + currAxis.y * otherY.z + currAxis.z * otherZ.z + currAxis.w * otherW.z;
	yAxis.w = currAxis.x * otherX.w + currAxis.y * otherY.w + currAxis.z * otherZ.w + currAxis.w * otherW.w;

	currAxis = zAxis;
	zAxis.x = currAxis.x * otherX.x + currAxis.y * otherY.x + currAxis.z * otherZ.x + currAxis.w * otherW.x;
	zAxis.y = currAxis.x * otherX.y + currAxis.y * otherY.y + currAxis.z * otherZ.y + currAxis.w * otherW.y;
	zAxis.z = currAxis.x * otherX.z + currAxis.y * otherY.z + currAxis.z * otherZ.z + currAxis.w * otherW.z;
	zAxis.w = currAxis.x * otherX.w + currAxis.y * otherY.w + currAxis.z * otherZ.w + currAxis.w * otherW.w;

	currAxis = wAxis;
	wAxis.x = currAxis.x * otherX.x + currAxis.y * otherY.x + currAxis.z * otherZ.x + currAxis.w * otherW.x;
	wAxis.y = currAxis.x * otherX.y + currAxis.y * otherY.y + currAxis.z * otherZ.y + currAxis.w * otherW.y;
	wAxis.z = currAxis.x * otherX.z + currAxis.y * otherY.z + currAxis.z * otherZ.z + currAxis.w * otherW.z;
	wAxis.w = currAxis.x * otherX.w + currAxis.y * otherY.w + currAxis.z * otherZ.w + currAxis.w * otherW.w;
#endif
}

inline Vec4f_Out RECON_VEC_CALLCONV operator*(Vec4f_In vVector, Mat44f_In mMatrix)
{
	f32 fX = vVector.GetX();
	f32 fY = vVector.GetY();
	f32 fZ = vVector.GetZ();
	f32 fW = vVector.GetW();

#if SSE_AVAILABLE
	Vector tmp1, tmp2;

	// get the top row
	tmp1 = VectorSet(fX);
	tmp2 = VectorMultiply(VectorLoadU((f32*)&mMatrix.xAxis), tmp1);
	tmp1 = VectorSet(fY);
	tmp2 = VectorAdd(VectorMultiply(VectorLoadU((f32*)&mMatrix.yAxis), tmp1), tmp2);
	tmp1 = VectorSet(fZ);
	tmp2 = VectorAdd(VectorMultiply(VectorLoadU((f32*)&mMatrix.zAxis), tmp1), tmp2);
	tmp1 = VectorSet(fW);
	tmp2 = VectorAdd(VectorMultiply(VectorLoadU((f32*)&mMatrix.wAxis), tmp1), tmp2);

	return Vec4f(tmp2);
#else
	return Vec4f(fX * mMatrix.xAxis.x + fY * mMatrix.yAxis.x + fZ * mMatrix.zAxis.x + fW * mMatrix.wAxis.x,
				 fX * mMatrix.xAxis.y + fY * mMatrix.yAxis.y + fZ * mMatrix.zAxis.y + fW * mMatrix.wAxis.y,
				 fX * mMatrix.xAxis.z + fY * mMatrix.yAxis.z + fZ * mMatrix.zAxis.z + fW * mMatrix.wAxis.z,
				 fX * mMatrix.xAxis.w + fY * mMatrix.yAxis.w + fZ * mMatrix.zAxis.w + fW * mMatrix.wAxis.w);
#endif
}

__forceinline Vec4f_Ref RECON_VEC_CALLCONV operator*=(Vec4f_Ref vVector, Mat44f_In mMatrix)
{
	return vVector = vVector * mMatrix;
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV Mat44f::operator+(Mat44f_In rhs) const
{
	return Mat44f(xAxis + rhs.GetXAxisRef(), yAxis + rhs.GetYAxisRef(),  zAxis + rhs.GetZAxisRef(), wAxis + rhs.GetWAxisRef());
}

__forceinline void RECON_VEC_CALLCONV Mat44f::operator+=(Mat44f_In rhs)
{
	xAxis += rhs.GetXAxisRef(); yAxis += rhs.GetYAxisRef(); zAxis += rhs.GetZAxisRef(); wAxis += rhs.GetWAxisRef();
}

__forceinline void Mat44f::MakeIdentity3x3()
{
	xAxis.SetXYZ(Vec3f(I_X_AXIS));
	yAxis.SetXYZ(Vec3f(I_Y_AXIS));
	zAxis.SetXYZ(Vec3f(I_Z_AXIS));
}

__forceinline Mat44f_Out RECON_VEC_CALLCONV Mat44f::operator-(Mat44f_In rhs) const
{
	return Mat44f(xAxis - rhs.GetXAxisRef(), yAxis - rhs.GetYAxisRef(),  zAxis - rhs.GetZAxisRef(), wAxis - rhs.GetWAxisRef());
}

__forceinline void RECON_VEC_CALLCONV Mat44f::operator-=(Mat44f_In rhs)
{
	xAxis -= rhs.GetXAxisRef(); yAxis -= rhs.GetYAxisRef(); zAxis -= rhs.GetZAxisRef(); wAxis -= rhs.GetWAxisRef();
}

// actually faster than DirectX Version :)
__forceinline void RECON_VEC_CALLCONV Mat44f::Rotate_GlobalX(const f32& fRadians)
{
	Mat44f tmp(I_ROTATION_X, fRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44f::Rotate_GlobalY(const f32& fRadians)
{
	Mat44f tmp(I_ROTATION_Y, fRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44f::Rotate_GlobalZ(const f32& fRadians)
{
	Mat44f tmp(I_ROTATION_Z, fRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44f::Rotate_LocalX(const f32& fRadians)
{
	Mat44f tmp(I_ROTATION_X, fRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat44f::Rotate_LocalY(const f32& fRadians)
{
	Mat44f tmp(I_ROTATION_Y, fRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat44f::Rotate_LocalZ(const f32& fRadians)
{
	Mat44f tmp(I_ROTATION_Z, fRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat44f::Scale(const Vec3f& vScale)
{
	xAxis.SetXYZ(xAxis.GetXYZ() * vScale.GetX());
	yAxis.SetXYZ(yAxis.GetXYZ() * vScale.GetY());
	zAxis.SetXYZ(zAxis.GetXYZ() * vScale.GetZ());
}

__forceinline void RECON_VEC_CALLCONV Mat44f::SetScale(const Vec3f& vScale)
{
	xAxis.SetXYZ(::Normalize(xAxis.GetXYZ()) * vScale.GetX());
	yAxis.SetXYZ(::Normalize(yAxis.GetXYZ()) * vScale.GetY());
	zAxis.SetXYZ(::Normalize(zAxis.GetXYZ()) * vScale.GetZ());
}

__forceinline Vec3f_Out Mat44f::GetScale() const
{
	Vec3f retVal(Mag(xAxis.GetXYZ()), Mag(yAxis.GetXYZ()), Mag(zAxis.GetXYZ()));
	return retVal;
}

__forceinline void RECON_VEC_CALLCONV Mat44f::Translate(Vec3f vTranslation)
{
	wAxis.SetXYZ(wAxis.GetXYZ() + vTranslation);
}

__forceinline void Mat44f::Normalize()
{
	xAxis.SetXYZ(::Normalize(xAxis.GetXYZ()));
	yAxis.SetXYZ(::Normalize(yAxis.GetXYZ()));
	zAxis.SetXYZ(::Normalize(zAxis.GetXYZ()));
}
