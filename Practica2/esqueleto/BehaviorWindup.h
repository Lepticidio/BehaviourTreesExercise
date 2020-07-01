#pragma once
#include "Behavior.h"
class Character;
class BehaviorWindup : public Behavior
{
	float m_fTimePassed = 0.0f;
	float m_fWindupTime = 0.5f;
	Character* m_pCharacter;
public:
	BehaviorWindup(Character* _pOwner);
	void onEnter() override;
	void onExit() override;
	Status update() override;
};