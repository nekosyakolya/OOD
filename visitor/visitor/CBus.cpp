#include "stdafx.h"
#include "CBus.h"

void CBus::Accept(ITransportVisitor &visitor)
{
	visitor.Visit(*this);
}
