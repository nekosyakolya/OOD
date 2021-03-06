﻿// GumballMachine.cpp : Defines the entry point for the console application.
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
void CSoldState::Refill(size_t)
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
	if (m_gumballMachine.GetBallCount() != 0)
	{
		m_gumballMachine.ReleaseCoin();
	}

	m_gumballMachine.ReleaseBall();
	bool hasBalls = m_gumballMachine.GetBallCount() != 0;
	bool hasCoins = m_gumballMachine.GetCoins() != 0;

	if (!hasBalls)
	{
		m_out << "Oops, out of gumballs\n";
	}

	if (!hasBalls && !hasCoins)
	{
		m_gumballMachine.SetSoldOutState();
	}
	else if (!hasCoins)
	{
		m_gumballMachine.SetNoCoinState();
	}
	else
	{
		m_gumballMachine.SetHasCoinState();
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
	m_gumballMachine.AddBall(count);
	if (m_gumballMachine.GetBallCount() != 0)
	{
		m_gumballMachine.SetNoCoinState();
	}
}

void CSoldOutState::InsertCoin()
{
	m_out << "You can't insert a coin, the machine is sold out\n";
}
void CSoldOutState::EjectCoin()
{
	m_out << "You can't eject, you haven't inserted a coin yet\n";
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
	m_gumballMachine.AddBall(count);
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
		m_out << "Coin returned\n";
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
	m_gumballMachine.AddBall(count);
}

void CNoCoinState::InsertCoin()
{
	m_gumballMachine.AddCoin();
	m_gumballMachine.SetHasCoinState();
}
void CNoCoinState::EjectCoin()
{
	m_out << "You haven't inserted a coin\n";
}
void CNoCoinState::TurnCrank()
{
	m_out << "You turned but there's no coin\n";
}
void CNoCoinState::Dispense()
{
	m_out << "You need to pay first\n";
}
std::string CNoCoinState::ToString() const
{
	return "waiting for coin";
}

CMultiGumballMachine::CMultiGumballMachine(size_t numBalls, std::ostream& out)
	: m_soldState(*this, out)
	, m_soldOutState(*this, out)
	, m_noCoinState(*this, out)
	, m_hasCoinState(*this, out)
	, m_state(&m_soldOutState)
	, m_gumBallsCount(numBalls)
	, m_out(out)
{
	if (m_gumBallsCount > 0)
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
	auto fmt = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
Number of coins: %4%
)");
	return (fmt % m_gumBallsCount % (m_gumBallsCount != 1 ? "s" : "") % m_state->ToString() % m_coinsCount).str();
}

size_t CMultiGumballMachine::GetBallCount() const
{
	return m_gumBallsCount;
}
void CMultiGumballMachine::ReleaseBall()
{
	if (m_gumBallsCount != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_gumBallsCount;
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
	if (m_coinsCount != MAX_COUNT_OF_COINS)
	{
		++m_coinsCount;
		m_out << "You inserted a coin\n";
	}
	else
	{
		m_out << "Can not insert coin\nStorage overflow!\n";
	}
}

void CMultiGumballMachine::ReleaseCoin()
{
	if (m_coinsCount != 0)
	{
		--m_coinsCount;
	}
}

void CMultiGumballMachine::Refill(size_t count)
{
	m_state->Refill(count);
}

void CMultiGumballMachine::AddBall(size_t count)
{
	m_gumBallsCount += count;
	m_out << "Added " << count << " gum ball" << (count != 1 ? "s" : "") << "\n";
}

size_t CMultiGumballMachine::GetCoins()
{
	return m_coinsCount;
}
