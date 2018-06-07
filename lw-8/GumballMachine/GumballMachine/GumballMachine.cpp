// GumballMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GumBallMachineWithState.h"

using namespace with_state;

CSoldState::CSoldState(IGumballMachineContext& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}
void CSoldState::InsertCoin()
{
	m_out << "Please wait, we're already giving you a gumball\n";
}
void CSoldState::EjectCoin()
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
		m_gumballMachine.SetNoCoinState();
	}
}
std::string CSoldState::ToString() const
{
	return "delivering a gumball";
}

CSoldOutState::CSoldOutState(IGumballMachineContext& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CSoldOutState::InsertCoin()
{
	m_out << "You can't insert a quarter, the machine is sold out\n";
}
void CSoldOutState::EjectCoin()
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

CHasCoinState::CHasCoinState(IGumballMachineContext& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CHasCoinState::InsertCoin()
{
	m_out << "You can't insert another quarter\n";
}
void CHasCoinState::EjectCoin()
{
	m_out << "Quarter returned\n";
	m_gumballMachine.SetNoCoinState();
}
void CHasCoinState::TurnCrank()
{
	m_out << "You turned...\n";
	m_gumballMachine.SetSoldState();
}
void CHasCoinState::Dispense()
{
	m_out << "No gumball dispensed\n";
}
std::string CHasCoinState::ToString() const
{
	return "waiting for turn of crank";
}

CNoCoinState::CNoCoinState(IGumballMachineContext& gumballMachine, std::ostream& out)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CNoCoinState::InsertCoin()
{
	m_out << "You inserted a quarter\n";
	m_gumballMachine.SetHasCoinState();
}
void CNoCoinState::EjectCoin()
{
	m_out << "You haven't inserted a quarter\n";
}
void CNoCoinState::TurnCrank()
{
	m_out << "You turned but there's no quarter\n";
}
void CNoCoinState::Dispense()
{
	m_out << "You need to pay first\n";
}
std::string CNoCoinState::ToString() const
{
	return "waiting for quarter";
}

CGumballMachine::CGumballMachine(size_t numBalls, std::ostream& out)
	: m_soldState(*this, out)
	, m_soldOutState(*this, out)
	, m_noCoinState(*this, out)
	, m_hasCoinState(*this, out)
	, m_state(&m_soldOutState)
	, m_count(numBalls)
	, m_out(out)
{
	if (m_count > 0)
	{
		m_state = &m_noCoinState;
	}
}
void CGumballMachine::EjectCoin()
{
	m_state->EjectCoin();
}
void CGumballMachine::InsertCoin()
{
	m_state->InsertCoin();
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
void CGumballMachine::SetNoCoinState()
{
	m_state = &m_noCoinState;
}
void CGumballMachine::SetSoldState()
{
	m_state = &m_soldState;
}
void CGumballMachine::SetHasCoinState()
{
	m_state = &m_hasCoinState;
}
