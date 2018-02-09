#pragma once
#include "Duck.h"
class CDecoyDuck :
	public CDuck
{
public:
	CDecoyDuck();
	void Display() const override;
};

