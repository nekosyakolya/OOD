#pragma once
#include "CShape.h"
class CTriangle : public CShape
{
public:
	CTriangle(const Point& first, const Point& second, const Point& third, const Color& color);
	void Draw(ICanvas& canvas) const override;
	const Point GetVertex1() const;
	const Point GetVertex2() const;
	const Point GetVertex3() const;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};
