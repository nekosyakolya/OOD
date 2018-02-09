#pragma once
#include "IFlyBehavior.h"
class CFlyNoWay :
	public IFlyBehavior
{
public:
	void Fly() override;
};
