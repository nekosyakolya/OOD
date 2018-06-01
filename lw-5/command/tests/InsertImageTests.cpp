#include "stdafx.h"
#include "../command/CCommandHistory.h"
#include "../command/CDocumentItem.h"
#include "../command/InsertImage.h"

struct InsertImage_
{
	struct InsertImage_()
	{
		command = std::make_unique<CInsertImage>(history, items, "resources/amanita.png", 450, 300, 0);
	}
	std::vector<CDocumentItem> items;
	CCommandHistory history;
	std::unique_ptr<CInsertImage> command;
};

BOOST_FIXTURE_TEST_SUITE(Insert_image_command, InsertImage_)

	BOOST_AUTO_TEST_CASE(can_be_executed)
	{
		BOOST_CHECK(items.empty());
		command->Execute();
		BOOST_CHECK(!items.empty());
	}
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
		BOOST_CHECK(boost::filesystem::exists(image->GetPath()));
	}
BOOST_AUTO_TEST_SUITE_END()
