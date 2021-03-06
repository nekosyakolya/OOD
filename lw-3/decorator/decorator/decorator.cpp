﻿#include "stdafx.h"
#include "Beverages.h"
#include "Condiments.h"

#include <iostream>
#include <string>
#include <functional>

using namespace std;


/*
Функциональный объект, создающий лимонную добавку
*/
struct MakeLemon
{
	MakeLemon(unsigned quantity)
		:m_quantity(quantity)
	{}

	auto operator()(IBeveragePtr && beverage)const
	{
		return make_unique<CLemon>(move(beverage), m_quantity);
	}
private:
	unsigned m_quantity;
};

/*
Функция, возвращающая функцию, создающую коричную добавку
*/
function<IBeveragePtr(IBeveragePtr &&)> MakeCinnamon()
{
	return [](IBeveragePtr && b) {
		return make_unique<CCinnamon>(move(b));
	};
}

/*
Возвращает функцию, декорирующую напиток определенной добавкой

Параметры шаблона:
Condiment - класс добавки, конструктор которого в качестве первого аргумента
принимает IBeveragePtr&& оборачиваемого напитка
Args - список типов прочих параметров конструктора (возможно, пустой)
*/
template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&...args)
{
	// Возвращаем функцию, декорирующую напиток, переданный ей в качестве аргумента
	// Дополнительные аргументы декоратора, захваченные лямбда-функцией, передаются
	// конструктору декоратора через make_unique
	return [=](auto && b) {
		// Функции make_unique передаем b вместе со списком аргументов внешней функции
		return make_unique<Condiment>(forward<decltype(b)>(b), args...);
	};
}

/*
Перегруженная версия оператора <<, которая предоставляет нам синтаксический сахар
для декорирования компонента

Позволяет создать цепочку оборачивающих напиток декораторов следующим образом:
auto beverage = make_unique<CConcreteBeverage>(a, b, c)
<< MakeCondimentA(d, e, f)
<< MakeCondimentB(g, h);

Функциональные объекты MakeCondiment* запоминают аргументы, необходимые для создания
дополнения, и возвращают фабричную функцию, принимающую оборачиваемый напиток, которая
при своем вызове создаст нужный объект Condiment, передав ему запомненные аргументы.
Использование:
auto beverage =
make_unique<CConcreteBeverage>(a, b, c)
<< MakeCondimentA(d, e, f)
<< MakeCondimentB(g, h);
или даже так:
auto beverage =
make_unique<CConcreteBeverage>
<< MakeCondiment<CondimentA>(d, e, f)
<< MakeCondiment<CondimentB>(g, h);
В последнем случае нет необходимости писать вручную реализации MakeCondimentA и MakeCondimentB, т.к.
необходимую реализацию сгенерирует компилятор

Классический способ оборачивания выглядел бы так:
auto baseBeverage = make_unique<CConcretedBeverage>(a, b, c);
auto wrappedWithCondimentA = make_unique<CCondimentA>(move(baseBeverage), d, e, f);
auto beverage = make_unique<CCondimentB>(move(wrappedWithCondimentA), g, h);
либо так:
auto beverage = make_unique<CCondimentB>(
make_unique<CCondimentA>(
make_unique<CConcreteBeverage>(a, b, c), // Напиток
d, e, f	// доп. параметы CondimentA
),
g, h		// доп. параметры CondimentB
);

unique_ptr<CLemon> operator << (IBeveragePtr && lhs, const MakeLemon & factory)
{
return factory(move(lhs));
}
unique_ptr<CCinnamon> operator << (IBeveragePtr && lhs, const MakeCinnamon & factory)
{
return factory(move(lhs));
}
*/
template <typename Component, typename Decorator>
auto operator << (Component && component, const Decorator & decorate)
{
	return decorate(forward<Component>(component));
}

unique_ptr<IBeverage> CreateTea()
{
	cout << "You selected a Ceylon tea\n";
	cout << "Type 1 for Indian or 2 for Chinese or 3 for African\n";
	int gradeChoice;
	cin >> gradeChoice;
	unique_ptr<IBeverage> tea = make_unique<CTea>();
	
	if (gradeChoice == 1)
	{
		tea = make_unique<CTea>(Tea::INDIAN);
	}
	else if (gradeChoice == 2)
	{
		tea = make_unique<CTea>(Tea::CHINESE);
	}
	else if (gradeChoice == 3)
	{
		tea = make_unique<CTea>(Tea::AFRICAN);
	}

	return tea;
}

