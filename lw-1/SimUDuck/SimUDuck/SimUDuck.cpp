#include "stdafx.h"


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
	CDecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);
	CModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(std::make_unique<CFlyWithWings>());
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(std::make_unique<CFlyRocketPowered>());
	PlayWithDuck(modelDuck);


	return EXIT_SUCCESS;
}

