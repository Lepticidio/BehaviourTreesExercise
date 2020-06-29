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
	return eInvalid;
}