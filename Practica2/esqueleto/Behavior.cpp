#include "stdafx.h"
#include "Behavior.h"

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
void Behavior::Reset()
{
	m_eStatus = eInvalid;
}