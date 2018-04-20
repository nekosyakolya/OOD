#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(const Point& leftTop, const Point& rightBottom, const Color& color)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawLine(m_leftTop, { m_rightBottom.x, m_leftTop.y });
	canvas.DrawLine({ m_rightBottom.x, m_leftTop.y }, m_rightBottom);
	canvas.DrawLine(m_rightBottom, { m_leftTop.x, m_rightBottom.y });
	canvas.DrawLine({ m_leftTop.x, m_rightBottom.y }, m_leftTop);
}

const Point CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

const Point CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}
