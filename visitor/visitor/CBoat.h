#pragma once
#include "ITransport.h"
#include "ITransportVisitor.h"

class CBoat : public ITransport
{
public:
	void Accept(ITransportVisitor &) override;
};
