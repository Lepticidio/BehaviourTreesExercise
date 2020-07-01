#pragma once
#include "Behavior.h"
class Character;
class PursueSteering;
class BehaviorPursue : public Behavior
{
    float m_fMinDistance;
    Character* m_pCharacter;
    Character* m_pOther;
    PursueSteering* m_pPursueSteering;
public:
    BehaviorPursue(Character* _pCharacter, Character* _pOther);
    void onEnter() override;
    void onExit() override;
    Status update() override;
};

