
__forceinline Mat44V::Mat44V(ScalarV_In vXx, ScalarV_In vXy, ScalarV_In vXz, ScalarV_In vXw,
							 ScalarV_In vYx, ScalarV_In vYy, ScalarV_In vYz, ScalarV_In vYw,
							 ScalarV_In vZx, ScalarV_In vZy, ScalarV_In vZz, ScalarV_In vZw,
							 ScalarV_In vWx, ScalarV_In vWy, ScalarV_In vWz, ScalarV_In vWw) :
	xAxis(vXx, vXy, vXz, vXw),
	yAxis(vYx, vYy, vYz, vYw),
	zAxis(vZx, vZy, vZz, vZw),
	wAxis(vWx, vWy, vWz, vWw)
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

inline Mat44V::Mat44V(eXRotationInitializer UNUSED_PARAM(eXRotation), ScalarV_In vRotationInRadians) :
	xAxis(I_X_AXIS),
	wAxis(I_W_AXIS)
{
	Vec2V vSinCos(SinCos(vRotationInRadians));
	yAxis = Vec4V(ScalarV(I_ZERO), vSinCos.GetY(), vSinCos.GetX(), ScalarV(I_ZERO));
	zAxis = Vec4V(ScalarV(I_ZERO), -vSinCos.GetX(), vSinCos.GetY(), ScalarV(I_ZERO));
}

inline Mat44V::Mat44V(eYRotationInitializer UNUSED_PARAM(eYRotation), ScalarV_In vRotationInRadians) :
	yAxis(I_Y_AXIS),
	wAxis(I_W_AXIS)
{
	Vec2V vSinCos(SinCos(vRotationInRadians));
	xAxis = Vec4V(vSinCos.GetY(), ScalarV(I_ZERO), -vSinCos.GetX(), ScalarV(I_ZERO));
	zAxis = Vec4V(vSinCos.GetX(), ScalarV(I_ZERO), vSinCos.GetY(), ScalarV(I_ZERO));
}

inline Mat44V::Mat44V(eZRotationInitializer UNUSED_PARAM(eZRotation), ScalarV_In vRotationInRadians) :
	zAxis(I_Z_AXIS),
	wAxis(I_W_AXIS)
{
	Vec2V vSinCos(SinCos(vRotationInRadians));
	xAxis = Vec4V(vSinCos.GetY(), vSinCos.GetX(), Vec2V(I_ZERO));
	yAxis = Vec4V(-vSinCos.GetX(), vSinCos.GetY(), Vec2V(I_ZERO));
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
__forceinline void RECON_VEC_CALLCONV Mat44V::RotateGlobalX(ScalarV_In vRadians)
{
	Mat44V tmp(I_ROTATION_X, vRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44V::RotateGlobalY(ScalarV_In vRadians)
{
	Mat44V tmp(I_ROTATION_Y, vRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44V::RotateGlobalZ(ScalarV_In vRadians)
{
	Mat44V tmp(I_ROTATION_Z, vRadians);
	*this *= tmp;
}

__forceinline void RECON_VEC_CALLCONV Mat44V::RotateLocalX(ScalarV_In vRadians)
{
	Mat44V tmp(I_ROTATION_X, vRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat44V::RotateLocalY(ScalarV_In vRadians)
{
	Mat44V tmp(I_ROTATION_Y, vRadians);
	*this = tmp * (*this);
}

__forceinline void RECON_VEC_CALLCONV Mat44V::RotateLocalZ(ScalarV_In vRadians)
{
	Mat44V tmp(I_ROTATION_Z, vRadians);
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