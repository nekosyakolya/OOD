#pragma once
#include "CShape.h"
#include "ICanvas.h"
class CRectangle : public CShape
{
public:
	CRectangle(const Point& leftTop, const Point& rightBottom, const Color& color);
	void Draw(ICanvas& canvas) const override;
	const Point GetLeftTop() const;
	const Point GetRightBottom() const;

private:
	Point m_leftTop;
	Point m_rightBottom;
};
