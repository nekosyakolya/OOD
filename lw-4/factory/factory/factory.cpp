#include "stdafx.h"
#include "CCanvas.h"
#include "CDesigner.h"
#include "CPainter.h"
#include "CShapeFactory.h"

#include "CModernCanvas.h"

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

	CPictureDraft pictureDraft = designer.CreateDraft(std::cin);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Canvas", sf::Style::Default, settings);

	CModernCanvas canvas(window);
	CPainter painter;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);

		painter.DrawPicture(pictureDraft, canvas);

		window.display();
	}

	return 0;
}
