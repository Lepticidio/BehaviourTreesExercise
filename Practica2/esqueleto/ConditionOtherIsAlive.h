#pragma once
#include "Behavior.h"
class Character;
class ConditionOtherIsAlive : public Behavior
{
    Character* m_pOther;
public:
    ConditionOtherIsAlive(Character* _pOther);
    Status update() override;
    void onEnter() override;
    void onExit() override;
};

