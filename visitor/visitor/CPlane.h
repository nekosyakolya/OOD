#pragma once
#include "ITransport.h"
#include "ITransportVisitor.h"

class CPlane : public ITransport
{
public:
	void Accept(ITransportVisitor &) override;
};
