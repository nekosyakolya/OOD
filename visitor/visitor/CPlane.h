#pragma once
#include "ITransport.h"
#include "IVisitor.h"

class CPlane : public ITransport
{
public:
	void Accept(IVisitor &) override;
};
