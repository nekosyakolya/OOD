#include "stdafx.h"
#include "../factory/CPictureDraft.h"
#include "../factory/CShape.h"

namespace
{
struct PictureDraft_
{
	CPictureDraft draft;
};

class TestEllipse : public CShape
{
public:
	TestEllipse()
		: CShape(Color::BLACK)
	{
	}
	void Draw(ICanvas& /*canvas*/) const override {}
};

class TestRectangle : public CShape
{
public:
	TestRectangle()
		: CShape(Color::BLACK)
	{
	}
	void Draw(ICanvas& /*canvas*/) const override {}
};

} // namespace

BOOST_FIXTURE_TEST_SUITE(PictureDraft, PictureDraft_)
	BOOST_AUTO_TEST_CASE(by_default_is_empty)
	{
		BOOST_CHECK(draft.IsEmpty());
	}

	BOOST_AUTO_TEST_CASE(after_adding_shapes_becomes_not_empty)
	{
		std::unique_ptr<CShape> shape1 = std::make_unique<TestEllipse>();
		std::unique_ptr<CShape> shape2 = std::make_unique<TestRectangle>();

		draft.AddShape(move(shape1));
		draft.AddShape(move(shape2));

		BOOST_CHECK(!draft.IsEmpty());
	}
BOOST_AUTO_TEST_SUITE_END()
