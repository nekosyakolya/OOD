#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(const RectD & rect, ILineStyle &, IStyle &);
	void Draw(ICanvas & canvas) override;
};

