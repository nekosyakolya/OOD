#pragma once

#include "ICanvas.h"

class IDrawable
{
public:
	virtual void Draw(const ICanvas & canvas) = 0;
	virtual ~IDrawable() = default;
};
