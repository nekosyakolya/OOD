#pragma once
#include "ITransport.h"
#include "ITransportVisitor.h"

class CCar : public ITransport
{
public:
	void Accept(ITransportVisitor &) override;
};
