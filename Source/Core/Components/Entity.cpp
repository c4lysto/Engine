#include "Entity.h"
#include "Component.h"

CEntity::CEntity() : m_ID(INVALID_ENTITY_ID)
{
	m_Components.clear();
}

CEntity::~CEntity()
{
	ShutdownComponents();
}

template<typename ComponentClass>
void CEntity::AddComponent(ComponentClass* pComponent)
{
	if(Verify(pComponent, "Attempting To Add An Invalid Component To An Entity", COMPONENT_ID(ComponentClass)))
	{
		if(Verify(m_Components.find(COMPONENT_ID(ComponentClass)) == m_Components.end(), 
					"Component (ID: %d, Name: %s) Already Exists On Entity!", COMPONENT_ID(ComponentClass), COMPONENT_NAME(ComponentClass)))
		{
			m_Components.insert(pComponent);
			pComponent->PostAdd();
		}
	}
}

template<typename ComponentClass>
void CEntity::RemoveComponent()
{
	Assert(COMPONENT_ID(ComponentClass) != INVALID_COMPONENT_ID, "Component (%s) has an ID that is the same as INVALID_COMPONENT_ID", COMPONENT_NAME(ComponentClass));
	
	//if(Verify(pComponent, "Attempting To Remove An Invalid Component (ID: %d, Name: %s) From An Entity", COMPONENT_ID(ComponentClass), COMPONENT_NAME(ComponentClass)))
	{
		EntityComponentContainer::iterator iter = m_Components.find(COMPONENT_ID(ComponentClass));
		if(iter != m_Components.end())
		{
			if(iter->second)
			{
				iter->second->PostRemove();
				delete iter->second;
			}

			m_Components.erase(iter);
		}
	}
}

template<typename ComponentClass>
ComponentClass* CEntity::GetComponent()
{
	Assert(COMPONENT_ID(ComponentClass) != INVALID_COMPONENT_ID, "Component (%s) has an ID that is the same as INVALID_COMPONENT_ID", COMPONENT_NAME(ComponentClass));

	EntityComponentContainer::iterator iter = m_Components.find(COMPONENT_ID(ComponentClass));

	if(iter != m_Component.end())
	{
		return (ComponentClass*)iter->second;
	}

	return nullptr;
}

void CEntity::ShutdownComponents()
{
	for(EntityComponentContainer::iterator iter = m_Components.begin(); iter != m_Components.end(); ++iter)
	{
		if(iter->second)
		{
			iter->second->PostRemove();
			delete iter->second;
		}
	}

	m_Components.clear();
}