#pragma once
class CBoat;
class CCar;
class CBus;
class CPlane;

class ITransportVisitor
{
public:
	virtual ~ITransportVisitor() = default;
	virtual void Visit(CBoat &) = 0;
	virtual void Visit(CCar &) = 0;
	virtual void Visit(CBus &) = 0;
	virtual void Visit(CPlane &) = 0;
};
