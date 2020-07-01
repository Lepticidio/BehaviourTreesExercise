#pragma once
#include "Behavior.h"
class Character;
class BehaviorAttack : public Behavior
{
	float m_fTimePassed = 0.0f;
	float m_fCooldownTime = 1.0f;
	float m_fDamage = 40;
	Character* m_pCharacter;
	Character* m_pTarget;
public:
	BehaviorAttack(Character* _pOwner, Character* _pTarget);
	void onEnter() override;
	void onExit() override;
	Status update() override;
};

