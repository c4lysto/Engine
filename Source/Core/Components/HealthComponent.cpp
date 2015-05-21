#include "HealthComponent.h"
#include "Math Lib\MathLib.h"

HealthComponent::HealthComponent() : 
	m_MaxHealth(0),
	m_CurrHealth(0)
{

}

HealthComponent::~HealthComponent()
{
	m_MaxHealth = 0;
	m_CurrHealth = 0;
}

void HealthComponent::PostAdd()
{
	m_MaxHealth = 100;
	m_CurrHealth = m_MaxHealth;
}

void HealthComponent::SetCurrHealth(s32 currHealth)
{
	m_CurrHealth = Clamp(currHealth, 0, m_MaxHealth);
}

void HealthComponent::TakeDamage(s32 healthDamage)
{
	m_CurrHealth = Max(m_CurrHealth - healthDamage, 0);
}

void HealthComponent::Heal(s32 healthToHeal)
{
	m_CurrHealth = Min(m_CurrHealth + healthToHeal, m_MaxHealth);
}