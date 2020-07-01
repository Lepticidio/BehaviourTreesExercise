#pragma once
#include "Group.h"
class Sequence : public Group
{
protected:
	void onEnter() override;
	void onExit() override;
	Status update() override;
	int m_iCurrentChild;
};

