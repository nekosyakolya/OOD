#include "stdafx.h"
#include "CEllipse.h"

CEllipse::CEllipse(const RectD & rect, ILineStyle & lineStyle, IStyle & style):
	CShape(rect, lineStyle, style)
{
}

void CEllipse::Draw(ICanvas & canvas)
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

	canvas.DrawEllipse(m_rect.left, m_rect.top, m_rect.width, m_rect.height);

	if (m_style.IsEnabled())
	{
		canvas.EndFill();
	}
}
