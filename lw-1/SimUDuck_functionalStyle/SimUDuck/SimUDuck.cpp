#include "stdafx.h"

namespace Behavior {
	using Fly = std::function<void()>;
	using Quack = std::function<void()>;
	using Dance = std::function<void()>;
}

namespace FlyBehavior {
	namespace FlightNumber {
		const std::function<void()> calculate = [flightNumber = 0]() mutable {
			std::cout << "Flight number: " << ++flightNumber << std::endl;
		};
	}

	const Behavior::Fly WITH_WINGS = [calculateFlightNumber = FlightNumber::calculate]() {
		calculateFlightNumber();
		std::cout << "I'm flying with wings!!" << std::endl;
	};

	const Behavior::Fly ROCKET_POWERED = [calculateFlightNumber = FlightNumber::calculate]() {
		calculateFlightNumber();
		std::cout << "I'm flying on rocket powered!!" << std::endl;
	};

	const Behavior::Fly NO_WAY = []() {
		std::cout << "Men don't fly" << std::endl;
	};
}

namespace QuackBehavior {
	const Behavior::Quack QUAK = []() {
		std::cout << "Quack Quack!!!" << std::endl;
	};

	const Behavior::Quack SQUEAK = []() {
		std::cout << "Squeek!!!" << std::endl;
	};

	const Behavior::Quack MUTE_QUAK = []() {};
}

namespace DanceBehavior {
	const Behavior::Dance MINUET = []() {
		std::cout << "I'm dancing minuet" << std::endl;
	};

	const Behavior::Dance WALTZ = []() {
		std::cout << "I'm dancing waltz" << std::endl;
	};

	const Behavior::Dance NOT_DANCE = []() {
		std::cout << "Men don't dance" << std::endl;
	};
}


class CDuck
{
public:
	CDuck(const Behavior::Fly &flyBehavior,
		const Behavior::Quack &quackBehavior,
		const Behavior::Dance &danceBehavior):
		m_quackBehavior(quackBehavior),
		m_danceBehavior(danceBehavior)
	{
		SetFlyBehavior(flyBehavior);
	}

	void Quack() const
	{
		m_quackBehavior();
	}

	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}
	
	void Fly() const
	{
		m_flyBehavior();
	}
	
	void Dance() const
	{
		m_danceBehavior();
	}

	void SetFlyBehavior(const Behavior::Fly & flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	virtual void Display() const = 0;
	virtual ~CDuck() = default;

private:
	Behavior::Fly m_flyBehavior;
	Behavior::Quack m_quackBehavior;
	Behavior::Dance m_danceBehavior;
};

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(FlyBehavior::WITH_WINGS,
			QuackBehavior::QUAK,
			DanceBehavior::WALTZ)
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
		: CDuck(FlyBehavior::WITH_WINGS,
			QuackBehavior::QUAK,
			DanceBehavior::MINUET)
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
		: CDuck(FlyBehavior::NO_WAY,
			QuackBehavior::MUTE_QUAK,
			DanceBehavior::NOT_DANCE)
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
		: CDuck(FlyBehavior::NO_WAY,
			QuackBehavior::SQUEAK,
			DanceBehavior::NOT_DANCE)
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
		: CDuck(FlyBehavior::NO_WAY,
			QuackBehavior::QUAK,
			DanceBehavior::NOT_DANCE)
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

	modelDuck.SetFlyBehavior(FlyBehavior::WITH_WINGS);
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyBehavior::ROCKET_POWERED);
	PlayWithDuck(modelDuck);
	PlayWithDuck(mallarDuck);
	PlayWithDuck(mallarDuck);
	PlayWithDuck(modelDuck);

	return EXIT_SUCCESS;
}
