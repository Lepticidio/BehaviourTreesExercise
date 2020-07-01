#include "stdafx.h"
#include "Group.h"
void Group::AddBehavior(Behavior* _pBehavior)
{
	m_tChildren.push_back(_pBehavior);
}