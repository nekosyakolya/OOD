#include "stdafx.h"

#include "../command/ReplaceSpecialHtmlCharacters.h"

BOOST_AUTO_TEST_SUITE(Replace_special_html_characters)

	BOOST_AUTO_TEST_CASE(can_execute)
	{
		std::string text = "&><&\"\'";
		CReplaceSpecialHtmlCharacters::Execute(text);

		BOOST_CHECK_EQUAL(text, "&amp;&gt;&lt;&amp;&quot;&apos;");
	}
BOOST_AUTO_TEST_SUITE_END()
