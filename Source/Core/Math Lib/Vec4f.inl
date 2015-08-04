
FORCEINLINE Vec4f::Vec4f(Vec4f_In vVector)
#if !SSE_AVAILABLE || 1
: x(vVector.x), y(vVector.y), z(vVector.z), w(vVector.w)
#endif
{
#if SSE_AVAILABLE && 0
	VectorStoreU(VectorLoadU(vVector.vector), vector);
#endif
}

FORCEINLINE Vec4f::Vec4f(Vec4f&& vVector)
#if !SSE_AVAILABLE || 1
: x(vVector.x), y(vVector.y), z(vVector.z), w(vVector.w)
#endif
{
#if SSE_AVAILABLE && 0
	VectorStoreU(VectorLoadU(vVector.vector), vector);
#endif
}

#if SSE_AVAILABLE
FORCEINLINE Vec4f::Vec4f(Vector_In vVector)
{
	VectorStoreU(vVector, vector);
}

#if !RECON_OS_64BIT
FORCEINLINE Vec4f::Vec4f(Vector&& vVector)
{
	VectorStoreU(vVector, vector);
}
#endif // !RECON_OS_64BIT
#endif //SSE_AVAILABLE

FORCEINLINE Vec4f::Vec4f(const float& fVal) : x(fVal), y(fVal), z(fVal), w(fVal)
{

}

FORCEINLINE Vec4f::Vec4f(const float& fX, const float& fY, const float& fZ, const float& fW) : x(fX), y(fY), z(fZ), w(fW)
{

}

FORCEINLINE Vec4f::Vec4f(Vec2f_In vXY, Vec2f_In vZW) :
	x(vXY.GetXRef()),
	y(vXY.GetYRef()),
	z(vZW.GetXRef()),
	w(vZW.GetYRef())
{

}

FORCEINLINE Vec4f::Vec4f(const float& fX, const float& fY, Vec2f_In vZW) : 
	x(fX),
	y(fY),
	z(vZW.GetXRef()),
	w(vZW.GetYRef())
{

}

FORCEINLINE Vec4f::Vec4f(Vec2f_In vXY, const float& fZ, const float& fW) :
	x(vXY.GetXRef()),
	y(vXY.GetYRef()),
	z(fZ),
	w(fW)
{

}

FORCEINLINE Vec4f::Vec4f(const float& fX, Vec3f_In vYZW) : 
	x(fX),
	y(vYZW.GetXRef()),
	z(vYZW.GetYRef()),
	w(vYZW.GetZRef())
{

}

FORCEINLINE Vec4f::Vec4f(Vec3f_In vVector, const float& fW) : position(vVector), w(fW)
{

}

FORCEINLINE Vec4f_Out Vec4f::operator-()
{
	return Vec4fInt(iX ^ 0x80000000, iY ^ 0x80000000, iZ ^ 0x80000000, iW ^ 0x80000000);
}

FORCEINLINE Vec4f_Ref Vec4f::operator=(Vec4f_In vVector)
{
	x = vVector.x; y = vVector.y; z = vVector.z; w = vVector.w;
	return *this;
}

FORCEINLINE Vec4f_Ref Vec4f::operator=(Vec4f&& vVector)
{
	x = vVector.x; y = vVector.y; z = vVector.z; w = vVector.w;
	return *this;
}

FORCEINLINE Vec4f_Out Vec4f::operator-(Vec4f_In vVector) const
{
	return Vec4f(x - vVector.x, y - vVector.y, z - vVector.z, w - vVector.w);
}

FORCEINLINE void Vec4f::operator-=(Vec4f_In vVector)
{
	x -= vVector.x; y -= vVector.y; z -= vVector.z; w -= vVector.w;
}

FORCEINLINE Vec4f_Out Vec4f::operator+(Vec4f_In vVector) const
{
	return Vec4f(x + vVector.x, y + vVector.y, z + vVector.z, w + vVector.w);
}

FORCEINLINE void Vec4f::operator+=(Vec4f_In vVector)
{
	x += vVector.x; y += vVector.y; z += vVector.z; w += vVector.w;
}

