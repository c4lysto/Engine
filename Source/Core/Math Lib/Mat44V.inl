
__forceinline Mat44V::Mat44V(const f32& fXx, const f32& fXy, const f32& fXz, const f32& fXw,
							 const f32& fYx, const f32& fYy, const f32& fYz, const f32& fYw,
							 const f32& fZx, const f32& fZy, const f32& fZz, const f32& fZw,
							 const f32& fWx, const f32& fWy, const f32& fWz, const f32& fWw) :
	xAxis(fXx, fXy, fXz, fXw),
	yAxis(fYx, fYy, fYz, fYw),
	zAxis(fZx, fZy, fZz, fZw),
	wAxis(fWx, fWy, fWz, fWw)
{
}

__forceinline Mat44V::Mat44V(Mat44V_In mMatrix) : 
	xAxis(mMatrix.xAxis),
	yAxis(mMatrix.yAxis),
	zAxis(mMatrix.zAxis),
	wAxis(mMatrix.wAxis)
{
}

__forceinline Mat44V::Mat44V(Mat44V&& mMatrix) : 
	xAxis(std::move(mMatrix.xAxis)),
	yAxis(std::move(mMatrix.yAxis)),
	zAxis(std::move(mMatrix.zAxis)),
	wAxis(std::move(mMatrix.wAxis))
{
}

__forceinline Mat44V::Mat44V(Vec4V_In vXAxis,
							 Vec4V_In vYAxis,
							 Vec4V_In vZAxis,
							 Vec4V_In vWAxis) : 
	xAxis(vXAxis),
	yAxis(vYAxis),
	zAxis(vZAxis),
	wAxis(vWAxis)
{
}

inline Mat44V::Mat44V(eIdentityInitializer UNUSED_PARAM(eIdentity)) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
}

inline Mat44V::Mat44V(eXRotationInitializer UNUSED_PARAM(eXRotation), const f32& fRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	yAxis = Vec4V(0.0f, fCosAngle, fSinAngle, 0.0f);
	zAxis = Vec4V(0.0f, -fSinAngle, fCosAngle, 0.0f);
}

inline Mat44V::Mat44V(eYRotationInitializer UNUSED_PARAM(eYRotation), const f32& fRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec4V(fCosAngle, 0.0f, -fSinAngle, 0.0f);
	zAxis = Vec4V(fSinAngle, 0.0f, fCosAngle, 0.0f);
}

inline Mat44V::Mat44V(eZRotationInitializer UNUSED_PARAM(eZRotation), const f32& fRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	f32 fSinAngle = sin(fRotationInRadians);
	f32 fCosAngle = cos(fRotationInRadians);
	xAxis = Vec4V(fCosAngle, fSinAngle, 0.0f, 0.0f);
	yAxis = Vec4V(-fSinAngle, fCosAngle, 0.0f, 0.0f);
}

__forceinline Mat44V::Mat44V(eMatrixPositionInitializer UNUSED_PARAM(eMatrixPos), Vec3V_In vPos) :
	xAxis(I_X_AXIS),
	yAxis(I_Y_AXIS),
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
}

//__forceinline Mat44V::operator XMMATRIX() const
//{
//	return *(XMMATRIX*)this;
//}
//
//__forceinline Mat44V::operator XMMATRIX*() const
//{
//	return (XMMATRIX*)this;
//}

__forceinline Mat44V_ConstRef RECON_VEC_CALLCONV Mat44V::operator=(Mat44V_In mMatrix)
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

__forceinline Mat44V_ConstRef RECON_VEC_CALLCONV Mat44V::operator=(Mat44V&& mMatrix)
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

inline Mat44V RECON_VEC_CALLCONV Mat44V::operator*(Mat44V_In mMatrix) const
{
	Mat44V result;

	Vector tmp1, tmp2;

	// get the top row
	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(row1);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(row1);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(row1);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(row1);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	result.row1 = tmp2;

	// get 2nd row
	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(row2);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(row2);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(row2);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(row2);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	result.row2 = tmp2;

	// get 3rd row
	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(row3);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(row3);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(row3);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(row3);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	result.row3 = tmp2;

	// get 4th row
	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(row4);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(row4);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(row4);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(row4);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	result.row4 = tmp2;

	return result;
}

