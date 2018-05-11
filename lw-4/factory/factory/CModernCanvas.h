#pragma once
#include "Color.h"

#include "ICanvas.h"
class CModernCanvas : public ICanvas
{
public:
	CModernCanvas(sf::RenderTarget&);
	void SetColor(const Color& color) override;
	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(float left, float top, float width, float height) override;

private:
	sf::RenderTarget& m_target;
	sf::Color m_color;
	const std::unordered_map<Color, sf::Color> COLORS = { { Color::BLACK, sf::Color::Black },
		{ Color::BLUE, sf::Color::Blue },
		{ Color::GREEN, sf::Color::Green },
		{ Color::PINK, sf::Color(255, 105, 180) },
		{ Color::RED, sf::Color::Red },
		{ Color::YELLOW, sf::Color::Yellow } };
	sf::Vertex CreateVertex(const Point& point) const;
	sf::VertexArray CreateLine(const Point& from, const Point& to) const;
	sf::CircleShape CreateEllipse(float left, float top, float width, float height) const;
};
