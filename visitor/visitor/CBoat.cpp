#include "stdafx.h"
#include "CBoat.h"

void CBoat::Accept(ITransportVisitor & visitor)
{
	visitor.Visit(*this);
}