inline void RECON_VEC_CALLCONV Mat44V::operator*=(Mat44V_In mMatrix)
{
	Vector tmp1, tmp2;

	// get the top row
	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(row1);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(row1);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(row1);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(row1);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	row1 = tmp2;

	// get 2nd row
	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(row2);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(row2);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(row2);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(row2);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	row2 = tmp2;

	// get 3rd row
	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(row3);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(row3);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(row3);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(row3);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	row3 = tmp2;

	// get 4th row
	tmp1 = VectorPermute<VecElem::X, VecElem::X, VecElem::X, VecElem::X>(row4);
	tmp2 = VectorMultiply(mMatrix.row1, tmp1);
	tmp1 = VectorPermute<VecElem::Y, VecElem::Y, VecElem::Y, VecElem::Y>(row4);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row2, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::Z, VecElem::Z, VecElem::Z, VecElem::Z>(row4);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row3, tmp1), tmp2);
	tmp1 = VectorPermute<VecElem::W, VecElem::W, VecElem::W, VecElem::W>(row4);
	tmp2 = VectorAdd(VectorMultiply(mMatrix.row4, tmp1), tmp2);

	row4 = tmp2;
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV Mat44V::operator+(Mat44V_In rhs) const
{
	return Mat44V(xAxis + rhs.GetXAxisRef(), yAxis + rhs.GetYAxisRef(), zAxis + rhs.GetZAxisRef(), wAxis + rhs.GetWAxisRef());
}

__forceinline void RECON_VEC_CALLCONV Mat44V::operator+=(Mat44V_In rhs)
{
	xAxis += rhs.GetXAxisRef(); yAxis += rhs.GetYAxisRef(); zAxis += rhs.GetZAxisRef(); wAxis += rhs.GetWAxisRef();
}

__forceinline Mat44V_Out RECON_VEC_CALLCONV Mat44V::operator-(Mat44V_In rhs) const
{
	return Mat44V(xAxis - rhs.GetXAxisRef(), yAxis - rhs.GetYAxisRef(), zAxis - rhs.GetZAxisRef(), wAxis - rhs.GetWAxisRef());
}

__forceinline void RECON_VEC_CALLCONV Mat44V::operator-=(Mat44V_In rhs)
{
	xAxis -= rhs.GetXAxisRef(); yAxis -= rhs.GetYAxisRef(); zAxis -= rhs.GetZAxisRef(); wAxis -= rhs.GetWAxisRef();
}

// actually faster than DirectX Version :)
__forceinline void RECON_VEC_CALLCONV Mat44V::Rotate_GlobalX(const f32& fRadians)
{
	Mat44V tmp(I_ROTATION_X, fRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44V::Rotate_GlobalY(const f32& fRadians)
{
	Mat44V tmp(I_ROTATION_Y, fRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44V::Rotate_GlobalZ(const f32& fRadians)
{
	Mat44V tmp(I_ROTATION_Z, fRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44V::Rotate_LocalX(const f32& fRadians)
{
	Mat44V tmp(I_ROTATION_X, fRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat44V::Rotate_LocalY(const f32& fRadians)
{
	Mat44V tmp(I_ROTATION_Y, fRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat44V::Rotate_LocalZ(const f32& fRadians)
{
	Mat44V tmp(I_ROTATION_Z, fRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat44V::Scale(Vec3V_In vScale)
{
	xAxis.SetXYZ(xAxis.GetXYZ() * vScale.GetX());
	yAxis.SetXYZ(yAxis.GetXYZ() * vScale.GetY());
	zAxis.SetXYZ(zAxis.GetXYZ() * vScale.GetZ());
}

__forceinline void RECON_VEC_CALLCONV Mat44V::SetScale(Vec3V_In vScale)
{
	xAxis.SetXYZ(::Normalize(xAxis.GetXYZ()) * vScale.GetX());
	yAxis.SetXYZ(::Normalize(yAxis.GetXYZ()) * vScale.GetY());
	zAxis.SetXYZ(::Normalize(zAxis.GetXYZ()) * vScale.GetZ());
}

__forceinline Vec3V_Out Mat44V::GetScale() const
{
	return Vec3V(Mag(xAxis), Mag(yAxis), Mag(zAxis));
}

__forceinline void Mat44V::Translate(Vec3V_In vTranslation)
{
	wAxis.SetXYZ(wAxis.GetXYZ() + vTranslation);
}

__forceinline void Mat44V::Normalize()
{
	xAxis = ::Normalize(xAxis);
	yAxis = ::Normalize(yAxis);
	zAxis = ::Normalize(zAxis);
}