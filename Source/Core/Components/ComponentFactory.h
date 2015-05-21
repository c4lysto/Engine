#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include "Component.h"

#include <map>

class ComponentFactory
{
private:
	struct ComponentDesc
	{
		std::string m_szName;
		
	};

	//typedef std::map<u64, > ComponentPoolContainer;

private:

public:
	ComponentFactory();
	~ComponentFactory();

	void Init();

	template<typename ComponentClass>
	ComponentClass* CreateComponent();

	IComponent* CreateComponent(ComponentID componentID);

	template<typename ComponentClass>
	void ReturnComponent(ComponentClass* pComponent);
};

extern ComponentFactory gComponentFactory;

#endif // COMPONENT_FACTORY_H