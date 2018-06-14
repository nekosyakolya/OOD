#include "stdafx.h"

#include "../command/CCommandHistory.h"
#include "../command/CDocumentItem.h"
#include "../command/InsertParagraphCommand.h"
#include "../command/Paragraph.h"

struct InsertParagraph_
{
	InsertParagraph_()
	{
		text = "text";
		paragraphPtr = std::make_shared<CParagraph>(history, text);
		command = std::make_unique<CInsertParagraphCommand>(paragraphPtr, items, 0);
	}
	std::string text;
	std::vector<CDocumentItem> items;
	CCommandHistory history;
	std::shared_ptr<CParagraph> paragraphPtr;
	std::unique_ptr<CInsertParagraphCommand> command;
};

BOOST_FIXTURE_TEST_SUITE(Insert_paragraph_command, InsertParagraph_)

	BOOST_AUTO_TEST_SUITE(should_be_executed)
		BOOST_AUTO_TEST_CASE(if_position_is_correct)
		{
			BOOST_CHECK(items.empty());

			command->Execute();
			BOOST_REQUIRE(!items.empty());
			BOOST_REQUIRE(items.front().GetParagraph() != nullptr);
			BOOST_CHECK_EQUAL(items.front().GetParagraph()->GetText(), text);
		}
		BOOST_AUTO_TEST_CASE(if_position_is_not_transferred)
		{
			command = std::make_unique<CInsertParagraphCommand>(paragraphPtr, items, boost::none);

			BOOST_CHECK(items.empty());

			command->Execute();
			BOOST_REQUIRE(!items.empty());
			BOOST_REQUIRE(items.front().GetParagraph() != nullptr);
			BOOST_CHECK_EQUAL(items.front().GetParagraph()->GetText(), text);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(can_be_unexecuted)
	{
		command->Execute();
		BOOST_CHECK(!items.empty());
		command->Unexecute();

		BOOST_REQUIRE(items.empty());
	}
	BOOST_AUTO_TEST_CASE(should_be_not_executed_if_position_is_incorrect)
	{
		BOOST_CHECK(items.empty());

		command = std::make_unique<CInsertParagraphCommand>(paragraphPtr, items, 10);

		BOOST_REQUIRE_THROW(command->Execute(), std::invalid_argument);
	}

BOOST_AUTO_TEST_SUITE_END()
