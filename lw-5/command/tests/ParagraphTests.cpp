#include "stdafx.h"
#include "../command/CCommandHistory.h"
#include "../command/Paragraph.h"

BOOST_AUTO_TEST_SUITE(Paragraph)

	CCommandHistory history;
	std::string expectedText = "text";
	CParagraph paragraph(history, expectedText);

	BOOST_AUTO_TEST_CASE(has_text)
	{
		BOOST_CHECK_EQUAL(paragraph.GetText(), expectedText);
	}

	BOOST_AUTO_TEST_CASE(can_be_changed)
	{
		std::string newValue = "newValue";
		BOOST_CHECK_EQUAL(paragraph.GetText(), expectedText);
		paragraph.SetText(newValue);
		BOOST_CHECK_EQUAL(paragraph.GetText(), newValue);
	}

BOOST_AUTO_TEST_SUITE_END()
