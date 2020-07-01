#include "stdafx.h"
#include "BehaviorIdle.h"
#include "character.h"
BehaviorIdle::BehaviorIdle()
{

}
BehaviorIdle::BehaviorIdle(Character* _pCharacter) : m_pCharacter(_pCharacter)
{

}
Status BehaviorIdle::update()
{
	return eSuccess;
}
void BehaviorIdle::onEnter()
{
	m_pCharacter->SetImage(0);
	m_pCharacter->SetLinearVelocity(0, 0);
}
void BehaviorIdle::onExit()
{
	m_pCharacter->SetLinearVelocity(0, 0);
}