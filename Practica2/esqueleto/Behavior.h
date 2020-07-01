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
	virtual Status update() = 0;
	virtual void onEnter() = 0;
	virtual void onExit() = 0;
public:
	Status tick();
private:
	Status m_eStatus;
public:
	void Reset();
};