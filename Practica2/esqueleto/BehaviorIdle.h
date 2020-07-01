#pragma once
#include "Behavior.h"
class Character;
class BehaviorIdle : public Behavior
{
	Character* m_pCharacter;
public:
	BehaviorIdle();
	BehaviorIdle(Character* _pCharacter);
	Status update();
	void onEnter();
};

