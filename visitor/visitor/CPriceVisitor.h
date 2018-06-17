#pragma once
#include "ITransportVisitor.h"
#include "CBoat.h"
#include "CCar.h"
#include "CBus.h"
#include "CPlane.h"

class CPriceVisitor : public ITransportVisitor
{
public:
	CPriceVisitor();
	double GetTicketPrice(double distance, ITransport & transport);
	using TypeCheck = std::function<bool(ITransport* transport)>;
	void AddTypeCheck(const TypeCheck& typeCheck, double price);

	void Visit(CBoat &) override;
	void Visit(CCar &) override;
	void Visit(CBus &) override;
	void Visit(CPlane &) override;
private:
	double m_price;
	std::vector<std::pair<TypeCheck, double>> m_priceList;
	void SetPrice(ITransport & transport);
};

