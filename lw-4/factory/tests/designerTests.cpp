#include "stdafx.h"
#include "../factory/CShapeFactory.h"
#include "../factory/IDesigner.h"
#include "../factory/IShapeFactory.h"

namespace
{
class TestDesigner : public IDesigner
{
public:
	TestDesigner(IShapeFactory& factory, std::stringstream& stream)
		: m_factory(factory)
		, m_stream(stream)
	{
	}

	CPictureDraft CreateDraft(std::istream& strm)
	{
		CPictureDraft result;
		std::string description;
		while (std::getline(strm, description))
		{
			try
			{
				auto shape = m_factory.CreateShape(description);
				result.AddShape(std::move(shape));
				m_stream << description << std::endl;
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
		return result;
	}

private:
	IShapeFactory& m_factory;
	std::stringstream& m_stream;
};

struct Designer_
{
	CShapeFactory factory;
	TestDesigner designer;
	std::stringstream stream;
	Designer_()
		: factory(CShapeFactory())
		, designer(factory, stream)
	{
	}
};

} // namespace

BOOST_FIXTURE_TEST_SUITE(Designer, Designer_)

	BOOST_AUTO_TEST_CASE(can_create_draft)
	{
		std::vector<std::string> shapeDescriptions = {
			"rectangle 10 10 180 180 red",
			"triangle 20 40 60 80 80 40 green",
			"ellipse 500 300 20 50 pink",
			"regularPolygon 300 500 20 8 black"
		};

		std::stringstream str;
		for (auto description : shapeDescriptions)
		{
			str << description << std::endl;
		}

		auto draft = designer.CreateDraft(str);
		BOOST_CHECK(!draft.IsEmpty());
		BOOST_CHECK_EQUAL(stream.str(), "rectangle 10 10 180 180 red\ntriangle 20 40 60 80 80 40 green\nellipse 500 300 20 50 pink\nregularPolygon 300 500 20 8 black\n");
	}

	BOOST_AUTO_TEST_CASE(returns_empty_draft_if_stream_is_empty)
	{
		std::istringstream stream;
		auto draft = designer.CreateDraft(stream);
		BOOST_CHECK(draft.IsEmpty());
	}
BOOST_AUTO_TEST_SUITE_END()
