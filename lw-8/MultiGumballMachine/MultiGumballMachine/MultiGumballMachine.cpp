// GumballMachine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MultiGumBallMachineWithState.h"

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
void CSoldState::Refill(size_t /*count*/)
{
	m_out << "Sorry, this operation is not available\n ";
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
	m_gumballMachine.ReleaseCoin();

	if (m_gumballMachine.GetCoins() > m_gumballMachine.GetBallCount())
	{
		m_gumballMachine.SetHasCoinState();
	}
	else if (m_gumballMachine.GetBallCount() == 0)
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

void CSoldOutState::Refill(size_t count)
{
	m_gumballMachine.Refill(count);
}

void CSoldOutState::InsertCoin()
{
	m_out << "You can't insert a Coin, the machine is sold out\n";
}
void CSoldOutState::EjectCoin()
{
	m_out << "You can't eject, you haven't inserted a Coin yet\n";
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

void CHasCoinState::Refill(size_t count)
{
	m_gumballMachine.Refill(count);
}
void CHasCoinState::InsertCoin()
{
	m_gumballMachine.AddCoin();
}
void CHasCoinState::EjectCoin()
{
	while (m_gumballMachine.GetCoins() != 0)
	{
		m_gumballMachine.ReleaseCoin();
	}

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

void CNoCoinState::Refill(size_t count)
{
	m_gumballMachine.Refill(count);
}

void CNoCoinState::InsertCoin()
{
	m_gumballMachine.AddCoin();
	m_gumballMachine.SetHasCoinState();
}
void CNoCoinState::EjectCoin()
{
	m_out << "You haven't inserted a Coin\n";
}
void CNoCoinState::TurnCrank()
{
	m_out << "You turned but there's no Coin\n";
}
void CNoCoinState::Dispense()
{
	m_out << "You need to pay first\n";
}
std::string CNoCoinState::ToString() const
{
	return "waiting for Coin";
}

CMultiGumballMachine::CMultiGumballMachine(size_t numBalls, std::ostream& out)
	: m_soldState(*this, out)
	, m_soldOutState(*this, out)
	, m_noCoinState(*this, out)
	, m_hasCoinState(*this, out)
	, m_state(&m_soldOutState)
	, m_gumBalls(numBalls)
	, m_out(out)
{
	if (m_gumBalls > 0)
	{
		m_state = &m_noCoinState;
	}
}
void CMultiGumballMachine::EjectCoin()
{
	m_state->EjectCoin();
}
void CMultiGumballMachine::InsertCoin()
{
	m_state->InsertCoin();
}
void CMultiGumballMachine::TurnCrank()
{
	m_state->TurnCrank();
	m_state->Dispense();
}
std::string CMultiGumballMachine::ToString() const
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % m_gumBalls % (m_gumBalls != 1 ? "s" : "") % m_state->ToString()).str();
}

size_t CMultiGumballMachine::GetBallCount() const
{
	return m_gumBalls;
}
void CMultiGumballMachine::ReleaseBall()
{
	if (m_gumBalls != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_gumBalls;
	}
}
void CMultiGumballMachine::SetSoldOutState()
{
	m_state = &m_soldOutState;
}
void CMultiGumballMachine::SetNoCoinState()
{
	m_state = &m_noCoinState;
}
void CMultiGumballMachine::SetSoldState()
{
	m_state = &m_soldState;
}
void CMultiGumballMachine::SetHasCoinState()
{
	m_state = &m_hasCoinState;
}

void CMultiGumballMachine::AddCoin()
{
	if (m_coin != MAX_COUNT_OF_COINS)
	{
		++m_coin;
		m_out << "You inserted a Coin\n";
	}
	else
	{
		m_out << "Can not insert coin\nStorage overflow!\n";
	}
}

void CMultiGumballMachine::ReleaseCoin()
{
	if (m_coin != 0)
	{
		m_out << "Coin returned\n";
		--m_coin;
	}
}

void CMultiGumballMachine::Refill(size_t count)
{
	m_gumBalls += count;
	m_out << "Added " << count << (count != 1 ? "s" : "") << "\n";
}

size_t CMultiGumballMachine::GetCoins()
{
	return m_coin;
}
