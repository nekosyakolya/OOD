#include "stdafx.h"
#include "CPlane.h"

void CPlane::Accept(ITransportVisitor & visitor)
{
	visitor.Visit(*this);
}
