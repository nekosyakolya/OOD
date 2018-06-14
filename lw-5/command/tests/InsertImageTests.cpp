#include "stdafx.h"
#include "../command/CCommandHistory.h"
#include "../command/CDocumentItem.h"
#include "../command/InsertImageCommand.h"

struct InsertImage_
{
	struct InsertImage_()
	{
		width = 450;
		height = 300;
		command = std::make_unique<CInsertImageCommand>(history, items, "resources/amanita.png", width, height, "tmp", 0);
	}
	int width;
	int height;

	std::vector<CDocumentItem> items;
	CCommandHistory history;
	std::unique_ptr<CInsertImageCommand> command;
};

BOOST_FIXTURE_TEST_SUITE(Insert_image_command, InsertImage_)

	BOOST_AUTO_TEST_SUITE(should_be_executed)
		BOOST_AUTO_TEST_CASE(if_position_is_correct)
		{
			BOOST_CHECK(items.empty());
			command->Execute();

			BOOST_REQUIRE(!items.empty());

			auto image = items.front().GetImage();

			BOOST_REQUIRE(image != nullptr);
			BOOST_CHECK(boost::filesystem::exists(image->GetPath()));
			BOOST_CHECK_EQUAL(image->GetHeight(), height);
			BOOST_CHECK_EQUAL(image->GetWidth(), width);
		}
		BOOST_AUTO_TEST_CASE(if_position_is_not_transferred)
		{
			command = std::make_unique<CInsertImageCommand>(history, items, "resources/amanita.png", width, height, "tmp");

			BOOST_CHECK(items.empty());

			command->Execute();
			BOOST_REQUIRE(!items.empty());

			auto image = items.front().GetImage();

			BOOST_REQUIRE(image != nullptr);
			BOOST_CHECK(boost::filesystem::exists(image->GetPath()));

			BOOST_CHECK_EQUAL(image->GetHeight(), height);
			BOOST_CHECK_EQUAL(image->GetWidth(), width);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(should_be_not_executed)

		BOOST_AUTO_TEST_CASE(if_position_is_incorrect)
		{
			BOOST_CHECK(items.empty());
			command = std::make_unique<CInsertImageCommand>(history, items, "resources/amanita.png", width, height, "tmp", 10);
			BOOST_REQUIRE_THROW(command->Execute(), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(if_path_is_incorrect)
		{
			BOOST_REQUIRE_THROW(std::make_unique<CInsertImageCommand>(history, items, "resources/1.png", width, height, "tmp", 0), boost::filesystem::filesystem_error);
			BOOST_REQUIRE_THROW(std::make_unique<CInsertImageCommand>(history, items, "resources/tmp.txt", width, height, "tmp", 0), std::logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_be_unexecuted)
	{
		command->Execute();
		command->Unexecute();
		BOOST_CHECK(items.empty());
	}
	BOOST_AUTO_TEST_CASE(copy_image_to_images_directory)
	{
		command->Execute();
		auto image = items.front().GetImage();

		BOOST_REQUIRE(image != nullptr);
		BOOST_CHECK(boost::filesystem::exists(image->GetPath()));
	}

	BOOST_AUTO_TEST_CASE(does_not_delete_image_if_it_was_deleted_at_executed_state)
	{
		command->Execute();
		auto image = items.front().GetImage();

		BOOST_REQUIRE(image != nullptr);
		command.reset();

		BOOST_CHECK(boost::filesystem::exists(image->GetPath()));
	}

	BOOST_AUTO_TEST_CASE(does_delete_image_if_it_was_deleted_at_unexecuted_state)
	{
		command->Execute();
		auto image = items.front().GetImage();

		BOOST_REQUIRE(image != nullptr);
		command->Unexecute();
		command.reset();

		BOOST_CHECK(!boost::filesystem::exists(image->GetPath()));
	}

BOOST_AUTO_TEST_SUITE_END()
