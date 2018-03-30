#include "stdafx.h"

BOOST_AUTO_TEST_SUITE(adapter)
	BOOST_AUTO_TEST_CASE(can_move_to_point)
	{
		std::stringstream stream;
		modern_graphics_lib::CModernGraphicsRenderer renderer(stream);
		app::CModernGraphicsRendererAdapter adapter(renderer);

		adapter.MoveTo(13, 13);
		BOOST_CHECK_EQUAL(stream.str(), "<draw>\n");
	}

	BOOST_AUTO_TEST_CASE(can_draw_color_line)
	{
		std::stringstream stream;
		modern_graphics_lib::CModernGraphicsRenderer renderer(stream);
		app::CModernGraphicsRendererAdapter adapter(renderer);
		adapter.SetColor(0x520057);
		adapter.MoveTo(9, 13);
		adapter.LineTo(0, 10);

		std::stringstream expected;
		expected << "<draw>" << std::endl;
		expected << R"(<line fromX="9" fromY="13" toX="0" toY="10">)" << std::endl;
		expected << '\t' << R"(<color r="0.321569" g="0" b="0.341176" a="1" />)" << std::endl;
		expected << "</line>" << std::endl;

		BOOST_CHECK_EQUAL(stream.str(), expected.str());
	}

BOOST_AUTO_TEST_SUITE_END()
