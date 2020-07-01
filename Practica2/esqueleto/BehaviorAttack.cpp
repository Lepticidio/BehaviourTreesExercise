#include "stdafx.h"
#include "BehaviorAttack.h"
#include "character.h"

Status BehaviorAttack::update()
{

	m_fTimePassed += m_pCharacter->GetLastStep();

	if (m_fTimePassed < m_fCooldownTime)
	{
		return eRunning;
	}
	else
	{
		return eSuccess;
	}
}
void BehaviorAttack::onEnter()
{
	m_fTimePassed = 0;
	m_pCharacter->SetImage(3);
	m_pTarget->TakeDamage(m_fDamage);

}
void BehaviorAttack::onExit()
{
	m_fTimePassed = 0;
	m_pCharacter->SetImage(3);

}
BehaviorAttack::BehaviorAttack(Character* _pCharacter, Character* _pTarget) : m_pCharacter(_pCharacter), m_pTarget(_pTarget)
{
}