unique_ptr<IBeverage> CreateMilkshake()
{

	cout << "You selected a middle milkshake\n";
	cout << "Type 1 for small or 2 for big\n";
	int portion;
	cin >> portion;
	unique_ptr<IBeverage> milkshake = make_unique<CMilkshake>();

	if (portion == 1)
	{
		milkshake = make_unique<CMilkshake>(Milkshake::SMALL);
	}
	else if (portion == 2)
	{
		milkshake = make_unique<CMilkshake>(Milkshake::BIG);
	}

	return milkshake;
}

unique_ptr<IBeverage> CreateLatte()
{
	cout << "You selected a standard latte\n";
	cout << "Type 1 for double\n";
	int portion;
	cin >> portion;
	unique_ptr<IBeverage> latte = make_unique<CLatte>();

	if (portion == 1)
	{
		latte = make_unique<CLatte>(Coffee::DOUBLE);
	}

	return latte;
}


unique_ptr<IBeverage> CreateCappuchino()
{
	cout << "You selected a standard cappuchino\n";
	cout << "Type 1 for double\n";
	int portion;
	cin >> portion;
	unique_ptr<IBeverage> capuccino = make_unique<CCapuccino>();

	if (portion == 1)
	{
		capuccino = make_unique<CCapuccino>(Coffee::DOUBLE);
	}

	return capuccino;
}

void DialogWithUser()
{
	cout << "Type 1 for coffee or 2 for tea or 3 for milkshake or 4 for latte or 5 for capuccino\n";
	int beverageChoice;
	cin >> beverageChoice;

	unique_ptr<IBeverage> beverage;

	if (beverageChoice == 1)
	{
		beverage = make_unique<CCoffee>();
	}
	else if (beverageChoice == 2)
	{
		beverage = CreateTea();
	}
	else if (beverageChoice == 3)
	{
		beverage = CreateMilkshake();
	}
	else if (beverageChoice == 4)
	{
		beverage = CreateLatte();
	}
	else if (beverageChoice == 5)
	{
		beverage = CreateCappuchino();
	}
	else
	{
		return;
	}

	int condimentChoice;
	if (beverageChoice == 2)
	{
		for (;;)
		{
			cout << "1 - Lemon, 2 - Chocolate, 3 - Nut liquor, 4 - Chocolate liquor, 0 - Checkout" << endl;
			cin >> condimentChoice;

			if (condimentChoice == 1)
			{
				//beverage = make_unique<CLemon>(move(beverage));
				beverage = move(beverage) << MakeCondiment<CLemon>(2);
			}
			else if (condimentChoice == 2)
			{
				//beverage = make_unique<CChocolate>(move(beverage));
				beverage = move(beverage) << MakeCondiment<CChocolate>(5);
			}
			else if (condimentChoice == 3)
			{
				beverage = move(beverage) << MakeCondiment<CLiquor>(LiquorType::NUT);
			}
			else if (condimentChoice == 4)
			{
				beverage = move(beverage) << MakeCondiment<CLiquor>(LiquorType::CHOCOLATE);
			}
			else if (condimentChoice == 0)
			{
				break;
			}
			else
			{
				return;
			}
		}
	}

	if (beverageChoice == 1 || beverageChoice == 4 || beverageChoice == 5)
	{
		for (;;)
		{
			cout << "1-Cinnamon, 2-Chocolate, 3-Nut liquor, 4-Chocolate liquor, 5-Cream, 0 - Checkout" << endl;
			cin >> condimentChoice;

			if (condimentChoice == 1)
			{
				beverage = move(beverage) << MakeCondiment<CCinnamon>();
			}
			else if (condimentChoice == 2)
			{
				//beverage = make_unique<CChocolate>(move(beverage));
				beverage = move(beverage) << MakeCondiment<CChocolate>(5);
			}
			else if (condimentChoice == 3)
			{
				beverage = move(beverage) << MakeCondiment<CLiquor>(LiquorType::NUT);
			}
			else if (condimentChoice == 4)
			{
				beverage = move(beverage) << MakeCondiment<CLiquor>(LiquorType::CHOCOLATE);
			}
			else if (condimentChoice == 5)
			{
				beverage = move(beverage) << MakeCondiment<CCream>();
			}
			else if (condimentChoice == 0)
			{
				break;
			}
			else
			{
				return;
			}
		}
	}

	if (beverageChoice == 3)
	{
		for (;;)
		{
			cout << "1-Chocolate, 2-Chocolate syrup, 3-Maple syrup, 0 - Checkout" << endl;
			cin >> condimentChoice;

			if (condimentChoice == 1)
			{
				beverage = move(beverage) << MakeCondiment<CChocolate>(5);
			}
			else if (condimentChoice == 2)
			{
				beverage = move(beverage) << MakeCondiment<CSyrup>(SyrupType::Chocolate);
			}
			else if (condimentChoice == 3)
			{
				beverage = move(beverage) << MakeCondiment<CSyrup>(SyrupType::Maple);
			}
			else if (condimentChoice == 0)
			{
				break;
			}
			else
			{
				return;
			}
		}
	}

	cout << beverage->GetDescription() << ", cost: " << beverage->GetCost() << endl;
}


