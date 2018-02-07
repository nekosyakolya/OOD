#pragma once
#include "IFlyBehavior.h"
class CFlyWithWings :
	public IFlyBehavior
{
public:
	void Fly() override;
};

