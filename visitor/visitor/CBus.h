#pragma once
#include "ITransport.h"
#include "IVisitor.h"

class CBus : public ITransport
{
public:
	void Accept(IVisitor &) override;
};
