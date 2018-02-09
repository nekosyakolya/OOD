#include "stdafx.h"
#include "DecoyDuck.h"


CDecoyDuck::CDecoyDuck():
	CDuck(std::make_unique<CFlyNoWay>(),
		std::make_unique<CMuteQuackBehavior>(),
		std::make_unique<CNotDanceBehavior>())
{
}
void CDecoyDuck::Display() const
{
	std::cout << "I'm deckoy duck" << std::endl;
}

