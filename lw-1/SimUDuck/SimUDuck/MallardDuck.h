#pragma once
#include "Duck.h"
class CMallardDuck :
	public CDuck
{
public:
	CMallardDuck();
	void Display() const override;
};

