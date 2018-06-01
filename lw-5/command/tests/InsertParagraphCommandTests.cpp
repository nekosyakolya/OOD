#include "stdafx.h"

#include "../command/CCommandHistory.h"
#include "../command/CDocumentItem.h"
#include "../command/InsertParagraph.h"

struct InsertParagraph_
{
	InsertParagraph_()
	{
		text = "text";
		command = std::make_unique<CInsertParagraph>(history, items, text, 0);
	}
	std::string text;
	std::vector<CDocumentItem> items;
	CCommandHistory history;
	std::unique_ptr<CInsertParagraph> command;
};

BOOST_FIXTURE_TEST_SUITE(Insert_paragraph_command, InsertParagraph_)

	BOOST_AUTO_TEST_CASE(can_be_executed)
	{
		BOOST_CHECK(items.empty());

		command->Execute();
		BOOST_REQUIRE(!items.empty());
		BOOST_REQUIRE(items.front().GetParagraph() != nullptr);
		BOOST_CHECK_EQUAL(items.front().GetParagraph()->GetText(), text);
	}

	BOOST_AUTO_TEST_CASE(can_be_unexecuted)
	{
		command->Execute();

		BOOST_CHECK(!items.empty());
		command->Unexecute();

		BOOST_REQUIRE(items.empty());
	}

BOOST_AUTO_TEST_SUITE_END()
