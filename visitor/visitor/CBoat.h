#pragma once
#include "ITransport.h"
#include "IVisitor.h"

class CBoat : public ITransport
{
public:
	void Accept(IVisitor &) override;
};
