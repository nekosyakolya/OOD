#include "stdafx.h"
#include "CModernCanvas.h"

CModernCanvas::CModernCanvas(sf::RenderTarget& window)
	: m_target(window)
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
	sf::VertexArray line = CreateLine(from, to);
	m_target.draw(line);
}

void CModernCanvas::DrawEllipse(float left, float top, float width, float height)
{

	sf::CircleShape ellipse = CreateEllipse(left, top, width, height);
	m_target.draw(ellipse);
}

sf::Vertex CModernCanvas::CreateVertex(const Point& point) const
{
	sf::Vertex result;
	result.position = sf::Vector2f(point.x, point.y);
	result.color = m_color;
	return result;
}

sf::VertexArray CModernCanvas::CreateLine(const Point& from, const Point& to) const
{
	sf::VertexArray line(sf::Lines, 2);
	line[0] = CreateVertex(from);
	line[1] = CreateVertex(to);
	return line;
}

sf::CircleShape CModernCanvas::CreateEllipse(float left, float top, float width, float height) const
{

	float horizontalRadius = width / 2.f;
	float verticalRadius = height / 2.f;

	sf::CircleShape ellipse(horizontalRadius);
	ellipse.setOutlineColor(m_color);
	ellipse.setOutlineThickness(1);
	ellipse.setScale(1.f, verticalRadius / horizontalRadius);

	ellipse.setPosition(left, top);
	return ellipse;
}
