#pragma once

#include "CShape.h"
#include <boost/iterator/indirect_iterator.hpp>
#include <memory>
#include <string>
#include <vector>

class CPictureDraft
{
public:
	using Storage = std::vector<std::unique_ptr<CShape>>;

	using ConstIterator = boost::indirect_iterator<Storage::const_iterator, const CShape&>;

	CPictureDraft();

	bool IsEmpty() const;
	size_t GetShapeCount() const;

	ConstIterator begin() const;

	ConstIterator end() const;

	void AddShape(std::unique_ptr<CShape>&& shape);
	CPictureDraft(CPictureDraft&&) = default;
	CPictureDraft& operator=(CPictureDraft&&) = default;

	CPictureDraft(const CPictureDraft&) = delete;
	CPictureDraft& operator=(const CPictureDraft&) = delete;

	~CPictureDraft();

private:
	Storage m_shapes;
};
