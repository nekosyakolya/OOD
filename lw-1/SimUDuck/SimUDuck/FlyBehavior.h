#pragma once
#include "IFlyBehavior.h"
class CFlyBehavior :
	public IFlyBehavior
{
public:
	void Fly() override;
	virtual ~CFlyBehavior() = default;
private:
	virtual void FlyBehavior() = 0;
	int m_flightNumber = 0;
};

