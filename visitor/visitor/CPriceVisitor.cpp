#include "stdafx.h"
#include "CPriceVisitor.h"

CPriceVisitor::CPriceVisitor():
	m_price(.0f)
{
}

float CPriceVisitor::GetTicketPrice(float distance, ITransport & transport)
{
	transport.Accept(*this);
	return m_price * distance;
}

void CPriceVisitor::Visit(CBoat & boat)
{
	m_price = m_priceList.boatPrice;
}

void CPriceVisitor::Visit(CCar & car)
{
	m_price = m_priceList.carPrice;
}

void CPriceVisitor::Visit(CBus & bus)
{
	m_price = m_priceList.busPrice;
}

void CPriceVisitor::Visit(CPlane &plane)
{
	m_price = m_priceList.planePrice;
}
