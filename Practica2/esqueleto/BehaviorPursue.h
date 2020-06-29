#pragma once
#include "Behavior.h"
class Character;
class PursueSteering;
class BehaviorPursue :
    public Behavior
{
    Character* m_pCharacter;
    PursueSteering* m_pPursueSteering;
public:
    Status update();
};

