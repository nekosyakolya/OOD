// visitor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CPlane.h"
#include "CBoat.h"
#include "CBus.h"
#include "CCar.h"
#include "CDrawingVisitor.h"
#include "CCalculateTicketPriceVisitor.h"

int main()
{
	CBus bus;
	CDrawingVisitor drawingVisitor;
	CCalculateTicketPriceVisitor calculateTicketPriceVisitor;
	calculateTicketPriceVisitor.AddPrice([](const ITransport* transport) {
		return dynamic_cast<const CBus*>(transport);
	}, 100.f);

	calculateTicketPriceVisitor.AddPrice([](const ITransport* transport) {
		return dynamic_cast<const CBoat*>(transport);
	}, 230.f);

	calculateTicketPriceVisitor.AddPrice([](const ITransport* transport) {
		return dynamic_cast<const CCar*>(transport);
	}, 43.5f);

	calculateTicketPriceVisitor.AddPrice([](const ITransport* transport) {
		return dynamic_cast<const CPlane*>(transport);
	}, 3000.f);

	calculateTicketPriceVisitor.SetDistance(500.f);
	bus.Accept(drawingVisitor);
	bus.Accept(calculateTicketPriceVisitor);
	std::cout << "Ticket price: " << calculateTicketPriceVisitor.GetTicketPrice() << std::endl;

	CCar car;
	car.Accept(drawingVisitor);
	car.Accept(calculateTicketPriceVisitor);
	std::cout << "Ticket price: " << calculateTicketPriceVisitor.GetTicketPrice() << std::endl;

	return 0;
}
