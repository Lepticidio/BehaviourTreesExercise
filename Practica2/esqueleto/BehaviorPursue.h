#pragma once
#include "Behavior.h"
class Character;
class PursueSteering;
class BehaviorPursue : public Behavior
{
    Character* m_pCharacter;
    PursueSteering* m_pPursueSteering;
public:
    BehaviorPursue(Character* _pCharacter, Character* _pOther);
    void onEnter() override;
    void onExit() override;
    Status update() override;
};

