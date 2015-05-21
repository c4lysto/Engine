#ifndef ARMOR_COMPONENT_H
#define ARMOR_COMPONENT_H

#include "Component.h"

class ArmorComponent : public IComponent
{
private:
	s32 m_Armor;

public:
	ArmorComponent();
	~ArmorComponent();

	virtual void PostAdd();

	s32 GetArmor() const {return m_Armor;}
	void SetArmor(s32 armor) {m_Armor = armor;}

	// Returns The Amount Of Damage That We Have Blocked
	s32 TakeDamage(s32 damage);

};

#endif // ARMOR_COMPONENT_H