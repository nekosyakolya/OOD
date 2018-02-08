#pragma once
#include "IFlyBehavior.h"
class CFlyBehavior :
	public IFlyBehavior
{
public:
	void SetFlightNumber(int) override;
	int GetFlightNumber() const override;
	virtual void FlyBehavior() = 0;
	void Fly() override;
private:
	int m_flightNumber = 0;
};

