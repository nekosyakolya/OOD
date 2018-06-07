#pragma once
#include "MultiGumBallMachineWithState.h"

class CMenu
{
public:
	CMenu();
	void Run();

private:
	bool m_isRun;
	std::unique_ptr<with_state::IGumballMachine>
		m_machine;
	using Command = std::function<void(std::istream& args)>;

	void EjectCoin(std::istream&);

	void InsertCoin(std::istream&);
	void TurnCrank(std::istream&);
	void ToString(std::istream&);
	void Refill(std::istream&);

	void Exit(std::istream&);
	void Help(std::istream&);

	struct Item
	{
		Item(const std::string& name, const std::string& description, const Command& command)
			: name(name)
			, description(description)
			, command(command)
		{
		}

		std::string name;
		std::string description;
		Command command;
	};

	const std::vector<Item> COMMANDS = {
		{ "InsertCoin", "Insert coin", std::bind(&CMenu::InsertCoin, this, std::placeholders::_1) },
		{ "EjectCoin", "Eject coin", std::bind(&CMenu::EjectCoin, this, std::placeholders::_1) },
		{ "ToString", "Insert coin", std::bind(&CMenu::ToString, this, std::placeholders::_1) },
		{ "TurnCrank", "Turn crank", std::bind(&CMenu::TurnCrank, this, std::placeholders::_1) },
		{ "Refill", "Refill <count>", std::bind(&CMenu::Refill, this, std::placeholders::_1) },
		{ "Help", "Help", std::bind(&CMenu::Help, this, std::placeholders::_1) },
		{ "Exit", "Exit", std::bind(&CMenu::Exit, this, std::placeholders::_1) }
	};
};
