#include "stdafx.h"
#include "CPictureDraft.h"

CPictureDraft::CPictureDraft()
{
}

bool CPictureDraft::IsEmpty() const
{
	return m_shapes.empty();
}

size_t CPictureDraft::GetShapeCount() const
{
	return m_shapes.size();
}

CPictureDraft::ConstIterator CPictureDraft::begin() const
{
	return m_shapes.begin();
}

CPictureDraft::ConstIterator CPictureDraft::end() const
{
	return m_shapes.end();
}

void CPictureDraft::AddShape(std::unique_ptr<CShape>&& shape)
{
	m_shapes.push_back(move(shape));
}

CPictureDraft::~CPictureDraft()
{
}
