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
	std::unique_ptr<CTriangle> CreateTriangle(std::istringstream& stream) const;
	std::unique_ptr<CRectangle> CreateRectangle(std::istringstream& stream) const;
	std::unique_ptr<CEllipse> CreateEllipse(std::istringstream& stream) const;
	std::unique_ptr<CRegularPolygon> CreateRegularPolygon(std::istringstream& stream) const;

	using ShapeCreator = std::function<std::unique_ptr<CShape>(std::istringstream& stream)>;

	const std::unordered_map<std::string, ShapeCreator> SHAPES_CREATOR = {
		{ "triangle", std::bind(&CShapeFactory::CreateTriangle, this, std::placeholders::_1) },
		{ "rectangle", std::bind(&CShapeFactory::CreateRectangle, this, std::placeholders::_1) },
		{ "ellipse", std::bind(&CShapeFactory::CreateEllipse, this, std::placeholders::_1) },
		{ "regularPolygon", std::bind(&CShapeFactory::CreateRegularPolygon, this, std::placeholders::_1) }
	};
};
