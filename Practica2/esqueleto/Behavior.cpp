#include "stdafx.h"
#include "Behavior.h"
Behavior::Behavior()
{
}

Status Behavior::tick()
{
	if (m_eStatus == eInvalid)
	{
		onEnter();
	}
	m_eStatus = update();
	if (m_eStatus != eRunning)
	{
		onExit();
	}
	return m_eStatus;
}
void Behavior::onEnter()
{

}
void Behavior::onExit()
{

}
Status Behavior::update()
{
	return eInvalid;
}