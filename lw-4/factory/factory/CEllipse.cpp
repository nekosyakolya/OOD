#include "stdafx.h"
#include "CEllipse.h"

CEllipse::CEllipse(const Point& center, float horizontalRadius, float verticalRadius, const Color& color)
	: CShape(color)
	, m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

void CEllipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawEllipse(m_center.x - m_horizontalRadius, m_center.y - m_verticalRadius, m_horizontalRadius * 2.f, m_verticalRadius * 2.f);
}

const Point CEllipse::GetCenter() const
{
	return m_center;
}

const float CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

const float CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}
