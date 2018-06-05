#include "stdafx.h"
#include "../command/CCommandHistory.h"
#include "../command/CDocumentItem.h"
#include "../command/DeleteItem.h"
#include "../command/InsertImage.h"
#include "../command/InsertParagraph.h"
#include "../command/Paragraph.h"

struct DeleteItem_
{
	struct DeleteItem_()
	{

		insertImageCommand = std::make_unique<CInsertImage>(history, items, "resources/amanita.png", 450, 300, 0);
		auto paragraph = std::make_shared<CParagraph>(history, "text");
		insertParagraphCommand = std::make_unique<CInsertParagraph>(paragraph, items, 0);

		command = std::make_unique<CDeleteItem>(items, 0);
	}
	std::unique_ptr<ICommand> insertImageCommand;
	std::unique_ptr<ICommand> insertParagraphCommand;

	std::vector<CDocumentItem> items;
	CCommandHistory history;
	std::unique_ptr<ICommand> command;
};

BOOST_FIXTURE_TEST_SUITE(Delete_item_command, DeleteItem_)

	BOOST_AUTO_TEST_SUITE(should_be_executed)
		BOOST_AUTO_TEST_CASE(with_image_if_position_is_correct)
		{

			insertImageCommand->Execute();
			BOOST_CHECK(!items.empty());

			command->Execute();
			BOOST_CHECK(items.empty());
		}
		BOOST_AUTO_TEST_CASE(with_paragraph_if_position_is_correct)
		{

			insertParagraphCommand->Execute();
			BOOST_CHECK(!items.empty());

			command->Execute();
			BOOST_CHECK(items.empty());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(should_be_not_executed)

		BOOST_AUTO_TEST_CASE(if_position_is_incorrect)
		{
			BOOST_CHECK(items.empty());
			BOOST_REQUIRE_THROW(command->Execute(), std::invalid_argument);
		}

	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(can_be_unexecuted)

		BOOST_AUTO_TEST_CASE(with_image)
		{

			insertImageCommand->Execute();
			BOOST_CHECK(!items.empty());
			command->Execute();
			command->Unexecute();
			BOOST_CHECK(!items.empty());
		}

		BOOST_AUTO_TEST_CASE(with_paragraph)
		{

			insertParagraphCommand->Execute();
			BOOST_CHECK(!items.empty());
			command->Execute();
			command->Unexecute();
			BOOST_CHECK(!items.empty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(does_not_delete_image_if_it_was_deleted_at_unexecuted_state)
	{
		insertImageCommand->Execute();
		auto image = items.front().GetImage();

		BOOST_REQUIRE(image != nullptr);
		command->Execute();
		command->Unexecute();
		command.reset();

		BOOST_CHECK(boost::filesystem::exists(image->GetPath()));
	}

	BOOST_AUTO_TEST_CASE(does_delete_image_if_it_was_deleted_at_executed_state)
	{
		insertImageCommand->Execute();

		auto image = items.front().GetImage();

		BOOST_REQUIRE(image != nullptr);
		command->Execute();

		command.reset();

		BOOST_CHECK(!boost::filesystem::exists(image->GetPath()));
	}

BOOST_AUTO_TEST_SUITE_END()
