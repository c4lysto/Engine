#ifndef _RECON_ENTITY_H_
#define _RECON_ENTITY_H_

#include "Utilities/UtilitiesInclude.h"

#include <map>
using std::map;

#include <string>
using std::string;

typedef u64 ComponentID;
typedef u64 EntityID;

#define INVALID_ENTITY_ID ((EntityID)-1)

namespace recon
{

class IComponent;

class Entity
{
private:
	typedef map<ComponentID, IComponent*> EntityComponentContainer;

private:
	EntityID m_ID;

#if RECON_DEBUG
	string m_szEntityName;
#endif

	EntityComponentContainer m_Components;

public:
	Entity();
	~Entity();

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

} // namespace recon

#endif // _RECON_ENTITY_H_