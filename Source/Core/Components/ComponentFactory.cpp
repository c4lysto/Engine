#include "ComponentFactory.h"

ComponentFactory gComponentFactory;

ComponentFactory::ComponentFactory()
{

}

ComponentFactory::~ComponentFactory()
{

}

void ComponentFactory::Init()
{

}

template<typename ComponentClass>
ComponentClass* ComponentFactory::CreateComponent()
{
	return new ComponentClass;
}

IComponent* CreateComponent(ComponentID componentID)
{

}

template<typename ComponentClass>
void ComponentFactory::ReturnComponent(ComponentClass* pComponent)
{
	if(pComponent)
	{
		delete pComponent;
	}
}