FORCEINLINE Vec4f_Out Vec4f::operator/(const float& fScalar) const
{
	float fInvScalar = 1.0f / fScalar;
	return Vec4f(x * fInvScalar, y * fInvScalar, z * fInvScalar, w * fInvScalar);
}

FORCEINLINE void Vec4f::operator/=(const float& fScalar)
{
	float fInvScalar = 1.0f / fScalar;
	x *= fInvScalar; y *= fInvScalar; z *= fInvScalar; w *= fInvScalar;
}

FORCEINLINE Vec4f_Out Vec4f::operator/(Vec4f_In vVector) const
{
	return Vec4f(x/vVector.x, y/vVector.y, z/vVector.z, w/vVector.w);
}

FORCEINLINE void Vec4f::operator/=(Vec4f_In vVector)
{
	x /= vVector.x; y /= vVector.y; z /= vVector.z; w /= vVector.w;
}

FORCEINLINE Vec4f_Out Vec4f::operator*(Vec4f_In vVector) const
{
	return Vec4f(x * vVector.x, y * vVector.y, z * vVector.z, w * vVector.w);
}

FORCEINLINE void Vec4f::operator*=(Vec4f_In vVector)
{
	x *= vVector.x;	y *= vVector.y;	z *= vVector.z;	w *= vVector.w;
}

FORCEINLINE Vec4f_Out Vec4f::operator*(const float& fScalar) const
{
	return Vec4f(x * fScalar, y * fScalar, z * fScalar, w * fScalar);
}

FORCEINLINE void Vec4f::operator*=(const float& fScalar)
{
	x *= fScalar; y *= fScalar; z *= fScalar; w *= fScalar;
}

FORCEINLINE Vec4f operator*(const float& fScalar, Vec4f_In vVector)
{
	return Vec4f(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar, vVector.w * fScalar);
}


FORCEINLINE bool Vec4f::operator==(Vec4f_In vVector)
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

FORCEINLINE bool Vec4f::operator!=(Vec4f_In vVector)
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

FORCEINLINE Vec4f_Out Vec4f::operator&(Vec4f_In vVector) const
{
	return Vec4fInt(iX & vVector.iX, iY & vVector.iY, iZ & vVector.iZ, iW & vVector.iW);
}

FORCEINLINE void Vec4f::operator&=(Vec4f_In vVector)
{
	iX &= vVector.iX; iY &= vVector.iY; iZ &= vVector.iZ; iW &= vVector.iW;
}

FORCEINLINE Vec4f_Out Vec4f::operator|(Vec4f_In vVector) const
{
	return Vec4fInt(iX | vVector.iX, iY | vVector.iY, iZ | vVector.iZ, iW | vVector.iW);
}

FORCEINLINE void Vec4f::operator|=(Vec4f_In vVector)
{
	iX |= vVector.iX; iY |= vVector.iY; iZ |= vVector.iZ; iW |= vVector.iW;
}

FORCEINLINE Vec4f_Out Vec4f::operator^(Vec4f_In vVector) const
{
	return Vec4fInt(iX ^ vVector.iX, iY ^ vVector.iY, iZ ^ vVector.iZ, iW ^ vVector.iW);
}

FORCEINLINE void Vec4f::operator^=(Vec4f_In vVector)
{
	iX ^= vVector.iX; iY ^= vVector.iY; iZ ^= vVector.iZ; iW ^= vVector.iW;
}

FORCEINLINE Vec4f_Out Vec4f::operator~() const
{
	return Vec4fInt(~iX, ~iY, ~iZ, ~iW);
}

FORCEINLINE const float& Vec4f::operator[](int index) const
{
	return vector[index];
}

FORCEINLINE float& Vec4f::operator[](int index)
{
	return vector[index];
}

FORCEINLINE Vec4f_Out Vec4fInt(const s32& intVal)
{
	return Vec4f(*reinterpret_cast<const float*>(&intVal));
}

FORCEINLINE Vec4f_Out Vec3fInt(const s32& intX, const s32& intY, const s32& intZ, const s32& intW)
{
	return Vec4f(*reinterpret_cast<const float*>(&intX), *reinterpret_cast<const float*>(&intY), *reinterpret_cast<const float*>(&intZ), *reinterpret_cast<const float*>(&intW));
}
