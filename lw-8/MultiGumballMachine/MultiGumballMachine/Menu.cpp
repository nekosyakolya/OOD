#include "stdafx.h"
#include "CMenu.h"

CMenu::CMenu()
	: m_machine(std::make_unique<with_state::CMultiGumballMachine>(0, std::cout))
	, m_isRun(true)
{
}

void CMenu::EjectCoin(std::istream&)
{
	m_machine->EjectCoin();
}

void CMenu::InsertCoin(std::istream&)
{
	m_machine->InsertCoin();
}

void CMenu::Refill(std::istream& args)
{
	size_t count = 0;
	if (!(args >> count))
	{
		throw std::invalid_argument("Incorrect number of arguments\n");
	}
	m_machine->Refill(count);
}

void CMenu::ToString(std::istream&)
{
	std::cout << m_machine->ToString();
}

void CMenu::Help(std::istream&)
{
	std::cout << "Commands list:" << std::endl;

	for (auto& item : COMMANDS)
	{
		std::cout << item.name << ": " << item.description << std::endl;
	}
}

void CMenu::TurnCrank(std::istream&)
{
	m_machine->TurnCrank();
}

void CMenu::Run()
{

	Help(std::cin);

	std::string command;
	while ((std::cout << ">") && m_isRun && getline(std::cin, command))
	{
		try
		{
			std::istringstream str(command);
			std::string name;
			str >> name;

			auto it = std::find_if(COMMANDS.cbegin(), COMMANDS.cend(), [&](const Item& item) {
				return item.name == name;
			});
			if (it == COMMANDS.end())
			{
				throw std::logic_error("Unknown command");
			}

			it->command(str);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

void CMenu::Exit(std::istream&)
{
	m_isRun = false;
}
