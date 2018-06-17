#pragma once
#include "IVisitor.h"
#include "CBoat.h"
#include "CCar.h"
#include "CBus.h"
#include "CPlane.h"

class CCalculateTicketPriceVisitor : public IVisitor
{
public:
	CCalculateTicketPriceVisitor();
	void Visit(CBoat &) override;
	void Visit(CCar &) override;
	void Visit(CBus &) override;
	void Visit(CPlane &) override;
	float GetTicketPrice() const;
	void SetDistance(float distance);
	using TypeCheck = std::function<bool(const ITransport* transport)>;

	void AddPrice(const TypeCheck& typeCheck, float price);
private:

	float m_distance;
	float m_ticketPrice;
	std::vector<std::pair<TypeCheck, float>> m_priceList;
	void Calculate(const ITransport&);
};

