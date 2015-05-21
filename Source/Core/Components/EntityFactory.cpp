#include "EntityFactory.h"
#include "ComponentFactory.h"
#include "Entity.h"

EntityFactory::EntityFactory()
{

}

EntityFactory::~EntityFactory()
{

}

void EntityFactory::RegisterEntity(const EntityDesc& entityDesc)
{
	if(Verify(entityDesc.m_Name.size(), "Trying To Register An Entity With An Invalid Name"))
	{
		HashString hashName(entityDesc.m_Name.c_str());

		if(m_EntityDescs.find(hashName) != m_EntityDescs.end())
		{
			m_EntityDescs[hashName] = entityDesc;
		}
#if __ASSERT
		else
		{
			EntityDescContainer::const_iterator currEntry = m_EntityDescs.find(hashName);

			Assert(false, "Hash Name Collision For Newly Registered Entity! Curr Entry: '%s' New Entry: '%s'", 
						currEntry->second.m_Name.c_str(), entityDesc.m_Name.c_str());
		}
#endif // ASSERT
	}
}

CEntity* EntityFactory::CreateEntityFromDesc(const EntityDesc& entityDesc)
{
	CEntity* pEntity = new CEntity;

	for(EntityDesc::CoreComponentList::const_iterator iter = entityDesc.m_CoreComponents.begin(); iter != entityDesc.m_CoreComponents.end(); ++iter)
	{
		IComponent* pComponent = gComponentFactory.CreateComponent(*iter);

		pEntity->AddComponent(pComponent);
	}

	return pEntity;
}

void EntityFactory::Init(const char* szDirectory)
{
	m_EntityDescs.clear();

	// Load Entity Descs

}

CEntity* EntityFactory::CreateEntity(const char* szName)
{
	return szName ? CreateEntity(HashString(szName)) : nullptr;
}

CEntity* EntityFactory::CreateEntity(const HashString& hashName)
{
	EntityDescContainer::const_iterator iter = m_EntityDescs.find(hashName);

	CEntity* pEntity = nullptr;

	if(iter != m_EntityDescs.end())
	{
		if(pEntity)
		{
			pEntity = CreateEntityFromDesc(iter->second);
		}
	}

	return pEntity;
}