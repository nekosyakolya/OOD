#pragma once

#include "CShape.h"
#include <memory>
#include <string>

class IShapeFactory
{
public:
	virtual std::unique_ptr<CShape> CreateShape(const std::string& description) = 0;
	virtual ~IShapeFactory() = default;
};
