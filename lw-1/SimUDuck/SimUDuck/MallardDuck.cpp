#include "stdafx.h"
#include "MallardDuck.h"


CMallardDuck::CMallardDuck() :
	CDuck(std::make_unique<CFlyWithWings>(),
		std::make_unique<CQuackBehavior>(),
		std::make_unique<CWaltzDanceBehavior>())
{
}

void CMallardDuck::Display() const
{
	std::cout << "I'm mallard duck" << std::endl;
}
