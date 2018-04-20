#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(const Point& first, const Point& second, const Point& third, const Color& color)
	: CShape(color)
	, m_vertex1(first)
	, m_vertex2(second)
	, m_vertex3(third)
{
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

const Point CTriangle::GetVertex1() const
{
	return m_vertex1;
}

const Point CTriangle::GetVertex2() const
{
	return m_vertex2;
}

const Point CTriangle::GetVertex3() const
{
	return m_vertex3;
}
