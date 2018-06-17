#pragma once
#include "ITransport.h"
#include "ITransportVisitor.h"

class CBus : public ITransport
{
public:
	void Accept(ITransportVisitor &) override;
};
