#include "stdafx.h"
#include "../factory/CPainter.h"
#include "../factory/CPictureDraft.h"
#include "../factory/CShape.h"
namespace
{
class CTestCanvas : public ICanvas
{
public:
	CTestCanvas(std::stringstream& stream)
		: m_stream(stream)
	{
	}

	void SetColor(const Color& /*color*/) override
	{
	}
	void DrawLine(const Point& /*from*/, const Point& /*to*/) override
	{
		m_stream << "DrawLine" << std::endl;
	}
	void DrawEllipse(float /*left*/, float /*top*/, float /*width*/, float /*height*/) override
	{
		m_stream << "DrawEllipse" << std::endl;
	}

private:
	std::stringstream& m_stream;
};

class TestEllipse : public CShape
{
public:
	TestEllipse()
		: CShape(Color::BLACK)
	{
	}
	void Draw(ICanvas& canvas) const override { canvas.DrawEllipse(0, 0, 10, 10); }
};

class TestRectangle : public CShape
{
public:
	TestRectangle()
		: CShape(Color::BLACK)
	{
	}
	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine({ 0, 0 }, { 0, 10 });
		canvas.DrawLine({ 0, 10 }, { 10, 10 });
		canvas.DrawLine({ 10, 10 }, { 10, 0 });
		canvas.DrawLine({ 10, 0 }, { 0, 0 });
	}
};

} // namespace

BOOST_AUTO_TEST_SUITE(Painter)
	BOOST_AUTO_TEST_CASE(draws_shapes_in_order_of_adding_shapes)
	{
		std::stringstream strm;

		CTestCanvas canvas(strm);

		CPainter painter;
		CPictureDraft draft;

		draft.AddShape(std::make_unique<TestEllipse>());
		draft.AddShape(std::make_unique<TestRectangle>());

		painter.DrawPicture(draft, canvas);
		BOOST_CHECK_EQUAL(strm.str(), "DrawEllipse\nDrawLine\nDrawLine\nDrawLine\nDrawLine\n");
	}
BOOST_AUTO_TEST_SUITE_END()
