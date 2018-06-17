#include "stdafx.h"
#include "CBoat.h"

void CBoat::Accept(IVisitor & visitor)
{
	visitor.Visit(*this);
}
