#pragma once
#include "IStyle.h"
using FillStyleCallBack = std::function<void(IStyle &style)>;
using FillStyleEnumerator = std::function<void(const FillStyleCallBack & callBack)>;

class CompositeStyle : public IStyle
{
public:
	CompositeStyle(FillStyleEnumerator & enumerator);
	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor()const override;
	void SetColor(RGBAColor color) override;

private:
	FillStyleEnumerator & m_enumerator;
};
