#pragma once
#include "IDanceBehavior.h"
class CNotDanceBehavior :
	public IDanceBehavior
{
public:
	void Dance() override;
};

