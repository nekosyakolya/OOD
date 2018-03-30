#include "stdafx.h"

BOOST_AUTO_TEST_SUITE(adapter)
	BOOST_AUTO_TEST_CASE(can_move_to_point)
	{
		std::stringstream stream;
		app::CModernGraphicsRendererAdapter adapter(stream);

		adapter.MoveTo(0, 6);

		BOOST_CHECK_EQUAL(stream.str(), "<draw>\n");
	}

	BOOST_AUTO_TEST_CASE(can_draw_line)
	{
		std::stringstream stream;
		app::CModernGraphicsRendererAdapter adapter(stream);

		adapter.MoveTo(0, 6);
		adapter.LineTo(0, 10);

		std::stringstream expected;
		expected << "<draw>" << std::endl;
		expected << R"(<line fromX="0" fromY="6" toX="0" toY="10"/>)" << std::endl;

		BOOST_CHECK_EQUAL(stream.str(), expected.str());
	}

BOOST_AUTO_TEST_SUITE_END()
