#include "stdafx.h"
#include "ModelDuck.h"


CModelDuck::CModelDuck():
	CDuck(std::make_unique<CFlyNoWay>(),
		std::make_unique<CQuackBehavior>(),
		std::make_unique<CNotDanceBehavior>())
{
}

void CModelDuck::Display() const
{
	std::cout << "I'm model duck" << std::endl;
}


