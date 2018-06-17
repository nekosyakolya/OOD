#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;

	ILineStyle & GetOutlineStyle() override;
	const ILineStyle & GetOutlineStyle()const override;
	void SetOutlineStyle(const ILineStyle &) override;

	IStyle & GetFillStyle() override;
	const IStyle & GetFillStyle()const override;
	void SetFillStyle(const IStyle &) override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	virtual ~CShape() = default;
private:
	RectD m_rect;
	IStyle & m_style;
	ILineStyle &m_lineStyle;
};

