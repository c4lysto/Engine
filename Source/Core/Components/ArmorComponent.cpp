#include "ArmorComponent.h"
#include "Math Lib\MathLib.h"

ArmorComponent::ArmorComponent() :
	m_Armor(0)
{

}

ArmorComponent::~ArmorComponent()
{

}

void ArmorComponent::PostAdd()
{

}

// Returns The Amount Of Damage That We Have Blocked
s32 ArmorComponent::TakeDamage(s32 damage)
{
	s32 currArmor = m_Armor;

	m_Armor = Max(m_Armor - damage, 0);

	return currArmor - m_Armor;
}