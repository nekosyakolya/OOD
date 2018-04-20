#pragma once
#include "CShape.h"
#include "ICanvas.h"

class CEllipse : public CShape
{
public:
	CEllipse(const Point& center, float horizontalRadius, float verticalRadius, const Color& color);
	void Draw(ICanvas& canvas) const override;
	const Point GetCenter() const;
	const float GetHorizontalRadius() const;
	const float GetVerticalRadius() const;

private:
	Point m_center;
	float m_horizontalRadius;
	float m_verticalRadius;
};
