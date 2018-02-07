#pragma once
#include "IQuackBehavior.h"
class CQuackBehavior :
	public IQuackBehavior
{
public:
	void Quack() override;
};

