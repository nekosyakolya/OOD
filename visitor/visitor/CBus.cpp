#include "stdafx.h"
#include "CBus.h"

void CBus::Accept(IVisitor &visitor)
{
	visitor.Visit(*this);
}
