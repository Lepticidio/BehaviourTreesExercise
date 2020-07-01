#pragma once
#include "Behavior.h"
class Character;
class PursueSteering;
class BehaviorWindup : public Behavior
{
	float m_fTimePassed = 0.0f;
	float m_fWindupTime = 0.5f;
	Character* m_pCharacter;
	PursueSteering* m_pPursueSteering;
public:
	BehaviorWindup(Character* _pOwner, Character* _pTarget);
	void onEnter() override;
	void onExit() override;
	Status update() override;
};