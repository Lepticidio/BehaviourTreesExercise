#include "stdafx.h"
#include "BehaviorPursue.h"
#include "PursueSteering.h"
#include "character.h"

Status BehaviorPursue::update()
{
	
	USVec2D vAcceleration = m_pPursueSteering->GetSteering();
	USVec2D vCurrentVelocity = m_pCharacter->GetLinearVelocity() + vAcceleration * m_pCharacter->GetLastStep();
	m_pCharacter->SetLinearVelocity(vCurrentVelocity.mX, vCurrentVelocity.mY);
	m_pCharacter->SetLoc(m_pCharacter->GetLoc() + m_pCharacter->GetLinearVelocity() * m_pCharacter->GetLastStep());


	float fDistance = (m_pCharacter->GetLoc() - m_pOther->GetLoc()).Length();
	if (fDistance < m_fMinDistance)
	{
		return eSuccess;
	}
	else
	{
		return eRunning;
	}
}
void BehaviorPursue::onEnter()
{
	m_pCharacter->SetImage(1);

}
void BehaviorPursue::onExit()
{
	m_pCharacter->SetImage(1);

}
BehaviorPursue::BehaviorPursue(Character* _pCharacter, Character* _pOther) : m_pCharacter(_pCharacter), m_pOther(_pOther)
{
	m_pPursueSteering = new PursueSteering(m_pCharacter->GetArrive(), _pCharacter);
	m_pPursueSteering->SetTarget(_pOther);
	m_fMinDistance = 32.f;
}