
__forceinline Vec3f::Vec3f(const f32& fVal) : x(fVal), y(fVal), z(fVal)
{

}

__forceinline Vec3f::Vec3f(const f32& fX, const f32& fY, const f32& fZ) : x(fX), y(fY), z(fZ)
{

}

__forceinline Vec3f::Vec3f(const f32& fX, Vec2f_In vYZ) : x(fX), y(vYZ.GetXRef()), z(vYZ.GetYRef())
{

}

__forceinline Vec3f::Vec3f(Vec2f_In vXY, const f32& fZ) : x(vXY.GetXRef()), y(vXY.GetYRef()), z(fZ)
{

}

__forceinline Vec3f::Vec3f(Vec3f_In vVector) : x(vVector.x), y(vVector.y), z(vVector.z)
{

}

__forceinline Vec3f::Vec3f(Vec3f&& vVector)
{
	x = std::move(vVector.x);
	y = std::move(vVector.y);
	z = std::move(vVector.z);
}

#if SSE_AVAILABLE
__forceinline Vec3f::Vec3f(Vector_In vVector)
{
	x = VectorExtractFloat<VecElem::X>(vVector);
	y = VectorExtractFloat<VecElem::Y>(vVector);
	z = VectorExtractFloat<VecElem::Z>(vVector);
}

#if !RECON_OS_64BIT
__forceinline Vec3f::Vec3f(Vector&& vVector)
{
	x = VectorExtractFloat<VecElem::X>(vVector);
	y = VectorExtractFloat<VecElem::Y>(vVector);
	z = VectorExtractFloat<VecElem::Z>(vVector);
}
#endif // !RECON_OS_64BIT
#endif // SSE_AVAILABLE

__forceinline Vec3f_Out Vec3f::operator-() const
{
	return Vec3fInt(iX ^ 0x80000000, iY ^ 0x80000000, iZ ^ 0x80000000);
}

__forceinline Vec3f_Ref RECON_VEC_CALLCONV Vec3f::operator=(Vec3f_In vVector)
{
	if(this != &vVector)
	{
		x = vVector.x;
		y = vVector.y;
		z = vVector.z;
	}
	return *this;
}

__forceinline Vec3f_Ref RECON_VEC_CALLCONV Vec3f::operator=(Vec3f&& vVector)
{
	if(this != &vVector)
	{
		x = std::move(vVector.x);
		y = std::move(vVector.y);
		z = std::move(vVector.z);
	}
	return *this;
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator*=(const f32& fScalar)
{
	x *= fScalar; y *= fScalar; z *= fScalar;
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator*=(Vec3f_In vScale)
{
	x *= vScale.x; y *= vScale.y; z *= vScale.z;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator/(const f32& fScalar) const
{
	f32 fInvScalar = 1 / fScalar;
	return Vec3f(x * fInvScalar, y * fInvScalar, z * fInvScalar);
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator/(Vec3f_In vScale) const
{
	return Vec3f(x / vScale.x, y / vScale.y, z / vScale.z);
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator/=(const f32& fScalar)
{
	f32 fInvScalar = 1 / fScalar;
	x *= fInvScalar; y *= fInvScalar; z *= fInvScalar;
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator/=(Vec3f_In vScale)
{
	x /= vScale.x; y /= vScale.y; z /= vScale.z;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator*(const f32& fScalar) const
{
	return Vec3f(x * fScalar, y * fScalar, z * fScalar);
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator*(Vec3f_In vScale) const
{
	return Vec3f(x * vScale.x, y * vScale.y, z * vScale.z);
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV operator*(const f32& fScalar, Vec3f_In vVector)
{
	return Vec3f(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar);
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator+=(Vec3f_In vVector)
{
	x += vVector.x;	y += vVector.y;	z += vVector.z;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator+(Vec3f_In vVector) const
{
	return Vec3f(x + vVector.x, y + vVector.y, z + vVector.z);
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator-=(Vec3f_In vVector)
{
	x -= vVector.x;	y -= vVector.y;	z -= vVector.z;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator-(Vec3f_In vVector) const
{
	return Vec3f(x - vVector.x, y - vVector.y, z - vVector.z);
}

__forceinline bool RECON_VEC_CALLCONV Vec3f::operator==(Vec3f_In vVector) const
{
	if(iX != vVector.iX)
		return false;
	if(iY != vVector.iY)
		return false;
	if(iZ != vVector.iZ)
		return false;
	return true;
}

__forceinline bool RECON_VEC_CALLCONV Vec3f::operator!=(Vec3f_In vVector) const
{
	if(iX != vVector.iX)
		return true;
	if(iY != vVector.iY)
		return true;
	if(iZ != vVector.iZ)
		return true;
	return false;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator&(Vec3f_In vVector) const
{
	return Vec3fInt(iX & vVector.iX, iY & vVector.iY, iZ & vVector.iZ);
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator&=(Vec3f_In vVector)
{
	iX &= vVector.iX;	iY &= vVector.iY;	iZ &= vVector.iZ;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator|(Vec3f_In vVector) const
{
	return Vec3fInt(iX | vVector.iX, iY | vVector.iY, iZ | vVector.iZ);
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator|=(Vec3f_In vVector)
{
	iX |= vVector.iX; iY |= vVector.iY; iZ |= vVector.iZ;
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3f::operator^(Vec3f_In vVector) const
{
	return Vec3fInt(iX ^ vVector.iX, iY ^ vVector.iY, iZ ^ vVector.iZ);
}

__forceinline void RECON_VEC_CALLCONV Vec3f::operator^=(Vec3f_In vVector)
{
	iX ^= vVector.iX; iY ^= vVector.iY; iZ ^= vVector.iZ;
}

__forceinline Vec3f_Out Vec3f::operator~() const
{
	return Vec3fInt(~iX, ~iY, ~iZ);
}

__forceinline const f32& Vec3f::operator[](s32 index) const
{
	return vector[index];
}

__forceinline f32& Vec3f::operator[](s32 index)
{
	return vector[index];
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3fInt(const s32& intVal)
{
	return Vec3f(*reinterpret_cast<const f32*>(&intVal));
}

__forceinline Vec3f_Out RECON_VEC_CALLCONV Vec3fInt(const s32& intX, const s32& intY, const s32& intZ)
{
	return Vec3f(*reinterpret_cast<const f32*>(&intX), *reinterpret_cast<const f32*>(&intY), *reinterpret_cast<const f32*>(&intZ));
}
