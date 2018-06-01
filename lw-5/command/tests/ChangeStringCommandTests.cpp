#include "stdafx.h"

#include "../command/ChangeStringCommand.h"

struct ChangeStringCommand_
{
	ChangeStringCommand_()
	{
		target = "target";
		newValue = "new value";
		command = std::make_unique<CChangeStringCommand>(target, newValue);
	}
	std::string target;
	std::string newValue;
	std::unique_ptr<CChangeStringCommand> command;
};

BOOST_FIXTURE_TEST_SUITE(Change_string_command, ChangeStringCommand_)

	BOOST_AUTO_TEST_CASE(can_be_executed)
	{
		command->Execute();
		BOOST_CHECK_EQUAL(target, newValue);
	}

	BOOST_AUTO_TEST_CASE(can_be_unexecuted)
	{
		command->Unexecute();

		BOOST_CHECK(target != newValue);
	}

BOOST_AUTO_TEST_SUITE_END()
