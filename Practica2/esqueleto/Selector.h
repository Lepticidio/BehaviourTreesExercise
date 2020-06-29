#pragma once
#include "Group.h"
class Selector : public Group
{
protected:
	void onEnter();
	Status update();
	int m_iCurrentChild;
};

