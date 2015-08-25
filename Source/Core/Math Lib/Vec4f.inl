
__forceinline Vec4f::Vec4f(Vec4f_In vVector) : x(vVector.x), y(vVector.y), z(vVector.z), w(vVector.w)
{

}

__forceinline Vec4f::Vec4f(Vec4f&& vVector) : x(vVector.x), y(vVector.y), z(vVector.z), w(vVector.w)
{

}

#if SSE_AVAILABLE
__forceinline Vec4f::Vec4f(Vector_In vVector)
{
	VectorStoreU(vVector, vector);
}

#if !RECON_OS_64BIT
__forceinline Vec4f::Vec4f(Vector&& vVector)
{
	VectorStoreU(vVector, vector);
}
#endif // !RECON_OS_64BIT
#endif //SSE_AVAILABLE

__forceinline Vec4f::Vec4f(const f32& fVal) : x(fVal), y(fVal), z(fVal), w(fVal)
{

}

__forceinline Vec4f::Vec4f(const f32& fX, const f32& fY, const f32& fZ, const f32& fW) : x(fX), y(fY), z(fZ), w(fW)
{

}

__forceinline Vec4f::Vec4f(Vec2f_In vXY, Vec2f_In vZW) :
	x(vXY.GetXRef()),
	y(vXY.GetYRef()),
	z(vZW.GetXRef()),
	w(vZW.GetYRef())
{

}

__forceinline Vec4f::Vec4f(const f32& fX, const f32& fY, Vec2f_In vZW) : 
	x(fX),
	y(fY),
	z(vZW.GetXRef()),
	w(vZW.GetYRef())
{

}

__forceinline Vec4f::Vec4f(Vec2f_In vXY, const f32& fZ, const f32& fW) :
	x(vXY.GetXRef()),
	y(vXY.GetYRef()),
	z(fZ),
	w(fW)
{

}

__forceinline Vec4f::Vec4f(const f32& fX, Vec3f_In vYZW) : 
	x(fX),
	y(vYZW.GetXRef()),
	z(vYZW.GetYRef()),
	w(vYZW.GetZRef())
{

}

__forceinline Vec4f::Vec4f(Vec3f_In vVector, const f32& fW) : position(vVector), w(fW)
{

}

__forceinline Vec4f_Out Vec4f::operator-()
{
	return Vec4fInt(iX ^ 0x80000000, iY ^ 0x80000000, iZ ^ 0x80000000, iW ^ 0x80000000);
}

__forceinline Vec4f_Ref RECON_VEC_CALLCONV Vec4f::operator=(Vec4f_In vVector)
{
	x = vVector.x; y = vVector.y; z = vVector.z; w = vVector.w;
	return *this;
}

__forceinline Vec4f_Ref RECON_VEC_CALLCONV Vec4f::operator=(Vec4f&& vVector)
{
	x = vVector.x; y = vVector.y; z = vVector.z; w = vVector.w;
	return *this;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator-(Vec4f_In vVector) const
{
	return Vec4f(x - vVector.x, y - vVector.y, z - vVector.z, w - vVector.w);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator-=(Vec4f_In vVector)
{
	x -= vVector.x; y -= vVector.y; z -= vVector.z; w -= vVector.w;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator+(Vec4f_In vVector) const
{
	return Vec4f(x + vVector.x, y + vVector.y, z + vVector.z, w + vVector.w);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator+=(Vec4f_In vVector)
{
	x += vVector.x; y += vVector.y; z += vVector.z; w += vVector.w;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator/(const f32& fScalar) const
{
	f32 fInvScalar = 1.0f / fScalar;
	return Vec4f(x * fInvScalar, y * fInvScalar, z * fInvScalar, w * fInvScalar);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator/=(const f32& fScalar)
{
	f32 fInvScalar = 1.0f / fScalar;
	x *= fInvScalar; y *= fInvScalar; z *= fInvScalar; w *= fInvScalar;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator/(Vec4f_In vVector) const
{
	return Vec4f(x/vVector.x, y/vVector.y, z/vVector.z, w/vVector.w);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator/=(Vec4f_In vVector)
{
	x /= vVector.x; y /= vVector.y; z /= vVector.z; w /= vVector.w;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator*(Vec4f_In vVector) const
{
	return Vec4f(x * vVector.x, y * vVector.y, z * vVector.z, w * vVector.w);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator*=(Vec4f_In vVector)
{
	x *= vVector.x;	y *= vVector.y;	z *= vVector.z;	w *= vVector.w;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator*(const f32& fScalar) const
{
	return Vec4f(x * fScalar, y * fScalar, z * fScalar, w * fScalar);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator*=(const f32& fScalar)
{
	x *= fScalar; y *= fScalar; z *= fScalar; w *= fScalar;
}

__forceinline Vec4f RECON_VEC_CALLCONV operator*(const f32& fScalar, Vec4f_In vVector)
{
	return Vec4f(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar, vVector.w * fScalar);
}


__forceinline bool RECON_VEC_CALLCONV Vec4f::operator==(Vec4f_In vVector)
{
	if(iX != vVector.iX)
		return false;
	if(iY != vVector.iY)
		return false;
	if(iZ != vVector.iZ)
		return false;
	if(iW != vVector.iW)
		return false;
	return true;
}

__forceinline bool RECON_VEC_CALLCONV Vec4f::operator!=(Vec4f_In vVector)
{
	if(iX != vVector.iX)
		return true;
	if(iY != vVector.iY)
		return true;
	if(iZ != vVector.iZ)
		return true;
	if(iW != vVector.iW)
		return true;
	return false;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator&(Vec4f_In vVector) const
{
	return Vec4fInt(iX & vVector.iX, iY & vVector.iY, iZ & vVector.iZ, iW & vVector.iW);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator&=(Vec4f_In vVector)
{
	iX &= vVector.iX; iY &= vVector.iY; iZ &= vVector.iZ; iW &= vVector.iW;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator|(Vec4f_In vVector) const
{
	return Vec4fInt(iX | vVector.iX, iY | vVector.iY, iZ | vVector.iZ, iW | vVector.iW);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator|=(Vec4f_In vVector)
{
	iX |= vVector.iX; iY |= vVector.iY; iZ |= vVector.iZ; iW |= vVector.iW;
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4f::operator^(Vec4f_In vVector) const
{
	return Vec4fInt(iX ^ vVector.iX, iY ^ vVector.iY, iZ ^ vVector.iZ, iW ^ vVector.iW);
}

__forceinline void RECON_VEC_CALLCONV Vec4f::operator^=(Vec4f_In vVector)
{
	iX ^= vVector.iX; iY ^= vVector.iY; iZ ^= vVector.iZ; iW ^= vVector.iW;
}

__forceinline Vec4f_Out Vec4f::operator~() const
{
	return Vec4fInt(~iX, ~iY, ~iZ, ~iW);
}

__forceinline const f32& Vec4f::operator[](s32 index) const
{
	return vector[index];
}

__forceinline f32& Vec4f::operator[](s32 index)
{
	return vector[index];
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4fInt(const s32& intVal)
{
	return Vec4f(*reinterpret_cast<const f32*>(&intVal));
}

__forceinline Vec4f_Out RECON_VEC_CALLCONV Vec4fInt(const s32& intX, const s32& intY, const s32& intZ, const s32& intW)
{
	return Vec4f(*reinterpret_cast<const f32*>(&intX), *reinterpret_cast<const f32*>(&intY), *reinterpret_cast<const f32*>(&intZ), *reinterpret_cast<const f32*>(&intW));
}
