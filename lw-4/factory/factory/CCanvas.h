#pragma once
#include "Color.h"
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas();
	void SetColor(const Color& color) override;
	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(float left, float top, float width, float height) override;

private:
	Color m_color;
};
