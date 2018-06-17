#include "stdafx.h"
#include "CCalculateTicketPriceVisitor.h"

CCalculateTicketPriceVisitor::CCalculateTicketPriceVisitor():
	m_distance(.0f),
	m_ticketPrice(.0f)
{
}

void CCalculateTicketPriceVisitor::Visit(CBoat & boat)
{
	std::cout << "Distance: " << m_distance << std::endl;
	m_ticketPrice = 0.f;
	auto it = std::find_if(m_priceList.cbegin(), m_priceList.cend(), [&](const std::pair<TypeCheck, float>& item) {
		return item.first(&boat);
	});
	if (it != m_priceList.end())
	{
		m_ticketPrice = it->second * m_distance;
	}

}

void CCalculateTicketPriceVisitor::Visit(CCar & car)
{
	std::cout << "Distance: " << m_distance << std::endl;
	m_ticketPrice = 0.f;
	auto it = std::find_if(m_priceList.cbegin(), m_priceList.cend(), [&](const std::pair<TypeCheck, float>& item) {
		return item.first(&car);
	});
	if (it != m_priceList.end())
	{
		m_ticketPrice = it->second * m_distance;
	}
}

void CCalculateTicketPriceVisitor::Visit(CBus & bus)
{
	std::cout << "Distance: " << m_distance << std::endl;

	m_ticketPrice = 0.f;
	auto it = std::find_if(m_priceList.cbegin(), m_priceList.cend(), [&](const std::pair<TypeCheck, float>& item) {
		return item.first(&bus);
	});
	if (it != m_priceList.end())
	{
		m_ticketPrice = it->second * m_distance;
	}
}

void CCalculateTicketPriceVisitor::Visit(CPlane &plane)
{
	std::cout << "Distance: " << m_distance << std::endl;

	m_ticketPrice = 0.f;
	auto it = std::find_if(m_priceList.cbegin(), m_priceList.cend(), [&](const std::pair<TypeCheck, float>& item) {
		return item.first(&plane);
	});
	if (it != m_priceList.end())
	{
		m_ticketPrice = it->second * m_distance;
	}
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
