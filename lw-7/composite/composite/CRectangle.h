#pragma once
#include "CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const RectD & rect, ILineStyle &, IStyle &);
	void Draw(ICanvas & canvas) override;
};

