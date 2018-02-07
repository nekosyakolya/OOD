#pragma once
#include "IQuackBehavior.h"
class CSqueakBehavior :
	public IQuackBehavior
{
public:
	void Quack() override;
};

