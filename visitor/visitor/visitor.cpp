// visitor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CPlane.h"
#include "CBoat.h"
#include "CBus.h"
#include "CCar.h"
#include "CDrawingVisitor.h"
#include "CPriceVisitor.h"

int main()
{
	CBus bus;
	CDrawingVisitor drawingVisitor;
	CPriceVisitor priceVisitor;
	priceVisitor.AddTypeCheck([](ITransport *transport) {
		return dynamic_cast<CBoat*>(transport);
	}, 200.0);
	
	priceVisitor.AddTypeCheck([](ITransport *transport) {
		return dynamic_cast<CBus*>(transport);
	}, 100.0);

	priceVisitor.AddTypeCheck([](ITransport *transport) {
		return dynamic_cast<CCar*>(transport);
	}, 43.5);

	priceVisitor.AddTypeCheck([](ITransport *transport) {
		return dynamic_cast<CPlane*>(transport);
	}, 300.0);

	bus.Accept(drawingVisitor);
	std::cout << "Ticket price: " << priceVisitor.GetTicketPrice(500.0, bus) << std::endl;

	CCar car;
	car.Accept(drawingVisitor);
	std::cout << "Ticket price: " << priceVisitor.GetTicketPrice(500.0, car) << std::endl;

	CBoat boat;
	boat.Accept(drawingVisitor);
	std::cout << "Ticket price: " << priceVisitor.GetTicketPrice(500.0, boat) << std::endl;

	CPlane plane;
	plane.Accept(drawingVisitor);
	std::cout << "Ticket price: " << priceVisitor.GetTicketPrice(500.0, plane) << std::endl;

	return 0;
}
