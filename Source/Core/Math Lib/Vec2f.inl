
__forceinline Vec2f::Vec2f(Vec2f_In vVector) : x(vVector.x), y(vVector.y)
{

}

__forceinline Vec2f::Vec2f(Vec2f&& vVector) : x(std::move(vVector.x)), y(std::move(vVector.y))
{

}

__forceinline Vec2f::Vec2f(const f32& fVal) : x(fVal), y(fVal)
{

}

__forceinline Vec2f::Vec2f(const f32& fX, const f32& fY) : x(fX), y(fY)
{
	
}

#if RECON_SSE_VERSION
__forceinline Vec2f::Vec2f(Vector128_In vVector)
{
	x = VectorExtractFloat<VecElem::X>(vVector);
	y = VectorExtractFloat<VecElem::Y>(vVector);
}

#if !RECON_OS_64BIT
__forceinline Vec2f::Vec2f(Vector128&& vVector)
{
	x = VectorExtractFloat<VecElem::X>(vVector);
	y = VectorExtractFloat<VecElem::Y>(vVector);
}
#endif // !RECON_OS_64BIT
#endif // RECON_SSE_VERSION

__forceinline Vec2f_Ref RECON_VEC_CALLCONV Vec2f::operator=(Vec2f_In vVector)
{
	if(this != &vVector)
	{
		x = vVector.x;
		y = vVector.y;
	}
	return *this;
}

__forceinline Vec2f_Ref RECON_VEC_CALLCONV Vec2f::operator=(Vec2f&& vVector)
{
	if(this != &vVector)
	{
		x = std::move(vVector.x);
		y = std::move(vVector.y);
	}
	return *this;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator+(Vec2f_In vVector) const
{
	return Vec2f(x + vVector.x, y + vVector.y);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator+=(Vec2f_In vVector)
{
	x += vVector.x;	y += vVector.y;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator-(Vec2f_In vVector) const
{
	return Vec2f(x - vVector.x, y - vVector.y);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator-=(Vec2f_In vVector)
{
	x -= vVector.x;	y -= vVector.y;
}

__forceinline Vec2f_Out Vec2f::operator-() const
{
	return Vec2fInt(iX ^ 0x80000000, iY ^ 0x80000000);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator*(const f32& fScalar) const
{
	return Vec2f(x * fScalar, y * fScalar);
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV operator*(const f32& fScalar, Vec2f_In vVector)
{
	return Vec2f(vVector.x * fScalar, vVector.y * fScalar);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator*=(const f32& fScalar)
{
	x *= fScalar; y *= fScalar;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator*(Vec2f_In vVector) const
{
	return Vec2f(x * vVector.x, y * vVector.y);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator*=(Vec2f_In vVector)
{
	x *= vVector.x; y *= vVector.y;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator/(const f32& fScalar) const
{
	f32 fInvScalar = 1 / fScalar;
	return Vec2f(x * fInvScalar, y * fInvScalar);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator/=(const f32& fScalar)
{
	f32 fInvScalar = 1 / fScalar;
	x *= fInvScalar; y *= fInvScalar;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator/(Vec2f_In vVector) const
{
	return Vec2f(x/vVector.x, y/vVector.y);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator/=(Vec2f_In vVector)
{
	x /= vVector.x; y /= vVector.y;
}

__forceinline bool RECON_VEC_CALLCONV Vec2f::operator==(Vec2f_In vVector)
{
	if(iX != vVector.iX)
		return false;
	if(iY != vVector.iY)
		return false;
	return true;
}

__forceinline bool RECON_VEC_CALLCONV Vec2f::operator!=(Vec2f_In vVector)
{
	if(iX != vVector.iX)
		return true;
	if(iY != vVector.iY)
		return true;
	return false;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator&(Vec2f_In vVector) const
{
	return Vec2fInt(iX & vVector.iX, iY & vVector.iY);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator&=(Vec2f_In vVector)
{
	iX &= vVector.iX; iY &= vVector.iY;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator|(Vec2f_In vVector) const
{
	return Vec2fInt(iX | vVector.iX, iY | vVector.iY);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator|=(Vec2f_In vVector)
{
	iX |= vVector.iX; iY |= vVector.iY;
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2f::operator^(Vec2f_In vVector) const
{
	return Vec2fInt(iX ^ vVector.iX, iY ^ vVector.iY);
}

__forceinline void RECON_VEC_CALLCONV Vec2f::operator^=(Vec2f_In vVector)
{
	iX ^= vVector.iX; iY ^= vVector.iY;
}

__forceinline Vec2f_Out Vec2f::operator~() const
{
	return Vec2fInt(~iX, ~iY);
}

__forceinline const f32& Vec2f::operator[](s32 index) const
{
	return vector[index];
}

__forceinline f32& Vec2f::operator[](s32 index)
{
	return vector[index];
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2fInt(const s32& intVal)
{
	return Vec2f(*reinterpret_cast<const f32*>(&intVal));
}

__forceinline Vec2f_Out RECON_VEC_CALLCONV Vec2fInt(const s32& intX, const s32& intY)
{
	return Vec2f(*reinterpret_cast<const f32*>(&intX), *reinterpret_cast<const f32*>(&intY));
}
