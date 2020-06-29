#pragma once
enum Status
{
	eInvalid,
	eSuccess,
	eFail,
	eRunning,
};

class Behavior
{
protected:
	Status update();
	void onEnter();
	void onExit();
public:
	Behavior();
	Status tick();
private:
	Status m_eStatus;
};