#include "stdafx.h"
#include "Sequence.h"
Status Sequence::update()
{
	while (true)
	{
		Status s = m_tChildren[m_iCurrentChild]->tick();
		if (s != eSuccess)
		{
			return s;
		}
		++m_iCurrentChild;
		if (m_iCurrentChild == m_tChildren.size())
		{
			return eSuccess;
		}
	}
	return eInvalid;
}
void Sequence::onEnter()
{
	m_iCurrentChild = 0;
	for (int i = 0; i < m_tChildren.size(); i++)
	{
		m_tChildren[i]->Reset();
	}
}
void Sequence::onExit()
{
	m_iCurrentChild = 0;
	for (int i = 0; i < m_tChildren.size(); i++)
	{
		m_tChildren[i]->Reset();
	}
}