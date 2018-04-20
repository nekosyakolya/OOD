#include "stdafx.h"
#include "CCanvas.h"

CCanvas::CCanvas()
{
}

void CCanvas::SetColor(const Color& color)
{
	m_color = color;

	std::cout << "Color: " << m_color << std::endl;
}

void CCanvas::DrawLine(const Point& from, const Point& to)
{
	std::cout << "From (" << from.x << ", " << from.y << ")" << std::endl;
	std::cout << "To (" << to.x << ", " << to.y << ")" << std::endl;
}

void CCanvas::DrawEllipse(float left, float top, float width, float height)
{
	std::cout << "Left top (" << left << ", " << top << ")" << std::endl;
	std::cout << "width:" << width << std::endl;
	std::cout << "height:" << height << std::endl;
}
