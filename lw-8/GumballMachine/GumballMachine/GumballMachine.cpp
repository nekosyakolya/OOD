// GumballMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GumBallMachineWithState.h"

using namespace with_state;

CSoldState::CSoldState(IGumballMachine& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}
void CSoldState::InsertQuarter()
{
	m_out << "Please wait, we're already giving you a gumball\n";
}
void CSoldState::EjectQuarter()
{
	m_out << "Sorry you already turned the crank\n";
}
void CSoldState::TurnCrank()
{
	m_out << "Turning twice doesn't get you another gumball\n";
}
void CSoldState::Dispense()
{
	m_gumballMachine.ReleaseBall();
	if (m_gumballMachine.GetBallCount() == 0)
	{
		m_out << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();
	}
	else
	{
		m_gumballMachine.SetNoQuarterState();
	}
}
std::string CSoldState::ToString() const
{
	return "delivering a gumball";
}

CSoldOutState::CSoldOutState(IGumballMachine& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CSoldOutState::InsertQuarter()
{
	m_out << "You can't insert a quarter, the machine is sold out\n";
}
void CSoldOutState::EjectQuarter()
{
	m_out << "You can't eject, you haven't inserted a quarter yet\n";
}
void CSoldOutState::TurnCrank()
{
	m_out << "You turned but there's no gumballs\n";
}
void CSoldOutState::Dispense()
{
	m_out << "No gumball dispensed\n";
}
std::string CSoldOutState::ToString() const
{
	return "sold out";
}

CHasQuarterState::CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CHasQuarterState::InsertQuarter()
{
	m_out << "You can't insert another quarter\n";
}
void CHasQuarterState::EjectQuarter()
{
	m_out << "Quarter returned\n";
	m_gumballMachine.SetNoQuarterState();
}
void CHasQuarterState::TurnCrank()
{
	m_out << "You turned...\n";
	m_gumballMachine.SetSoldState();
}
void CHasQuarterState::Dispense()
{
	m_out << "No gumball dispensed\n";
}
std::string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}

CNoQuarterState::CNoQuarterState(IGumballMachine& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CNoQuarterState::InsertQuarter()
{
	m_out << "You inserted a quarter\n";
	m_gumballMachine.SetHasQuarterState();
}
void CNoQuarterState::EjectQuarter()
{
	m_out << "You haven't inserted a quarter\n";
}
void CNoQuarterState::TurnCrank()
{
	m_out << "You turned but there's no quarter\n";
}
void CNoQuarterState::Dispense()
{
	m_out << "You need to pay first\n";
}
std::string CNoQuarterState::ToString() const
{
	return "waiting for quarter";
}

CGumballMachine::CGumballMachine(size_t numBalls, std::ostream& out)
	: m_soldState(*this, out)
	, m_soldOutState(*this, out)
	, m_noQuarterState(*this, out)
	, m_hasQuarterState(*this, out)
	, m_state(&m_soldOutState)
	, m_count(numBalls)
	, m_out(out)
{
	if (m_count > 0)
	{
		m_state = &m_noQuarterState;
	}
}
void CGumballMachine::EjectQuarter()
{
	m_state->EjectQuarter();
}
void CGumballMachine::InsertQuarter()
{
	m_state->InsertQuarter();
}
void CGumballMachine::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}
std::string CGumballMachine::ToString() const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % m_count % (m_count != 1 ? "s" : "") % m_state->ToString()).str();
}

size_t CGumballMachine::GetBallCount() const
{
	return m_count;
}
void CGumballMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}
void CGumballMachine::SetSoldOutState()
{
	m_state = &m_soldOutState;
}
void CGumballMachine::SetNoQuarterState()
{
	m_state = &m_noQuarterState;
}
void CGumballMachine::SetSoldState()
{
	m_state = &m_soldState;
}
void CGumballMachine::SetHasQuarterState()
{
	m_state = &m_hasQuarterState;
}
