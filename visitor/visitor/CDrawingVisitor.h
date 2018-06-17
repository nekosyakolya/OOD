#pragma once
#include "ITransportVisitor.h"
#include "CPlane.h"
#include "CBoat.h"
#include "CBus.h"
#include "CCar.h"

class CDrawingVisitor : public ITransportVisitor
{
public:
	void Visit(CBoat &) override;
	void Visit(CCar &) override;
	void Visit(CBus &) override;
	void Visit(CPlane &) override;
};