int main()
{
	DialogWithUser();


	//cout << endl;
	//{
	//	// Наливаем чашечку латте
	//	auto latte = make_unique<CLatte>();
	//	// добавляем корицы
	//	auto cinnamon = make_unique<CCinnamon>(move(latte));
	//	// добавляем пару долек лимона
	//	auto lemon = make_unique<CLemon>(move(cinnamon), 2);
	//	// добавляем пару кубиков льда
	//	auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
	//	// добавляем 2 грамма шоколадной крошки
	//	auto beverage = make_unique<CChocolateCrumbs>(move(iceCubes), 2);

	//	// Выписываем счет покупателю
	//	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	//}

	//{
	//	auto beverage =
	//		make_unique<CChocolateCrumbs>(			// Внешний слой: шоколадная крошка
	//			make_unique<CIceCubes>(				// | под нею - кубики льда
	//				make_unique<CLemon>(			// | | еще ниже лимон
	//					make_unique<CCinnamon>(		// | | | слоем ниже - корица
	//						make_unique<CLatte>()),	// | | |   в самом сердце - Латте
	//					2),							// | | 2 дольки лимона
	//				2, IceCubeType::Dry),			// | 2 кубика сухого льда
	//			2);									// 2 грамма шоколадной крошки

	//												// Выписываем счет покупателю
	//	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	//}

	//// Подробнее рассмотрим работу MakeCondiment и оператора <<
	//{
	//	// lemon - функция, добавляющая "2 дольки лимона" к любому напитку
	//	auto lemon2 = MakeCondiment<CLemon>(2);
	//	// iceCubes - функция, добавляющая "3 кусочка льда" к любому напитку
	//	auto iceCubes3 = MakeCondiment<CIceCubes>(3, IceCubeType::Water);

	//	auto tea = make_unique<CTea>();

	//	// декорируем чай двумя дольками лимона и тремя кусочками льда
	//	auto lemonIceTea = iceCubes3(lemon2(move(tea)));
	//	/* Предыдущая строка выполняет те же действия, что и следующий код:
	//	auto lemonIceTea =
	//	make_unique<CIceCubes>(
	//	make_unique<CLemon>(
	//	move(tea),
	//	2),
	//	2, IceCubeType::Water);
	//	*/

	//	auto oneMoreLemonIceTea =
	//		make_unique<CTea>()	// Берем чай
	//		<< MakeCondiment<CLemon>(2)	// добавляем пару долек лимона
	//		<< MakeCondiment<CIceCubes>(3, IceCubeType::Water); // и 3 кубика льда
	//															/*
	//															Предыдущая конструкция делает то же самое, что и следующая:
	//															auto oneMoreLemonIceTea =
	//															MakeCondiment<CIceCubes>(3, IceCubeType::Water)(
	//															MakeCondiment<CLemon>(2)(make_unique<CTea>())
	//															);
	//															*/
	//}

	//// Аналог предыдущего решения с добавкой синтаксического сахара
	//// обеспечиваемого операторами << и функцией MakeCondiment
	//{
	//	auto beverage =
	//		make_unique<CLatte>()							// Наливаем чашечку латте,
	//		<< MakeCondiment<CCinnamon>()					// оборачиваем корицей,
	//		<< MakeCondiment<CLemon>(2)						// добавляем пару долек лимона
	//		<< MakeCondiment<CIceCubes>(2, IceCubeType::Dry)// брасаем пару кубиков сухого льда
	//		<< MakeCondiment<CChocolateCrumbs>(2);			// посыпаем шоколадной крошкой

	//														// Выписываем счет покупателю
	//	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	//}

	//{
	//	auto beverage =
	//		make_unique<CMilkshake>()					// Наливаем молочный коктейль
	//		<< MakeCondiment<CSyrup>(SyrupType::Maple)	// заливаем кленовым сиропом
	//		<< MakeCondiment<CCoconutFlakes>(8);		// посыпаем кокосовой стружкой

	//													// Выписываем счет покупателю
	//	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;
	//}
}
