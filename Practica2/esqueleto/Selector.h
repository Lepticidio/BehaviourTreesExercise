#pragma once
#include "Group.h"
class Selector : public Group
{
protected:
	void onEnter() override;
	void onExit() override;
	Status  update() override;
	int m_iCurrentChild;
};

