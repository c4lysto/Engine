#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "Component.h"

class HealthComponent : public IComponent
{
private:
	s32 m_MaxHealth;
	s32 m_CurrHealth;

public:
	HealthComponent();
	~HealthComponent();

	virtual void PostAdd();

	s32 GetMaxHealth() const {return m_MaxHealth;}
	void SetMaxHealth(s32 maxHealth) {m_MaxHealth = maxHealth;}

	s32 GetCurrHealth() const {return m_CurrHealth;}
	void SetCurrHealth(s32 currHealth);

	void TakeDamage(s32 healthDamage);
	void TakeDamage(float percentDamage) {return TakeDamage(s32(m_MaxHealth * percentDamage));}
	void Heal(s32 healthToHeal);
	void Heal(float percentToHeal) {return Heal(s32(m_MaxHealth * percentToHeal));}

	bool IsAlive() {return (m_CurrHealth > 0 && m_MaxHealth > 0);}
	bool IsDead() {return (m_CurrHealth <= 0 || m_MaxHealth <= 0);}
};

#endif // HEALTH_COMPONENT_H