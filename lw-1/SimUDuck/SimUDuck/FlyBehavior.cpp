#include "stdafx.h"
#include "FlyBehavior.h"

void CFlyBehavior::SetFlightNumber(int flightNumber)
{
	m_flightNumber = flightNumber;
}

int CFlyBehavior::GetFlightNumber() const
{
	return m_flightNumber;
}

void CFlyBehavior::Fly()
{
	std::cout << "Flight number: " << ++m_flightNumber << std::endl;
	FlyBehavior();
}
