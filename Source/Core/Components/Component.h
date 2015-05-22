#ifndef COMPONENT_H
#define COMPONENT_H

#include <typeinfo>
#include "../Utilities/Memory/ObjectMemoryPool.h"

typedef u64 ComponentID;

#define INVALID_COMPONENT_ID ((ComponentID)-1)

template<typename ComponentClass>
__forceinline ComponentID GetComponentID() \
{ \
	return (ComponentID)typeid(ComponentClass).hash_code(); \
}

template<typename ComponentClass>
__forceinline const char* GetComponentName() \
{ \
	return typeid(ComponentClass).name(); \
}

#define COMPONENT_ID(className) (GetComponentID<(className)>())
#define COMPONENT_NAME(className) (GetComponentName<(className)>())


class CEntity;

class IComponent
{
protected:
	CEntity* m_pEntity;

public:
	IComponent() : m_pEntity(nullptr) {}
	IComponent(CEntity* pParent) : m_pEntity(pParent) {}

	// Runtime Check, Slower Than Using COMPONENT_ID()/COMPONENT_NAME()
	// and should only be used if we do not know the type of the component
	// at compile time
	__forceinline ComponentID GetID() {return typeid(*this).hash_code();}
	__forceinline const char* GetName() {return typeid(*this).name();}

	virtual ~IComponent() = 0 {m_pEntity = nullptr;}

	virtual void PostAdd() {}
	virtual void PostRemove() {}
};

#endif // COMPONENT_H