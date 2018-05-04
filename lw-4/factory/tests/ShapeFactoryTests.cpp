#include "stdafx.h"
#include "../factory/CShapeFactory.h"

namespace
{
struct ShapeFactory_
{
	CShapeFactory factory;
};

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
		BOOST_CHECK(triangle != nullptr);
	}

	BOOST_AUTO_TEST_CASE(can_create_rectangle)
	{
		std::string line = "rectangle 10 30 50 60 blue";
		auto shape = factory.CreateShape(line);
		CRectangle* rectangle = dynamic_cast<CRectangle*>(shape.get());
		BOOST_CHECK(rectangle != nullptr);
	}
	BOOST_AUTO_TEST_CASE(can_create_ellipse)
	{
		std::string line = "ellipse 500 300 20 50 pink";
		auto shape = factory.CreateShape(line);
		CEllipse* ellipse = dynamic_cast<CEllipse*>(shape.get());
		BOOST_CHECK(ellipse != nullptr);
	}
	BOOST_AUTO_TEST_CASE(can_create_regular_polygon)
	{
		std::string line = "regularPolygon 300 500 20 8 black";
		auto shape = factory.CreateShape(line);
		CRegularPolygon* regularPolygon = dynamic_cast<CRegularPolygon*>(shape.get());
		BOOST_CHECK(regularPolygon != nullptr);
	}

BOOST_AUTO_TEST_SUITE_END()
