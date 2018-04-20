#include "stdafx.h"
#include "CDesigner.h"

CDesigner::CDesigner(IShapeFactory& factory)
	: m_factory(factory)
{
}

CPictureDraft CDesigner::CreateDraft(std::istream& strm)
{
	CPictureDraft result;

	std::string description;
	while (std::getline(strm, description))
	{
		try
		{
			auto shape = m_factory.CreateShape(description);
			result.AddShape(move(shape));
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what();
		}
	}

	return result;
}
