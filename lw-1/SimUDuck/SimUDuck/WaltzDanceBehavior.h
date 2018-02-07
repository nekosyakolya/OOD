#pragma once
#include "IDanceBehavior.h"
class CWaltzDanceBehavior :
	public IDanceBehavior
{
public:
	void Dance() override;
};