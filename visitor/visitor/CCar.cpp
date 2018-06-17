#include "stdafx.h"
#include "CCar.h"

void CCar::Accept(ITransportVisitor &visitor)
{
	visitor.Visit(*this);
}
