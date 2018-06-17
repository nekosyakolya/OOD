#pragma once
#include "ITransportVisitor.h"

class ITransport
{
public:
	virtual ~ITransport() = default;
	virtual void Accept(ITransportVisitor &) = 0;
};
