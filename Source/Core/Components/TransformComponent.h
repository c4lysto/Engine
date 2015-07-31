#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include "ObjectTransform.h"

class TransformComponent : public recon::IComponent
{
private:
	IObjectTransform* m_pTransform;

public:
	TransformComponent() {}
	~TransformComponent() {}

	Vec3V_Out GetPosition() const {return m_pTransform ? m_pTransform->GetPosition() : Vec3V(I_ZERO);}

	Mat33V_Out GetMat33() const  {return m_pTransform ? m_pTransform->GetMat33() : Mat33V(I_IDENTITY);}
	Mat34V_Out GetMatrix() const { return m_pTransform ? m_pTransform->GetMatrix() : Mat34V(I_IDENTITY); }
	Mat44V_Out GetFullMatrix() const { return m_pTransform ? m_pTransform->GetFullMatrix() : Mat44V(I_IDENTITY); }

	void TransformLocal(Mat44V_In mTransform);
	void TransformGlobal(Mat44V_In mTransform);

	void Translate(Vec3V_In vTranslation);

	REGISTER_MEM_POOL(TransformComponent);
};

#endif // TRANSFORM_COMPONENT_H