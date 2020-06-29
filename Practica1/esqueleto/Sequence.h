#pragma once
#include "Group.h"
class Sequence : public Group
{
protected:
	void onEnter();
	Status update();
	int m_iCurrentChild;
};

