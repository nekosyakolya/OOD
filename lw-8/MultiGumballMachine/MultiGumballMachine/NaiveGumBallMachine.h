#pragma once

namespace naive
{
class CGumballMachine
{
public:
	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoQuarter, // Нет монетки
		HasQuarter, // Есть монетка
		Sold, // Монетка выдана
	};

	CGumballMachine(size_t count, std::ostream& out)
		: m_count(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		, m_out(out)
		, m_coin(0)
	{
	}

	void InsertQuarter()
	{
		switch (m_state)
		{
		case State::SoldOut:
			m_out << "You can't insert a quarter, the machine is sold out\n";
			break;
		case State::NoQuarter:
			AddCoin();
			m_state = State::HasQuarter;
			break;
		case State::HasQuarter:
			AddCoin();
			break;
		case State::Sold:
			m_out << "Please wait, we're already giving you a gumball\n";
			break;
		}
	}

	void EjectQuarter()
	{
		switch (m_state)
		{
		case State::HasQuarter:
			while (m_coin != 0)
			{
				ReleaseCoin();
			}
			m_state = State::NoQuarter;
			break;
		case State::NoQuarter:
			m_out << "You haven't inserted a quarter\n";
			break;
		case State::Sold:
			m_out << "Sorry you already turned the crank\n";
			break;
		case State::SoldOut:
			m_out << "You can't eject, you haven't inserted a quarter yet\n";
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
		case State::NoQuarter:
			m_out << "You turned but there's no quarter\n";
			break;
		case State::HasQuarter:
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
		m_count = numBalls;
		m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
	}

	std::string ToString() const
	{
		std::string state = (m_state == State::SoldOut) ? "sold out" : (m_state == State::NoQuarter) ? "waiting for quarter" : (m_state == State::HasQuarter) ? "waiting for turn of crank" : "delivering a gumball";
		auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%
Machine is %3%
)");
		return (fmt % m_count % (m_count != 1 ? "s" : "") % state).str();
	}

private:
	void Dispense()
	{
		switch (m_state)
		{
		case State::Sold:
			m_out << "A gumball comes rolling out the slot\n";
			--m_count;
			ReleaseCoin();
			if (m_coin > m_count)
			{
				m_state = State::HasQuarter;
			}
			else if (m_count == 0)
			{
				m_out << "Oops, out of gumballs\n";
				m_state = State::SoldOut;
			}
			else
			{
				m_state = State::NoQuarter;
			}
			break;
		case State::NoQuarter:
			m_out << "You need to pay first\n";
			break;
		case State::SoldOut:
		case State::HasQuarter:
			m_out << "No gumball dispensed\n";
			break;
		}
	}

	void AddCoin()
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

	void ReleaseCoin()
	{
		if (m_coin != 0)
		{
			m_out << "Coin returned\n";
			--m_coin;
		}
	}

	size_t m_count; // Количество шариков
	size_t m_coin; // Количество монет
	const size_t MAX_COUNT_OF_COINS = 5;

	State m_state = State::SoldOut;
	std::ostream& m_out;
};
} // namespace naive
