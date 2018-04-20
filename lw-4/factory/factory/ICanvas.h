#pragma once

struct Point
{
	float x;
	float y;
};

class ICanvas
{
public:
	virtual void SetColor(const Color& color) = 0;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(float left, float top, float width, float height) = 0;
	virtual ~ICanvas() = default;
};
