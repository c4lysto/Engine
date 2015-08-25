#ifndef OBJECT_TRANSFORM_H
#define OBJECT_TRANSFORM_H

#include "../Math Lib/MathLib.h"

class IObjectTransform
{
private:

public:
	IObjectTransform() {}
	virtual ~IObjectTransform() {}

	virtual Vec3V_Out GetPosition() const {return Vec3V(I_ZERO);}
	virtual Mat33V_Out GetMat33() const {return Mat33V(I_IDENTITY);}
	virtual Mat43V_Out GetMatrix() const {return Mat43V(I_IDENTITY);}
	virtual Mat44V_Out GetFullMatrix() const {return Mat44V(I_IDENTITY);}
};

class IdentityTransform : public IObjectTransform
{
private:

public:
	IdentityTransform() {}
	~IdentityTransform() {}
};

class PositionTransform : public IObjectTransform
{
private:
	Vec3V m_vPos;

public:
	PositionTransform() : m_vPos(I_ZERO) {}
	explicit PositionTransform(Vec3V_In vPos) : m_vPos(vPos) {}
	~PositionTransform() {}

	virtual Vec3V_Out GetPosition() const override {return m_vPos;}
	virtual Mat43V_Out GetMatrix() const override {return Mat43V(I_MAT_POS, m_vPos);}
	virtual Mat44V_Out GetFullMatrix() const override { return Mat44V(I_MAT_POS, m_vPos); }
};

class FullMatrixTransform : public IObjectTransform
{
private:
	Mat43V m_vTransform;

public:
	FullMatrixTransform() : m_vTransform(I_IDENTITY) {}
	explicit FullMatrixTransform(Mat44V_In mMatrix) : m_vTransform(mMatrix) {}
	~FullMatrixTransform() {}

	virtual Vec3V_Out GetPosition() const override {return m_vTransform.GetWAxis().GetXYZ();}
	virtual Mat43V_Out GetMatrix() const override {return m_vTransform;}
	virtual Mat44V_Out GetFullMatrix() const override { return Mat43ToMat44(m_vTransform); }
};

#endif // OBJECT_TRANSFORM_H