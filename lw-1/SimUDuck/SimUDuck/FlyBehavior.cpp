#include "stdafx.h"
#include "FlyBehavior.h"

void CFlyBehavior::Fly()
{
	std::cout << "Flight number: " << ++m_flightNumber << std::endl;
	FlyBehavior();
}
