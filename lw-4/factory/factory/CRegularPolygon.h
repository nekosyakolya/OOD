#pragma once
#include "CShape.h"
#include "ICanvas.h"
class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(const Point& center, float radius, size_t vertexCount, const Color& color);
	void Draw(ICanvas& canvas) const override;
	const Point GetCenter() const;
	const float GetRadius() const;
	const size_t GetVertexCount() const;

private:
	Point m_center;
	float m_radius;
	size_t m_vertexCount;
	std::vector<Point> GetVertices() const;
};
