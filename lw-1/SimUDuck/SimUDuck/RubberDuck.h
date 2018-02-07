#pragma once
#include "Duck.h"
class CRubberDuck :
	public CDuck
{
public:
	CRubberDuck();
	void Display() const override;
};

