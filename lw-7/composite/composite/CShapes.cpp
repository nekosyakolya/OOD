#include "stdafx.h"
#include "CShapes.h"

boost::optional<size_t> CShapes::GetShapesCount() const
{
	return boost::none;
}

void CShapes::InsertShape(const std::shared_ptr<IShape>&, size_t)
{
	throw std::logic_error("Incorrect operation");
}

std::shared_ptr<IShape> CShapes::GetShapeAtIndex(size_t)
{
	throw std::logic_error("Incorrect operation");
}

void CShapes::RemoveShapeAtIndex(size_t)
{
	throw std::logic_error("Incorrect operation");
}
