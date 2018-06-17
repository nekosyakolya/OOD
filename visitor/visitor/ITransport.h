#pragma once
#include "IVisitor.h"

class ITransport
{
public:
	virtual ~ITransport() = default;
	virtual void Accept(IVisitor &) = 0;
};
