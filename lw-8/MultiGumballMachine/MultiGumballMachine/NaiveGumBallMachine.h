﻿#pragma once

namespace naive
{
class CMultiGumballMachine
{
public:
	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoCoin, // Нет монетки
		HasCoin, // Есть монетка
		Sold, // Монетка выдана
	};

	CMultiGumballMachine(size_t count, std::ostream& out)
		: m_gumBallsCount(count)
		, m_state(count > 0 ? State::NoCoin : State::SoldOut)
		, m_out(out)
		, m_coinsCount(0)
	{
	}

	void InsertCoin()
	{
		switch (m_state)
		{
		case State::SoldOut:
			m_out << "You can't insert a coin, the machine is sold out\n";
			break;
		case State::NoCoin:
			AddCoin();
			m_state = State::HasCoin;
			break;
		case State::HasCoin:
			AddCoin();
			break;
		case State::Sold:
			m_out << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectCoin()
	{
		switch (m_state)
		{
		case State::HasCoin:
			while (m_coinsCount != 0)
			{
				ReleaseCoin();
				m_out << "Coin returned\n";
			}

			m_state = State::NoCoin;
			break;
		case State::NoCoin:
			m_out << "You haven't inserted a coin\n";
			break;
		case State::Sold:
			m_out << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			m_out << "You can't eject, you haven't inserted a coin yet\n";
			break;
		}
	}

	void TurnCrank()
	{
		switch (m_state)
		{
		case State::SoldOut:
			m_out << "You turned but there's no gumballs\n";
			break;
		case State::NoCoin:
			m_out << "You turned but there's no coin\n";
			break;
		case State::HasCoin:
			m_out << "You turned...\n";
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			m_out << "Turning twice doesn't get you another gumball\n";
			break;
		}
	}

	void Refill(size_t numBalls)
	{
		m_gumBallsCount = numBalls;
		m_state = numBalls > 0 ? State::NoCoin : State::SoldOut;
	}

	std::string ToString() const
	{
		std::string state = (m_state == State::SoldOut) ? "sold out" : (m_state == State::NoCoin) ? "waiting for coin" : (m_state == State::HasCoin) ? "waiting for turn of crank" : "delivering a gumball";
		auto fmt = boost::format(R"(Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
Number of coins: %4%
)");
		return (fmt % m_gumBallsCount % (m_gumBallsCount != 1 ? "s" : "") % state % m_coinsCount).str();
	}

private:
	void Dispense()
	{
		switch (m_state)
		{
		case State::Sold:
		{
			m_out << "A gumball comes rolling out the slot\n";

			if (m_gumBallsCount != 0)
			{
				--m_gumBallsCount;
				ReleaseCoin();
			}

			bool hasCoins = (m_coinsCount != 0);
			bool hasBalls = (m_gumBallsCount != 0);

			if (!hasBalls)
			{
				m_out << "Oops, out of gumballs\n";
			}

			if (!hasBalls && !hasCoins)
			{
				m_state = State::SoldOut;
			}
			else if (!hasCoins)
			{
				m_state = State::NoCoin;
			}
			else
			{
				m_state = State::HasCoin;
			}
			break;
		}
		case State::NoCoin:
			m_out << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasCoin:
			m_out << "No gumball dispensed\n";
			break;
		}
	}

	void AddCoin()
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

	void ReleaseCoin()
	{
		if (m_coinsCount != 0)
		{
			--m_coinsCount;
		}
	}

	size_t m_gumBallsCount; // Количество шариков
	size_t m_coinsCount; // Количество монет
	const size_t MAX_COUNT_OF_COINS = 5;

	State m_state = State::SoldOut;
	std::ostream& m_out;
};
} // namespace naive
