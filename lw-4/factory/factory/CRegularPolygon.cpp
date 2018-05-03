#include "stdafx.h"
#include "CRegularPolygon.h"

CRegularPolygon::CRegularPolygon(const Point& center, float radius, size_t vertexCount, const Color& color)
	: CShape(color)
	, m_center(center)
	, m_radius(radius)
	, m_vertexCount(vertexCount)
{
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);

	std::vector<Point> vertices = GetVertices();
	canvas.DrawLine(vertices.front(), vertices.back());

	for (size_t i = vertices.size() - 1; i != 0; --i)
	{
		canvas.DrawLine(vertices[i], vertices[i - 1]);
	}
}

const Point CRegularPolygon::GetCenter() const
{
	return m_center;
}

const float CRegularPolygon::GetRadius() const
{
	return m_radius;
}

const size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

std::vector<Point> CRegularPolygon::GetVertices() const
{
	std::vector<Point> result;
	const float STEP = 360.0f / m_vertexCount;

	for (float angle = 0; angle != 360.0f; angle += STEP)
	{
		Point vertex;
		float radians = static_cast<float>(angle * M_PI / 180.0f);
		vertex.x = m_center.x + m_radius * cos(radians);
		vertex.y = m_center.y + m_radius * sin(radians);

		result.emplace_back(vertex);
	}

	return result;
}
