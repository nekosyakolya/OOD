#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};


namespace Coffee
{
	enum Portion
	{
		STANDARD,
		DOUBLE
	};

	const auto toString = [](const Portion & portion) {
		static const std::string names[] = { "Standart", "Double" };
		return names[portion];
	};
}


// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const Coffee::Portion &portion = Coffee::STANDARD, const std::string& description = " Coffee")
		:m_portion(portion),
		CBeverage(Coffee::toString(portion) + description)
	{}
	double GetCost() const override
	{
		return 60;
	}
protected:
	Coffee::Portion m_portion;
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(const Coffee::Portion &portion = Coffee::STANDARD)
		:CCoffee(portion, " Capuccino ")
	{}

	double GetCost() const override
	{
		return (m_portion == Coffee::STANDARD) ? 80 : 120;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(const Coffee::Portion &portion = Coffee::STANDARD)
		:CCoffee(portion, " Latte ")
	{}

	double GetCost() const override
	{
		return (m_portion == Coffee::STANDARD) ? 90 : 130;
	}
};


namespace Tea
{
	enum Grade
	{
		CEYLON,
		INDIAN,
		CHINESE,
		AFRICAN
	};
	const auto toString = [](const Grade & grade) {
		static const std::string names[] = { "Ceylon", "Indian", "Chinese", "African" };
		return names[grade];
	};
}

// Чай
class CTea : public CBeverage
{
public:
	using GradeTea = Tea::Grade;

	CTea(const GradeTea &grade = GradeTea::CEYLON)
		:CBeverage(Tea::toString(grade) + " tea")
	{}

	double GetCost() const override
	{
		return 30;
	}
};

namespace Milkshake {
	enum Portion
	{
		SMALL,
		MIDDLE,
		BIG
	};

	const auto toString = [](const Portion & portion) {
		static const std::string names[] = {"Small", "Middle", "Big"};
		return names[portion];
	};


	const auto getCost = [](const Portion & portion) {
		static const double cost[] = {50, 60, 80};
		return cost[portion];
	};

}


// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	using MilkshakePortion = Milkshake::Portion;

	CMilkshake(const MilkshakePortion &portion = MilkshakePortion::MIDDLE)
		:m_portion(portion),
		CBeverage(Milkshake::toString(portion) + " milkshake")
	{}

	double GetCost() const override
	{
		return Milkshake::getCost(m_portion);
	}
private:
	Milkshake::Portion m_portion;
};
