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

enum CoffeePortion
{
	STANDARD,
	DOUBLE
};


// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const CoffeePortion &portion = STANDARD, const std::string& description = " Coffee")
		:m_portion(portion),
		CBeverage(GetFullDescription(description, portion))
	{}
	double GetCost() const override
	{
		return 60;
	}
private:
	std::string GetFullDescription(const std::string& description, const CoffeePortion &portion) const
	{

		std::string result = "";

		switch (portion)
		{
			case DOUBLE:
				result += "Double";
				break;
			default:
				result += "Standart";
				break;
		}
		result += description;

		return result;
	};
protected:
	CoffeePortion m_portion;
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(const CoffeePortion &portion = STANDARD)
		:CCoffee(portion, " Capuccino ")
	{}

	double GetCost() const override
	{
		return (m_portion == STANDARD) ? 80 : 120;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(const CoffeePortion &portion = STANDARD)
		:CCoffee(portion, " Latte ")
	{}

	double GetCost() const override
	{
		return (m_portion == STANDARD) ? 90 : 130;
	}
};



enum GradeTea
{
	CEYLON,
	INDIAN,
	CHINESE,
	AFRICAN
};


// Чай
class CTea : public CBeverage
{
public:
	CTea(const GradeTea &grade = CEYLON)
		:CBeverage(GetFullDescription(grade))
	{}

	double GetCost() const override
	{
		return 30;
	}
private:
	std::string GetFullDescription(const GradeTea &grade) const
	{

		std::string result = "";

		switch (grade)
		{
			case INDIAN:
				result += "Indian";
				break;
			case CHINESE:
				result += "Chinese";
				break;
			case AFRICAN:
				result += "African";
				break;
			default:
				result += "Ceylon";
				break;
		}
		result += " Tea";

		return result;
	};

};


enum MilkshakePortion
{
	SMALL,
	MIDDLE,
	BIG
};


// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(const MilkshakePortion &portion = MIDDLE)
		:m_portion(portion),
		CBeverage(GetFullDescription(portion))
	{}

	double GetCost() const override
	{
		double cost = 0;
		switch (m_portion)
		{
			case SMALL:
				cost = 50;
				break;
			case BIG:
				cost = 80;
				break;
			default:
				cost = 60;
				break;
		}
		return cost;
	}
private:
	MilkshakePortion m_portion;
	std::string GetFullDescription(const MilkshakePortion &portion) const
	{

		std::string result = "";

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
			break;
		}
		result += " Milkshake";

		return result;
	};

};
