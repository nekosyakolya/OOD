#include "stdafx.h"

#include <iostream>
#include <memory>
#include <functional>

namespace {
	using IFlyBehavior = std::function<void()>;
	using IQuackBehavior = std::function<void()>;
	using IDanceBehavior = std::function<void()>;
}

const IFlyBehavior flyBehavior = []() {
	std::cout << "I'm flying with wings!!" << std::endl;
};

const IFlyBehavior flyNoWay = []() {
	std::cout << "Men don't fly" << std::endl;
};

const IQuackBehavior quackBehavior = []() {
	std::cout << "Quack Quack!!!" << std::endl;
};

const IQuackBehavior squeakBehavior = []() {
	std::cout << "Squeek!!!" << std::endl;
};

const IQuackBehavior muteQuackBehavior = []() {};

const IDanceBehavior minuetDanceBehavior = []() {
	std::cout << "I'm dancing minuet" << std::endl;
};

const IDanceBehavior waltzDanceBehavior = []() {
	std::cout << "I'm dancing waltz" << std::endl;
};

const IDanceBehavior notDanceBehavior = []() {
	std::cout << "Men don't dance" << std::endl;
};

class CDuck
{
public:
	CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior) :
		m_quackBehavior(move(quackBehavior)),
		m_danceBehavior(move(danceBehavior))
	{
		SetFlyBehavior(move(flyBehavior));
	}
	void Quack() const
	{
		(*m_quackBehavior)();
	}
	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}
	void Fly() const
	{
		(*m_flyBehavior)();
	}
	void Dance() const
	{
		(*m_danceBehavior)();
	}

	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		m_flyBehavior = move(flyBehavior);
	}
	virtual void Display() const = 0;
	virtual ~CDuck() = default;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(std::make_unique<IFlyBehavior>(flyBehavior),
			std::make_unique<IQuackBehavior>(quackBehavior),
			std::make_unique<IDanceBehavior>(waltzDanceBehavior))
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

class CRedheadDuck : public CDuck
{
public:
	CRedheadDuck()
		: CDuck(std::make_unique<IFlyBehavior>(flyBehavior),
			std::make_unique<IQuackBehavior>(quackBehavior),
			std::make_unique<IDanceBehavior>(minuetDanceBehavior))
	{
	}
	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};
class CDecoyDuck : public CDuck
{
public:
	CDecoyDuck()
		: CDuck(std::make_unique<IFlyBehavior>(flyNoWay),
			std::make_unique<IQuackBehavior>(muteQuackBehavior),
			std::make_unique<IDanceBehavior>(notDanceBehavior))
	{
	}
	void Display() const override
	{
		std::cout << "I'm deckoy duck" << std::endl;
	}
};
class CRubberDuck : public CDuck
{
public:
	CRubberDuck()
		: CDuck(std::make_unique<IFlyBehavior>(flyNoWay),
			std::make_unique<IQuackBehavior>(squeakBehavior),
			std::make_unique<IDanceBehavior>(notDanceBehavior))
	{
	}
	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};

class CModelDuck : public CDuck
{
public:
	CModelDuck()
		: CDuck(std::make_unique<IFlyBehavior>(flyNoWay),
			std::make_unique<IQuackBehavior>(quackBehavior),
			std::make_unique<IDanceBehavior>(notDanceBehavior))
	{
	}
	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};

void DrawDuck(CDuck const& duck)
{
	duck.Display();
}

void PlayWithDuck(CDuck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	std::cout << std::endl;
}

int main()
{
	CMallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);
	CRedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	CRubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	CDecoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	CModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(std::make_unique<IFlyBehavior>(flyBehavior));
	PlayWithDuck(modelDuck);

	return EXIT_SUCCESS;
}
