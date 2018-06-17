#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(const RectD & rect, ILineStyle &, IStyle &);
	void Draw(ICanvas & canvas) override;
};
