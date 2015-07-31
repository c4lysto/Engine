#ifndef COMPONENTCONTAINER_H
#define COMPONENTCONTAINER_H

#include "Component.h"

class ComponentContainer : public recon::IComponent
{
private:


public:
	ComponentContainer(recon::Entity* pParent);
	virtual ~ComponentContainer();

};

#endif // COMPONENTCONTAINER_H