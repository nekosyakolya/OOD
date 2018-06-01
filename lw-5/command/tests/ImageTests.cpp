#include "stdafx.h"
#include "../command/CCommandHistory.h"
#include "../command/Image.h"

BOOST_AUTO_TEST_SUITE(Image)

	CCommandHistory history;
	CImage image(history, "resources/amanita.png", 450, 200);
	BOOST_AUTO_TEST_CASE(is_not_created_if_path_is_incorrect)
	{
		BOOST_REQUIRE_THROW(CImage image(history, "resources/1.png", 450, 200), std::logic_error);
		BOOST_REQUIRE_THROW(CImage image(history, "resources/tmp.txt", 450, 200), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(has_path)
	{
		BOOST_CHECK_EQUAL(image.GetPath(), "resources/amanita.png");
	}

	BOOST_AUTO_TEST_CASE(has_width)
	{
		BOOST_CHECK_EQUAL(image.GetWidth(), 450);
	}

	BOOST_AUTO_TEST_CASE(has_height)
	{
		BOOST_CHECK_EQUAL(image.GetHeight(), 200);
	}

	BOOST_AUTO_TEST_CASE(can_be_resized)
	{
		image.Resize(800, 400);
		BOOST_CHECK_EQUAL(image.GetWidth(), 800);
		BOOST_CHECK_EQUAL(image.GetHeight(), 400);
	}

BOOST_AUTO_TEST_SUITE_END()
