#include "stdafx.h"
#include "../factory/CEllipse.h"

namespace
{
class CTestCanvas : public ICanvas
{
public:
	CTestCanvas(std::stringstream& stream)
		: m_stream(stream)
	{
	}

	void SetColor(const Color& color) override
	{
		m_color = color;
		m_stream << "Color: " << m_color << std::endl;
	}
	void DrawLine(const Point& from, const Point& to) override
	{
		m_stream << "From (" << from.x << ", " << from.y << ")" << std::endl;
		m_stream << "To (" << to.x << ", " << to.y << ")" << std::endl;
	}
	void DrawEllipse(float left, float top, float width, float height) override
	{
		m_stream << "Left top (" << left << ", " << top << ")" << std::endl;
		m_stream << "width:" << width << std::endl;
		m_stream << "height:" << height << std::endl;
	}

private:
	std::stringstream& m_stream;
	Color m_color;
};

struct Ellipse_
{
	const Point expectedPoint{ 150, 150 };
	const float expectedHorizontalRadius = 20;
	const float expectedVerticalRadius = 50;
	const Color expectedColor = Color::GREEN;
	const CEllipse ellipse;
	Ellipse_()
		: ellipse(expectedPoint, expectedHorizontalRadius, expectedVerticalRadius, expectedColor)
	{
	}
};

bool operator==(const Point& p1, const Point& p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

} // namespace

BOOST_FIXTURE_TEST_SUITE(Ellipse, Ellipse_)

	BOOST_AUTO_TEST_CASE(has_a_center)
	{
		BOOST_CHECK(ellipse.GetCenter() == expectedPoint);
	}

	BOOST_AUTO_TEST_CASE(has_a_horizontal_radius)
	{
		BOOST_CHECK_EQUAL(ellipse.GetHorizontalRadius(), expectedHorizontalRadius);
	}

	BOOST_AUTO_TEST_CASE(has_a_vertical_radius)
	{
		BOOST_CHECK_EQUAL(ellipse.GetVerticalRadius(), 50);
	}

	BOOST_AUTO_TEST_CASE(has_a_color)
	{
		BOOST_CHECK_EQUAL(ellipse.GetColor(), Color::GREEN);
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas)
	{
		std::stringstream str;
		CTestCanvas canvas(str);
		ellipse.Draw(canvas);

		BOOST_CHECK_EQUAL(str.str(), "Color: green\nLeft top (130, 100)\nwidth:40\nheight:100\n");
	}

BOOST_AUTO_TEST_SUITE_END()
