#ifndef _RECON_ENTITY_FACTORY_H_
#define _RECON_ENTITY_FACTORY_H_

#include "../Utilities/HashString.h"

#include <map>
#include <list>

namespace recon
{

class Entity;

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

	Entity* CreateEntityFromDesc(const EntityDesc& entityDesc);

public:
	EntityFactory();
	~EntityFactory();

	void Init(const char* szDirectory);

	Entity* CreateEntity(const char* szName);
	Entity* CreateEntity(const HashString& hashName);
};

} // namespace recon

#endif // _RECON_ENTITY_FACTORY_H_