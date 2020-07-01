#include "stdafx.h"
#include "ConditionCanSee.h"
#include "character.h"
ConditionCanSee::ConditionCanSee(Character* _pCharacter, Character* _pOther) : m_pCharacter (_pCharacter), m_pOther(_pOther)
{
	m_fMaxAngle = 90;
}
Status ConditionCanSee::update()
{
	USVec2D vDirEnemy = m_pOther->GetLoc() - m_pCharacter->GetLoc();
	USVec2D vForward = Character::RotateVector(USVec2D(1, 0), m_pCharacter->GetRot());
	if (Character::AngleBetweenVectors(vDirEnemy, vForward) < m_fMaxAngle)
	{
		return eSuccess;
	}
	else
	{
		return eFail;
	}
}
void ConditionCanSee::onEnter()
{
}
void ConditionCanSee::onExit()
{

}