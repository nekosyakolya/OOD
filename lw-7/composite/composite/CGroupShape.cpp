#include "stdafx.h"
#include "CGroupShape.h"

CGroupShape::CGroupShape():
	m_rect({ std::numeric_limits<double>::max(),
		std::numeric_limits<double>::max(),
		std::numeric_limits<double>::min(),
		std::numeric_limits<double>::min()})
{
}

CGroupShape::~CGroupShape()
{
}

void CGroupShape::Draw(ICanvas & canvas)
{
	for (auto &&shape : m_shapes)
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
	m_shapes.emplace(m_shapes.cbegin() + position, shape);
	//set frame, set styles

	SetGroupFrame(shape->GetFrame());
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	return std::shared_ptr<IShape>(m_shapes.at(index));
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	//set frame, set styles
	m_shapes.erase(m_shapes.cbegin() + index);
	for (auto &shape : m_shapes)
	{
		SetGroupFrame(shape->GetFrame());
	}

	if (m_shapes.empty())
	{
		m_rect = { std::numeric_limits<double>::max(),
			std::numeric_limits<double>::max(),
			std::numeric_limits<double>::min(),
			std::numeric_limits<double>::min() };
	}
}

RectD CGroupShape::GetFrame() const
{
	return m_rect;
}

void CGroupShape::SetFrame(const RectD & rect)
{
	if (m_rect != rect)
	{
		auto coefficientLeft = rect.left / m_rect.left;
		auto coefficientTop = rect.top / m_rect.top;
		auto coefficientWidth = rect.width / m_rect.width;
		auto coefficientHeight = rect.height / m_rect.height;

		for (auto &shape : m_shapes)
		{
			auto newRect = shape->GetFrame();
			newRect.left *= coefficientLeft;
			newRect.top *= coefficientTop;
			newRect.width *= coefficientWidth;
			newRect.height *= coefficientHeight;

			shape->SetFrame(newRect);
		}

		m_rect = rect;
	}
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return std::shared_ptr<IGroupShape>(this);
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return std::shared_ptr<const IGroupShape>(this);
}

void CGroupShape::SetGroupFrame(const RectD & rect)
{
	RectD tmp = rect;
	if (tmp.left < m_rect.left)
	{
		std::swap(m_rect.left, tmp.left);
	}

	if (tmp.top < m_rect.top)
	{
		std::swap(m_rect.top, tmp.top);
	}

	if (tmp.width > m_rect.width)
	{
		std::swap(m_rect.width, tmp.width);
	}

	if (tmp.height > m_rect.height)
	{
		std::swap(m_rect.height, tmp.height);
	}
}
