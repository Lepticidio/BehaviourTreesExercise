#include "stdafx.h"
#include "BehaviorWindup.h"
#include "character.h"

Status BehaviorWindup::update()
{

	m_fTimePassed += m_pCharacter->GetLastStep();


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
	m_fTimePassed = 0;
	m_pCharacter->SetImage(2);

}
void BehaviorWindup::onExit()
{
	m_fTimePassed = 0;
	m_pCharacter->SetImage(2);

}
BehaviorWindup::BehaviorWindup(Character* _pCharacter) : m_pCharacter(_pCharacter)
{
}
