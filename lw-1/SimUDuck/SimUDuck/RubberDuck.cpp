#include "stdafx.h"
#include "RubberDuck.h"


CRubberDuck::CRubberDuck():
	CDuck(std::make_unique<CFlyNoWay>(), std::make_unique<CSqueakBehavior>())
{
}

void CRubberDuck::Display() const
{
	std::cout << "I'm rubber duck" << std::endl;
}

