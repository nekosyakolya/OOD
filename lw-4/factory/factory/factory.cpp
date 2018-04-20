#include "stdafx.h"
#include "CCanvas.h"
#include "CDesigner.h"
#include "CPainter.h"
#include "CShapeFactory.h"

static void OutputInfo()
{
	std::cout << "Input Format:" << std::endl;
	std::cout << "rectangle <leftTop.x> <leftTop.y> <rightBottom.x> <rightBottom.y> <color>" << std::endl;
	std::cout << "triangle <first.x> <first.y> <second.x> <second.y> <third.x> <third.y> <color>" << std::endl;
	std::cout << "ellipse <center.x> <center.y> <horizontal radius> <vertical radius> <color>" << std::endl;
	std::cout << "regularPolygon <center.x> <center.y> <radius> <vertex count> <color>" << std::endl;
	std::cout << "<color>:: { red, green, blue, black, pink, yellow }" << std::endl;
}

int main()
{
	OutputInfo();

	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	CCanvas canvas;
	CPainter painter;
	painter.DrawPicture(designer.CreateDraft(std::cin), canvas);

	return 0;
}
