#include "stdafx.h"
#include "Duck.h"


CDuck::CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior,
	std::unique_ptr<IQuackBehavior>&& quackBehavior):
	m_quackBehavior(move(quackBehavior))
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

void CDuck::SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
{
	m_flyBehavior = move(flyBehavior);
}

