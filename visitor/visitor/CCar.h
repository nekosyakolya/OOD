#pragma once
#include "ITransport.h"
#include "IVisitor.h"

class CCar : public ITransport
{
public:
	void Accept(IVisitor &) override;
};
