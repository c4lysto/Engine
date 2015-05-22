#ifndef ENTITY_H
#define ENTITY_H

#include "Utilities/UtilitiesInclude.h"

#include <map>
using std::map;

#include <string>
using std::string;

class IComponent;

typedef u64 ComponentID;
typedef u64 EntityID;

#define INVALID_ENTITY_ID ((EntityID)-1)

typedef map<ComponentID, IComponent*> EntityComponentContainer;

class CEntity
{
private:
	EntityID m_ID;

#if DEBUG
	string m_szEntityName;
#endif

	EntityComponentContainer m_Components;

public:
	CEntity();
	~CEntity();

	EntityID GetID() {return m_ID;}

	template<typename ComponentClass>
	void AddComponent(ComponentClass* pComponent);

	template<typename ComponentClass>
	void RemoveComponent();

	template<typename ComponentClass>
	ComponentClass* GetComponent();

private:
	void ShutdownComponents();

};

#endif // ENTITY_H