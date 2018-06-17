#include "stdafx.h"
#include "CDrawingVisitor.h"

void CDrawingVisitor::Visit(CBoat & boat)
{
	std::cout << "Draw a boat" << std::endl;
}

void CDrawingVisitor::Visit(CCar & car)
{
	std::cout << "Draw a car" << std::endl;
}

void CDrawingVisitor::Visit(CBus & bus)
{
	std::cout << "Draw a bus" << std::endl;
}

void CDrawingVisitor::Visit(CPlane & plane)
{
	std::cout << "Draw a plane" <<  std::endl;
}
