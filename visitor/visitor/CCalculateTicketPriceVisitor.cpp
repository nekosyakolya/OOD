#include "stdafx.h"
#include "CCalculateTicketPriceVisitor.h"

CCalculateTicketPriceVisitor::CCalculateTicketPriceVisitor():
	m_distance(.0f),
	m_ticketPrice(.0f)
{
}

void CCalculateTicketPriceVisitor::Visit(CBoat & boat)
{
	Calculate(boat);
}

void CCalculateTicketPriceVisitor::Visit(CCar & car)
{
	Calculate(car);
}

void CCalculateTicketPriceVisitor::Visit(CBus & bus)
{
	Calculate(bus);
}

void CCalculateTicketPriceVisitor::Visit(CPlane &plane)
{
	Calculate(plane);
}

float CCalculateTicketPriceVisitor::GetTicketPrice() const
{
	return m_ticketPrice;
}

void CCalculateTicketPriceVisitor::SetDistance(float distance)
{
	m_distance = distance;
}

void CCalculateTicketPriceVisitor::AddPrice(const TypeCheck & typeCheck, float price)
{
	m_priceList.emplace_back(typeCheck, price);
}

void CCalculateTicketPriceVisitor::Calculate(const ITransport &transport)
{
	m_ticketPrice = 0.f;
	auto it = std::find_if(m_priceList.cbegin(), m_priceList.cend(), [&](const std::pair<TypeCheck, float>& item) {
		return item.first(&transport);
	});
	if (it != m_priceList.end())
	{
		m_ticketPrice = it->second * m_distance;
	}

}
