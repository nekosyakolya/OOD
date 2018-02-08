#include "stdafx.h"
#include "Duck.h"


CDuck::CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior,
	std::unique_ptr<IQuackBehavior>&& quackBehavior,
	std::unique_ptr<IDanceBehavior>&& danceBehavior):
	m_quackBehavior(move(quackBehavior)),
	m_danceBehavior(move(danceBehavior))
{
	SetFlyBehavior(move(flyBehavior));
}

void CDuck::Swim()
{
	std::cout << "I'm swimming" << std::endl;
}

void CDuck::Fly() const
{
	m_flyBehavior->Fly();
}

void CDuck::Quack() const
{
	m_quackBehavior->Quack();
}

void CDuck::Dance() const
{
	m_danceBehavior->Dance();
}

void CDuck::SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
{
	int currentFlightNumber = (m_flyBehavior) ? m_flyBehavior->GetFlightNumber() : 0;
	m_flyBehavior = move(flyBehavior);
	m_flyBehavior->SetFlightNumber(currentFlightNumber);
}

