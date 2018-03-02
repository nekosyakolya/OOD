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

	inline const std::string ToString(const Portion & portion) {
		std::string result;
		switch (portion)
		{
		case DOUBLE:
			result = "Double";
			break;
		default:
			result = "Standart";
		}
		return result;

	};
}




// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const Coffee::Portion &portion = Coffee::STANDARD, const std::string& description = " Coffee")
		:m_portion(portion),
		CBeverage(Coffee::ToString(portion) + description)
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
	inline const std::string ToString(const Grade & grade) {
		std::string result;
		switch (grade)
		{
			case AFRICAN:
				result = "African";
				break;
			case INDIAN:
				result = "Indian";
				break;
			case CHINESE:
				result = "Chinese";
				break;
			default:
				result = "Ceylon";
		}
		return result;
	};
}

// Чай
class CTea : public CBeverage
{
public:
	using GradeTea = Tea::Grade;

	CTea(const GradeTea &grade = GradeTea::CEYLON)
		:CBeverage(Tea::ToString(grade) + " tea")
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

	inline const std::string ToString(const Portion & portion) {
		std::string result;
		switch (portion)
		{
			case SMALL:
				result = "Small";
				break;
			case BIG:
				result = "Big";
				break;
			default:
				result = "Middle";
		}
		return result;
	};


	inline const double GetCost(const Portion & portion) {
		double cost;
		switch (portion)
		{
			case SMALL:
				cost = 50;
				break;
			case BIG:
				cost = 80;
				break;
			default:
				cost = 60;
		}
		return cost;
	};

}


// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	using MilkshakePortion = Milkshake::Portion;

	CMilkshake(const MilkshakePortion &portion = MilkshakePortion::MIDDLE)
		:m_portion(portion),
		CBeverage(Milkshake::ToString(portion) + " milkshake")
	{}

	double GetCost() const override
	{
		return Milkshake::GetCost(m_portion);
	}
private:
	Milkshake::Portion m_portion;
};
