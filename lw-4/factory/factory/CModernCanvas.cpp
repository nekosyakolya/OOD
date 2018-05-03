#include "stdafx.h"
#include "CModernCanvas.h"

CModernCanvas::CModernCanvas(sf::RenderWindow& window)
	: m_window(window)
	, m_color(sf::Color::Black)
{
}

void CModernCanvas::SetColor(const Color& color)
{
	auto result = COLORS.find(color);
	m_color = result->second;
}

void CModernCanvas::DrawLine(const Point& from, const Point& to)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = sf::Vector2f(from.x, from.y);
	line[0].color = m_color;
	line[1].position = sf::Vector2f(to.x, to.y);
	line[1].color = m_color;
	m_window.draw(line);
}

void CModernCanvas::DrawEllipse(float left, float top, float width, float height)
{

	float horizontalRadius = width / 2.f;
	float verticalRadius = height / 2.f;

	sf::CircleShape ellipse(horizontalRadius);
	ellipse.setOutlineColor(m_color);
	ellipse.setOutlineThickness(1);
	ellipse.setScale(1.f, verticalRadius / horizontalRadius);

	ellipse.setPosition(left, top);

	m_window.draw(ellipse);
}
