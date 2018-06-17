#pragma once

#include "IShapes.h"
#include "IShape.h"

class IGroupShape : public IShape, public IShapes
{
public:
	virtual ~IGroupShape() = default;
};

