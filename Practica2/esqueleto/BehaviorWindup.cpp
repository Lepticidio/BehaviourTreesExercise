#include "stdafx.h"
#include "BehaviorWindup.h"
#include "PursueSteering.h"
#include "character.h"

Status BehaviorWindup::update()
{

	m_fTimePassed += m_pCharacter->GetLastStep();

	USVec2D vAcceleration = m_pPursueSteering->GetSteering();
	USVec2D vCurrentVelocity = m_pCharacter->GetLinearVelocity() + vAcceleration * m_pCharacter->GetLastStep();
	m_pCharacter->SetLinearVelocity(vCurrentVelocity.mX, vCurrentVelocity.mY);
	m_pCharacter->SetLoc(m_pCharacter->GetLoc() + m_pCharacter->GetLinearVelocity() * m_pCharacter->GetLastStep());

	if (m_fTimePassed < m_fWindupTime)
	{
		return eRunning;
	}
	else
	{
		return eSuccess;
	}
}
void BehaviorWindup::onEnter()
{
	m_pCharacter->SetImage(2);

}
void BehaviorWindup::onExit()
{
	m_pCharacter->SetImage(2);

}
BehaviorWindup::BehaviorWindup(Character* _pCharacter, Character* _pOther) : m_pCharacter(_pCharacter)
{
	m_pPursueSteering = new PursueSteering(m_pCharacter->GetArrive(), _pCharacter);
	m_pPursueSteering->SetTarget(_pOther);
}
