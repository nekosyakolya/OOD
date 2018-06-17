#pragma once

#include "IDrawable.h"
#include "IStyle.h"
#include "ILineStyle.h"

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual ILineStyle & GetOutlineStyle() = 0;
	virtual const ILineStyle & GetOutlineStyle()const = 0;
	virtual void SetOutlineStyle(const ILineStyle &) = 0;


	virtual IStyle & GetFillStyle() = 0;
	virtual const IStyle & GetFillStyle()const = 0;
	virtual void SetFillStyle(const IStyle &) = 0;


	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual ~IShape() = default;
};


