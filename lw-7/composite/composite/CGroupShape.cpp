#include "stdafx.h"
#include "CGroupShape.h"

CGroupShape::~CGroupShape()
{
}

void CGroupShape::Draw(ICanvas & canvas)
{
	for (auto &shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

boost::optional<size_t> CGroupShape::GetShapesCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	//set frame, set styles
	m_shapes.emplace(m_shapes.cbegin() + position, shape);
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	//set frame, set styles
	return std::shared_ptr<IShape>(m_shapes.at(index));
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	m_shapes.erase(m_shapes.cbegin() + index);
}

RectD CGroupShape::GetFrame() const
{
	return m_rect;
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return std::shared_ptr<IGroupShape>(this);
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return std::shared_ptr<const IGroupShape>(this);
}
