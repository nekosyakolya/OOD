#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual boost::optional<size_t> GetLineThickness()const = 0;
	virtual void SetLineThickness(size_t thickness) = 0;

	virtual ~ILineStyle() = default;
};
