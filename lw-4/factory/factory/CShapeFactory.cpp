#include "stdafx.h"
#include "CShapeFactory.h"

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string& description)
{
	std::istringstream stream(description);

	std::string shapeName;
	stream >> shapeName;

	auto result = SHAPES_CREATOR.find(shapeName);

	if (result == SHAPES_CREATOR.end())
	{
		throw std::invalid_argument("Incorrect name of shape\n");
	}

	return result->second(stream);
}

std::unique_ptr<CTriangle> CShapeFactory::CreateTriangle(std::istringstream& stream) const
{
	Point first;
	Point second;
	Point third;

	Color color;

	if (!(stream >> first.x >> first.y >> second.x >> second.y >> third.x >> third.y >> color))
	{
		throw std::invalid_argument("Incorrect number of arguments\n");
	}

	return std::make_unique<CTriangle>(first, second, third, color);
}

std::unique_ptr<CRectangle> CShapeFactory::CreateRectangle(std::istringstream& stream) const
{
	Point leftTop;
	Point rightBottom;

	Color color;

	if (!(stream >> leftTop.x >> leftTop.y >> rightBottom.x >> rightBottom.y >> color))
	{
		throw std::invalid_argument("Incorrect number of arguments\n");
	}

	return std::make_unique<CRectangle>(leftTop, rightBottom, color);
}

std::unique_ptr<CEllipse> CShapeFactory::CreateEllipse(std::istringstream& stream) const
{
	Point center;
	float horizontalRadius = 0;
	float verticalRadius = 0;
	Color color;

	if (!(stream >> center.x >> center.y >> horizontalRadius >> verticalRadius >> color))
	{
		throw std::invalid_argument("Incorrect number of arguments\n");
	}

	return std::make_unique<CEllipse>(center, horizontalRadius, verticalRadius, color);
}

std::unique_ptr<CRegularPolygon> CShapeFactory::CreateRegularPolygon(std::istringstream& stream) const
{
	Point center;
	float radius = 0;
	size_t vertexCount = 0;
	Color color;

	if (!(stream >> center.x >> center.y >> radius >> vertexCount >> color))
	{
		throw std::invalid_argument("Incorrect number of arguments\n");
	}

	return std::make_unique<CRegularPolygon>(center, radius, vertexCount, color);
}
