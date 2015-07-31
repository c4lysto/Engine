#ifndef _RECON_COMPONENT_FACTORY_H_
#define _RECON_COMPONENT_FACTORY_H_

#include "Component.h"

#include <map>

namespace recon
{

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

} // namespace recon

extern recon::ComponentFactory gComponentFactory;

#endif // _RECON_COMPONENT_FACTORY_H_