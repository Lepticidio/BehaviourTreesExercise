#include "stdafx.h"
#include "ConditionOtherIsAlive.h"
#include "character.h"
ConditionOtherIsAlive::ConditionOtherIsAlive(Character* _pOther) : m_pOther(_pOther)
{
}
Status ConditionOtherIsAlive::update()
{
	if (m_pOther->GetHealth() > 0)
	{
		return eSuccess;
	}
	else
	{
		return eFail;
	}
}
void ConditionOtherIsAlive::onEnter()
{
}
void ConditionOtherIsAlive::onExit()
{

}