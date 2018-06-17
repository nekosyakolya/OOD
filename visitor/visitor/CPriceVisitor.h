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
	float GetTicketPrice(float distance, ITransport & transport);

	void Visit(CBoat &) override;
	void Visit(CCar &) override;
	void Visit(CBus &) override;
	void Visit(CPlane &) override;
private:
	float m_price;
	struct PriceList
	{
		float boatPrice = 100.f;
		float carPrice = 43.5f;
		float busPrice = 50.5f;
		float planePrice = 4300.f;
	} m_priceList;
};

