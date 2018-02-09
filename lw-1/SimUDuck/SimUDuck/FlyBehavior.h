#pragma once
#include "IFlyBehavior.h"
class CFlyBehavior :
	public IFlyBehavior
{
public:
	virtual void FlyBehavior() = 0;
	void Fly() override;
	virtual ~CFlyBehavior() = default;
private:
	int m_flightNumber = 0;
};

