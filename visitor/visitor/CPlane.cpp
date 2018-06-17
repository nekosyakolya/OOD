#include "stdafx.h"
#include "CPlane.h"

void CPlane::Accept(IVisitor & visitor)
{
	visitor.Visit(*this);
}
