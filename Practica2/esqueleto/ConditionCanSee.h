#pragma once
#include "Behavior.h"
class Character;
class ConditionCanSee : public Behavior
{
    float m_fMaxAngle;
    
    Character* m_pCharacter;
    Character* m_pOther;
public:
    ConditionCanSee(Character* _pCharacter, Character* _pOther);
    Status update();
};

