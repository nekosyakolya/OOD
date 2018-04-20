#pragma once
#include "IShapeFactory.h"

#include "CEllipse.h"
#include "CRectangle.h"
#include "CRegularPolygon.h"
#include "CShape.h"
#include "CTriangle.h"
#include <functional>

class CShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(const std::string& description) override;

private:
	std::unique_ptr<CTriangle> TriangleExtractor(std::istringstream& stream) const;
	std::unique_ptr<CRectangle> RectangleExtractor(std::istringstream& stream) const;
	std::unique_ptr<CEllipse> EllipseExtractor(std::istringstream& stream) const;
	std::unique_ptr<CRegularPolygon> RegularPolygonExtractor(std::istringstream& stream) const;

	using ShapeCreator = std::function<std::unique_ptr<CShape>(std::istringstream& stream)>;

	const std::unordered_map<std::string, ShapeCreator> SHAPES_CREATOR = {
		{ "triangle", std::bind(&CShapeFactory::TriangleExtractor, this, std::placeholders::_1) },
		{ "rectangle", std::bind(&CShapeFactory::RectangleExtractor, this, std::placeholders::_1) },
		{ "ellipse", std::bind(&CShapeFactory::EllipseExtractor, this, std::placeholders::_1) },
		{ "regularPolygon", std::bind(&CShapeFactory::RegularPolygonExtractor, this, std::placeholders::_1) }
	};
};
