#include "stdafx.h"
#include "CShape.h"

RectD CShape::GetFrame()
{
	return m_rect;
}

void CShape::SetFrame(const RectD & rect)
{
	m_rect = rect;
}

ILineStyle & CShape::GetOutlineStyle()
{
	return m_lineStyle;
}

const ILineStyle & CShape::GetOutlineStyle() const
{
	return m_lineStyle;
}

void CShape::SetOutlineStyle(const ILineStyle &style)
{
	m_lineStyle = style;
}

IStyle & CShape::GetFillStyle()
{
	return m_style;
}

const IStyle & CShape::GetFillStyle() const
{
	return m_style;
}

void CShape::SetFillStyle(const IStyle &style)
{
	m_style = style;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	throw std::logic_error("Incorrect operation");
}

std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	throw std::logic_error("Incorrect operation");
}
