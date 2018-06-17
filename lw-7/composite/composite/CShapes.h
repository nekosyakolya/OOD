#pragma once
#include "IShapes.h"

class CShapes : public IShapes
{
public:
	boost::optional<size_t> GetShapesCount() const override;
	void InsertShape(const std::shared_ptr<IShape> &, size_t) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t) override;
	void RemoveShapeAtIndex(size_t) override;

	~CShapes() = default;

};

