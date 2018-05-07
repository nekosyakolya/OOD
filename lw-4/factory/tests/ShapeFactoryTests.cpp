#include "stdafx.h"
#include "../factory/CShapeFactory.h"

namespace
{
struct ShapeFactory_
{
	CShapeFactory factory;
};

bool operator==(const Point& first, const Point& second)
{
	return first.x == second.x && first.y == second.y;
}

} // namespace
BOOST_FIXTURE_TEST_SUITE(ShapeFactory, ShapeFactory_)
	BOOST_AUTO_TEST_CASE(throws_exception_if_the_name_of_shape_is_incorrect)
	{
		std::string line = "riangle 10 30 50 60 20 40 red";
		BOOST_REQUIRE_THROW(factory.CreateShape(line), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(throws_exception_if_the_name_of_color_is_incorrect)
	{
		std::string line = "triangle 10 30 50 60 20 40 re";
		BOOST_REQUIRE_THROW(factory.CreateShape(line), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(throws_exception_if_the_number_of_arguments_is_incorrect)
	{
		std::string line = "triangle 10 30 50 60 20 40";
		BOOST_REQUIRE_THROW(factory.CreateShape(line), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_create_triangle)
	{
		std::string line = "triangle 10 30 50 60 20 40 red";
		auto shape = factory.CreateShape(line);
		CTriangle* triangle = dynamic_cast<CTriangle*>(shape.get());
		BOOST_REQUIRE(triangle != nullptr);

		const Point expectedFirst{ 10, 30 };
		const Point expectedSecond{ 50, 60 };
		const Point expectedThird{ 20, 40 };

		const Color expectedColor = Color::RED;

		BOOST_CHECK_EQUAL(triangle->GetColor(), expectedColor);
		BOOST_CHECK(triangle->GetVertex1() == expectedFirst);
		BOOST_CHECK(triangle->GetVertex2() == expectedSecond);
		BOOST_CHECK(triangle->GetVertex3() == expectedThird);
	}

	BOOST_AUTO_TEST_CASE(can_create_rectangle)
	{
		std::string line = "rectangle 10 30 50 60 blue";
		auto shape = factory.CreateShape(line);
		CRectangle* rectangle = dynamic_cast<CRectangle*>(shape.get());
		BOOST_REQUIRE(rectangle != nullptr);

		const Point expectedLeftTop{ 10, 30 };
		const Point expectedRightBottom{ 50, 60 };

		const Color expectedColor = Color::BLUE;

		BOOST_CHECK_EQUAL(rectangle->GetColor(), expectedColor);
		BOOST_CHECK(rectangle->GetLeftTop() == expectedLeftTop);
		BOOST_CHECK(rectangle->GetRightBottom() == expectedRightBottom);
	}
	BOOST_AUTO_TEST_CASE(can_create_ellipse)
	{
		std::string line = "ellipse 500 300 20 50 pink";
		auto shape = factory.CreateShape(line);
		CEllipse* ellipse = dynamic_cast<CEllipse*>(shape.get());
		BOOST_REQUIRE(ellipse != nullptr);

		const Point expectedPoint{ 500, 300 };
		const float expectedHorizontalRadius = 20;
		const float expectedVerticalRadius = 50;
		const Color expectedColor = Color::PINK;

		BOOST_CHECK_EQUAL(ellipse->GetColor(), expectedColor);
		BOOST_CHECK(ellipse->GetCenter() == expectedPoint);
		BOOST_CHECK_EQUAL(ellipse->GetHorizontalRadius(), expectedHorizontalRadius);

		BOOST_CHECK_EQUAL(ellipse->GetVerticalRadius(), expectedVerticalRadius);
	}
	BOOST_AUTO_TEST_CASE(can_create_regular_polygon)
	{
		std::string line = "regularPolygon 300 500 20 8 black";
		auto shape = factory.CreateShape(line);
		CRegularPolygon* regularPolygon = dynamic_cast<CRegularPolygon*>(shape.get());
		BOOST_REQUIRE(regularPolygon != nullptr);

		const Point expectedCenter{ 300, 500 };
		const float expectedRadius = 20;
		const size_t expectedVertexCount = 8;

		const Color expectedColor = Color::BLACK;

		BOOST_CHECK_EQUAL(regularPolygon->GetColor(), expectedColor);
		BOOST_CHECK(regularPolygon->GetCenter() == expectedCenter);

		BOOST_CHECK_EQUAL(regularPolygon->GetRadius(), expectedRadius);

		BOOST_CHECK_EQUAL(regularPolygon->GetVertexCount(), expectedVertexCount);
	}

BOOST_AUTO_TEST_SUITE_END()
