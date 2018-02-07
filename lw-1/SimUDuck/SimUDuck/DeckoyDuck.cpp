#include "stdafx.h"
#include "DeckoyDuck.h"


CDeckoyDuck::CDeckoyDuck():
	CDuck(std::make_unique<CFlyNoWay>(), std::make_unique<CMuteQuackBehavior>())
{
}
void CDeckoyDuck::Display() const
{
	std::cout << "I'm deckoy duck" << std::endl;
}
