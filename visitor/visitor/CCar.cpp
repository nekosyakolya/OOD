#include "stdafx.h"
#include "CCar.h"

void CCar::Accept(IVisitor &visitor)
{
	visitor.Visit(*this);
}
