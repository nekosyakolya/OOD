#include "stdafx.h"
#include "CPriceVisitor.h"

CPriceVisitor::CPriceVisitor():
	m_price(.0)
{
}

double CPriceVisitor::GetTicketPrice(double distance, ITransport & transport)
{
	transport.Accept(*this);
	return m_price * distance;
}

void CPriceVisitor::AddTypeCheck(const TypeCheck & typeCheck, double price)
{
	m_priceList.emplace_back(typeCheck, price);
}

void CPriceVisitor::Visit(CBoat & boat)
{
	SetPrice(boat);
}

void CPriceVisitor::Visit(CCar & car)
{
	SetPrice(car);
}

void CPriceVisitor::Visit(CBus & bus)
{
	SetPrice(bus);
}

void CPriceVisitor::Visit(CPlane &plane)
{
	SetPrice(plane);
}

void CPriceVisitor::SetPrice(ITransport & transport)
{
	m_price = 0.f;
	auto it = std::find_if(m_priceList.cbegin(), m_priceList.cend(),
		[&](const std::pair<TypeCheck, double>& item) {return item.first(&transport);
	});
	if (it != m_priceList.end())
	{
		m_price = it->second;
	}
}
