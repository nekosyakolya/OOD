#pragma once
#include "IGroupShape.h"

class CGroupShape : public IGroupShape
{
public:
	~CGroupShape();
	void Draw(ICanvas & canvas) override;
	boost::optional<size_t> GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	RectD GetFrame() const override;
	void SetFrame(const RectD & rect) override;

	ILineStyle & GetOutlineStyle() override;
	const ILineStyle & GetOutlineStyle() const override;
	void SetOutlineStyle(const ILineStyle &) override;

	IStyle & GetFillStyle() override;
	const IStyle & GetFillStyle()const override;
	void SetFillStyle(const IStyle &) override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	RectD m_rect;
};
