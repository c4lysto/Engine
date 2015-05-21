#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "../Utilities/HashString.h"

#include <map>
#include <list>

class CEntity;

class EntityFactory
{
private:
	struct EntityDesc
	{
		typedef std::list<u64> CoreComponentList;

		std::string m_Name;
		CoreComponentList m_CoreComponents;
	};

private:
	typedef std::map<HashString, EntityDesc> EntityDescContainer;

	EntityDescContainer m_EntityDescs;

private:
	void RegisterEntity(const EntityDesc& entityDesc);

	CEntity* CreateEntityFromDesc(const EntityDesc& entityDesc);

public:
	EntityFactory();
	~EntityFactory();

	void Init(const char* szDirectory);

	CEntity* CreateEntity(const char* szName);
	CEntity* CreateEntity(const HashString& hashName);
};

#endif // ENTITY_FACTORY_H