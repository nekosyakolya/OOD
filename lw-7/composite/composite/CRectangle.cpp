#include "stdafx.h"
#include "CRectangle.h"


CRectangle::CRectangle(const RectD & rect, ILineStyle &lineStyle, IStyle &style):
	CShape(rect, lineStyle, style)
{
}

void CRectangle::Draw(ICanvas & canvas)
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

	canvas.MoveTo(m_rect.left, m_rect.top);
	canvas.LineTo(m_rect.left + m_rect.width, m_rect.top);
	canvas.LineTo(m_rect.left + m_rect.width, m_rect.top + m_rect.height);
	canvas.LineTo(m_rect.left, m_rect.top + m_rect.height);
	canvas.LineTo(m_rect.left, m_rect.top);

	if (m_style.IsEnabled())
	{
		canvas.EndFill();
	}
}
