#include "ComponentFactory.h"

recon::ComponentFactory gComponentFactory;

namespace recon
{

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

IComponent* ComponentFactory::CreateComponent(ComponentID componentID)
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

} // namespace recon