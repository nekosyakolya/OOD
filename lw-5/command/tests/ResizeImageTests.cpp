#include "stdafx.h"

#include "../command/ResizeImageCommand.h"

struct ResizeImage_
{
	ResizeImage_()
	{
		width = 300;
		height = 210;
		newWidth = 600;
		newHeight = 420;
		command = std::make_unique<CResizeImageCommand>(width, newWidth, height, newHeight);
	}
	int width;
	int height;
	int newWidth;
	int newHeight;
	std::unique_ptr<CResizeImageCommand> command;
};

BOOST_FIXTURE_TEST_SUITE(Resize_image_command, ResizeImage_)

	BOOST_AUTO_TEST_CASE(can_be_executed)
	{
		command->Execute();
		BOOST_CHECK_EQUAL(width, newWidth);
		BOOST_CHECK_EQUAL(height, newHeight);
	}

	BOOST_AUTO_TEST_CASE(can_be_unexecuted)
	{
		command->Execute();

		command->Unexecute();
		BOOST_CHECK(width != newWidth);
		BOOST_CHECK(height != newHeight);
	}

BOOST_AUTO_TEST_SUITE_END()
