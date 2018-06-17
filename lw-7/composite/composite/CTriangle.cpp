#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(const RectD & rect, ILineStyle & lineStyle, IStyle & style):
	CShape(rect, lineStyle, style)
{
}

void CTriangle::Draw(ICanvas & canvas)
{
	if (m_lineStyle.IsEnabled())
	{
		auto lineColor = m_lineStyle.GetColor();
		auto lineThickness = m_lineStyle.GetLineThickness();

		canvas.SetLineColor(lineColor.get());
		canvas.SetLineThickness(lineThickness.get());
	}

	if (m_style.IsEnabled())
	{
		auto color = m_style.GetColor();
		canvas.BeginFill(color.get());
	}

	auto firstPointX = m_rect.left + (m_rect.width / 2.0);

	canvas.MoveTo(firstPointX, m_rect.top);
	canvas.LineTo(m_rect.left + m_rect.width, m_rect.top + m_rect.height);
	canvas.LineTo(m_rect.left, m_rect.top + m_rect.height);
	canvas.LineTo(firstPointX, m_rect.top);

	if (m_style.IsEnabled())
	{
		canvas.EndFill();
	}
}
