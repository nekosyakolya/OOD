#include "stdafx.h"

#include "../command/CCommandHistory.h"

#include "../command/ChangeStringCommand.h"

BOOST_AUTO_TEST_SUITE(Command_history)
	CCommandHistory history;
	BOOST_AUTO_TEST_SUITE(when_is_empty)
		BOOST_AUTO_TEST_CASE(can_not_redo)
		{
			BOOST_CHECK_EQUAL(history.CanRedo(), false);
		}

		BOOST_AUTO_TEST_CASE(can_not_undo)
		{
			BOOST_CHECK_EQUAL(history.CanUndo(), false);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can)

		std::string target = "target";
		std::string newValue = "new value";

		BOOST_AUTO_TEST_CASE(set_and_execute_command)
		{
			history.SetAndExecuteCommand(std::make_unique<CChangeStringCommand>(target, newValue));

			BOOST_CHECK_EQUAL(target, newValue);
		}

		BOOST_AUTO_TEST_CASE(undo_command)
		{
			BOOST_CHECK_EQUAL(history.CanUndo(), true);
			history.Undo();
			BOOST_CHECK(target != newValue);
		}

		BOOST_AUTO_TEST_CASE(redo_command)
		{
			BOOST_CHECK_EQUAL(history.CanRedo(), true);
			history.Redo();
			BOOST_CHECK_EQUAL(target, newValue);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(has_a_limited_size)
	{
		std::string target;
		for (size_t i = 0; i < 20; ++i)
		{
			history.SetAndExecuteCommand(std::make_unique<CChangeStringCommand>(target, "new"));
		}
		size_t size = 0;
		size_t expectedSize = 10;
		for (; history.CanUndo(); ++size)
		{
			history.Undo();
		}
		BOOST_CHECK_EQUAL(size, expectedSize);
	}

BOOST_AUTO_TEST_SUITE_END()
