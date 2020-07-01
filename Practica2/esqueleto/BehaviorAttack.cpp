#include "stdafx.h"
#include "BehaviorAttack.h"
#include "PursueSteering.h"
#include "character.h"

Status BehaviorAttack::update()
{
	m_fTimePassed += m_pCharacter->GetLastStep();
	USVec2D vAcceleration = m_pPursueSteering->GetSteering();
	USVec2D vCurrentVelocity = m_pCharacter->GetLinearVelocity() + vAcceleration * m_pCharacter->GetLastStep();
	m_pCharacter->SetLinearVelocity(vCurrentVelocity.mX, vCurrentVelocity.mY);
	m_pCharacter->SetLoc(m_pCharacter->GetLoc() + m_pCharacter->GetLinearVelocity() * m_pCharacter->GetLastStep());

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
	m_pPursueSteering = new PursueSteering(m_pCharacter->GetArrive(), _pCharacter);
	m_pPursueSteering->SetTarget(_pTarget);
}

