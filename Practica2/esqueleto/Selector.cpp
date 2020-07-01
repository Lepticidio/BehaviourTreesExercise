#include "stdafx.h"
#include "Selector.h"

Status Selector::update()
{
	while (true)
	{
		Status s = m_tChildren[m_iCurrentChild]->tick();
		if (s != eFail)
		{
			return s;
		}
		++m_iCurrentChild;
		if (m_iCurrentChild == m_tChildren.size())
		{
			return eFail;
		}
	} 
	return eInvalid;
}
void Selector::onEnter()
{
	m_iCurrentChild = 0;
	for (int i = 0; i < m_tChildren.size(); i++)
	{
		m_tChildren[i]->Reset();
	}
}
void Selector::onExit()
{
	m_iCurrentChild = 0;
	for (int i = 0; i < m_tChildren.size(); i++)
	{
		m_tChildren[i]->Reset();
	}
}