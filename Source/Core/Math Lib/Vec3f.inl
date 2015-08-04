
FORCEINLINE Vec3f::Vec3f(const float& fVal) : x(fVal), y(fVal), z(fVal)
{

}

FORCEINLINE Vec3f::Vec3f(const float& fX, const float& fY, const float& fZ) : x(fX), y(fY), z(fZ)
{

}

FORCEINLINE Vec3f::Vec3f(const float& fX, Vec2f_In vYZ) : x(fX), y(vYZ.GetXRef()), z(vYZ.GetYRef())
{

}

FORCEINLINE Vec3f::Vec3f(Vec2f_In vXY, const float& fZ) : x(vXY.GetXRef()), y(vXY.GetYRef()), z(fZ)
{

}

FORCEINLINE Vec3f::Vec3f(Vec3f_In vVector) : x(vVector.x), y(vVector.y), z(vVector.z)
{

}

FORCEINLINE Vec3f::Vec3f(Vec3f&& vVector)
{
	x = std::move(vVector.x);
	y = std::move(vVector.y);
	z = std::move(vVector.z);
}

#if SSE_AVAILABLE
FORCEINLINE Vec3f::Vec3f(Vector_In vVector)
{
	x = VectorExtractFloat<VecElem::X>(vVector);
	y = VectorExtractFloat<VecElem::Y>(vVector);
	z = VectorExtractFloat<VecElem::Z>(vVector);
}

#if !RECON_OS_64BIT
FORCEINLINE Vec3f::Vec3f(Vector&& vVector)
{
	x = VectorExtractFloat<VecElem::X>(vVector);
	y = VectorExtractFloat<VecElem::Y>(vVector);
	z = VectorExtractFloat<VecElem::Z>(vVector);
}
#endif // !RECON_OS_64BIT
#endif // SSE_AVAILABLE

FORCEINLINE Vec3f_Out Vec3f::operator-() const
{
	return Vec3fInt(iX ^ 0x80000000, iY ^ 0x80000000, iZ ^ 0x80000000);
}

FORCEINLINE Vec3f_Ref Vec3f::operator=(Vec3f_In vVector)
{
	if(this != &vVector)
	{
		x = vVector.x;
		y = vVector.y;
		z = vVector.z;
	}
	return *this;
}

FORCEINLINE Vec3f_Ref Vec3f::operator=(Vec3f&& vVector)
{
	if(this != &vVector)
	{
		x = std::move(vVector.x);
		y = std::move(vVector.y);
		z = std::move(vVector.z);
	}
	return *this;
}

FORCEINLINE void Vec3f::operator*=(const float& fScalar)
{
	x *= fScalar; y *= fScalar; z *= fScalar;
}

FORCEINLINE void Vec3f::operator*=(Vec3f_In vScale)
{
	x *= vScale.x; y *= vScale.y; z *= vScale.z;
}

FORCEINLINE Vec3f_Out Vec3f::operator/(const float& fScalar) const
{
	float fInvScalar = 1 / fScalar;
	return Vec3f(x * fInvScalar, y * fInvScalar, z * fInvScalar);
}

FORCEINLINE Vec3f_Out Vec3f::operator/(Vec3f_In vScale) const
{
	return Vec3f(x / vScale.x, y / vScale.y, z / vScale.z);
}

FORCEINLINE void Vec3f::operator/=(const float& fScalar)
{
	float fInvScalar = 1 / fScalar;
	x *= fInvScalar; y *= fInvScalar; z *= fInvScalar;
}

FORCEINLINE void Vec3f::operator/=(Vec3f_In vScale)
{
	x /= vScale.x; y /= vScale.y; z /= vScale.z;
}

FORCEINLINE Vec3f_Out Vec3f::operator*(const float& fScalar) const
{
	return Vec3f(x * fScalar, y * fScalar, z * fScalar);
}

FORCEINLINE Vec3f_Out Vec3f::operator*(Vec3f_In vScale) const
{
	return Vec3f(x * vScale.x, y * vScale.y, z * vScale.z);
}

FORCEINLINE Vec3f_Out operator*(const float& fScalar, Vec3f_In vVector)
{
	return Vec3f(vVector.x * fScalar, vVector.y * fScalar, vVector.z * fScalar);
}

FORCEINLINE void Vec3f::operator+=(Vec3f_In vVector)
{
	x += vVector.x;	y += vVector.y;	z += vVector.z;
}

FORCEINLINE Vec3f_Out Vec3f::operator+(Vec3f_In vVector) const
{
	return Vec3f(x + vVector.x, y + vVector.y, z + vVector.z);
}

FORCEINLINE void Vec3f::operator-=(Vec3f_In vVector)
{
	x -= vVector.x;	y -= vVector.y;	z -= vVector.z;
}

FORCEINLINE Vec3f_Out Vec3f::operator-(Vec3f_In vVector) const
{
	return Vec3f(x - vVector.x, y - vVector.y, z - vVector.z);
}

FORCEINLINE bool Vec3f::operator==(Vec3f_In vVector) const
{
	if(iX != vVector.iX)
		return false;
	if(iY != vVector.iY)
		return false;
	if(iZ != vVector.iZ)
		return false;
	return true;
}

FORCEINLINE bool Vec3f::operator!=(Vec3f_In vVector) const
{
	if(iX != vVector.iX)
		return true;
	if(iY != vVector.iY)
		return true;
	if(iZ != vVector.iZ)
		return true;
	return false;
}

FORCEINLINE Vec3f_Out Vec3f::operator&(Vec3f_In vVector) const
{
	return Vec3fInt(iX & vVector.iX, iY & vVector.iY, iZ & vVector.iZ);
}

FORCEINLINE void Vec3f::operator&=(Vec3f_In vVector)
{
	iX &= vVector.iX;	iY &= vVector.iY;	iZ &= vVector.iZ;
}

FORCEINLINE Vec3f_Out Vec3f::operator|(Vec3f_In vVector) const
{
	return Vec3fInt(iX | vVector.iX, iY | vVector.iY, iZ | vVector.iZ);
}

FORCEINLINE void Vec3f::operator|=(Vec3f_In vVector)
{
	iX |= vVector.iX; iY |= vVector.iY; iZ |= vVector.iZ;
}

FORCEINLINE Vec3f_Out Vec3f::operator^(Vec3f_In vVector) const
{
	return Vec3fInt(iX ^ vVector.iX, iY ^ vVector.iY, iZ ^ vVector.iZ);
}

FORCEINLINE void Vec3f::operator^=(Vec3f_In vVector)
{
	iX ^= vVector.iX; iY ^= vVector.iY; iZ ^= vVector.iZ;
}

FORCEINLINE Vec3f_Out Vec3f::operator~() const
{
	return Vec3fInt(~iX, ~iY, ~iZ);
}

FORCEINLINE const float& Vec3f::operator[](int index) const
{
	return vector[index];
}

FORCEINLINE float& Vec3f::operator[](int index)
{
	return vector[index];
}

FORCEINLINE Vec3f_Out Vec3fInt(const s32& intVal)
{
	return Vec3f(*reinterpret_cast<const float*>(&intVal));
}

FORCEINLINE Vec3f_Out Vec3fInt(const s32& intX, const s32& intY, const s32& intZ)
{
	return Vec3f(*reinterpret_cast<const float*>(&intX), *reinterpret_cast<const float*>(&intY), *reinterpret_cast<const float*>(&intZ));
}
