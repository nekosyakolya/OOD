#include "stdafx.h"
#include "../command/Document.h"
#include "../command/HtmlToFileSerializer.h"

struct Document_
{
	CDocument document;
};

BOOST_FIXTURE_TEST_SUITE(Document, Document_)
	BOOST_AUTO_TEST_SUITE(when_is_empty)
		BOOST_AUTO_TEST_CASE(can_not_redo)
		{
			BOOST_CHECK(!document.CanRedo());
		}

		BOOST_AUTO_TEST_CASE(can_not_undo)
		{
			BOOST_CHECK(!document.CanUndo());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(can_set_title)
	{
		document.SetTitle("title");
		BOOST_CHECK_EQUAL(document.GetTitle(), "title");
	}
	BOOST_AUTO_TEST_CASE(can_undo_action)
	{
		document.SetTitle("title");
		BOOST_CHECK_EQUAL(document.GetTitle(), "title");

		document.SetTitle("new title");
		BOOST_CHECK_EQUAL(document.GetTitle(), "new title");
		document.Undo();
		BOOST_CHECK_EQUAL(document.GetTitle(), "title");
	}

	BOOST_AUTO_TEST_CASE(can_redo_action)
	{
		document.SetTitle("title");
		BOOST_CHECK_EQUAL(document.GetTitle(), "title");
		document.Undo();
		BOOST_CHECK(document.GetTitle() != "title");
		document.Redo();
		BOOST_CHECK_EQUAL(document.GetTitle(), "title");
	}
	BOOST_AUTO_TEST_CASE(can_insert_paragraph)
	{
		document.InsertParagraph("text");

		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		BOOST_REQUIRE(document.GetItem(0).GetParagraph() != nullptr);

		BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "text");

		document.InsertParagraph("new text", 0);
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
		BOOST_REQUIRE(document.GetItem(1).GetParagraph() != nullptr);

		BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "new text");
	}

	BOOST_AUTO_TEST_CASE(should_not_insert_paragraph_if_position_is_incorrect)
	{
		BOOST_REQUIRE_THROW(document.InsertParagraph("text", 10), std::invalid_argument);
	}

	BOOST_AUTO_TEST_SUITE(should_not_insert_image)

		BOOST_AUTO_TEST_CASE(if_position_is_incorrect)
		{
			BOOST_REQUIRE_THROW(document.InsertImage("resources/amanita.png", 100, 100, 10), std::invalid_argument);
		}

		BOOST_AUTO_TEST_CASE(if_path_is_incorrect)
		{
			BOOST_REQUIRE_THROW(document.InsertImage("resources/1.png", 100, 100, 0), boost::filesystem::filesystem_error);
			BOOST_REQUIRE_THROW(document.InsertImage("resources/tmp.txt", 100, 100, 0), std::logic_error);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(can_insert_image)
	{
		document.InsertImage("resources/amanita.png", 100, 150);

		BOOST_REQUIRE(document.GetItem(0).GetImage() != nullptr);

		BOOST_CHECK_EQUAL(document.GetItemsCount(), 1);
		BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetHeight(), 150);

		BOOST_CHECK_EQUAL(document.GetItem(0).GetImage()->GetWidth(), 100);

		BOOST_CHECK(boost::filesystem::exists(document.GetItem(0).GetImage()->GetPath()));
	}
	BOOST_AUTO_TEST_CASE(can_remove_item)
	{
		document.InsertParagraph("first");
		document.InsertImage("resources/amanita.png", 100, 150);
		document.InsertParagraph("third");

		BOOST_CHECK_EQUAL(document.GetItemsCount(), 3);
		BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");
		BOOST_REQUIRE(document.GetItem(1).GetImage() != nullptr);
		BOOST_CHECK_EQUAL(document.GetItem(2).GetParagraph()->GetText(), "third");
		document.DeleteItem(1);
		BOOST_CHECK_EQUAL(document.GetItemsCount(), 2);
		BOOST_CHECK_EQUAL(document.GetItem(0).GetParagraph()->GetText(), "first");
		BOOST_CHECK_EQUAL(document.GetItem(1).GetParagraph()->GetText(), "third");
	}

	BOOST_AUTO_TEST_CASE(can_save_to_html)
	{
		boost::filesystem::path path = "tmp/index.html";

		BOOST_CHECK(!boost::filesystem::exists(path));

		HtmlToFileSerializer serializer(path);

		document.Save(serializer);
		BOOST_CHECK(boost::filesystem::exists(path));

		boost::filesystem::remove_all(path);
	}

BOOST_AUTO_TEST_SUITE_END()
