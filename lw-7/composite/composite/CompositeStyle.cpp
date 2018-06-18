#include "stdafx.h"
#include "CompositeStyle.h"


CompositeStyle::CompositeStyle(FillStyleEnumerator & enumerator):
	m_enumerator(enumerator)
{
}

boost::optional<bool> CompositeStyle::IsEnabled() const
{
	boost::optional<bool> isEnabled;

	auto callback = [&](IStyle& style) {
		if (!isEnabled)
		{
			isEnabled = style.IsEnabled();
		}
		else if (isEnabled != style.IsEnabled())
		{
			isEnabled = boost::none;
		}
	};

	m_enumerator(callback);

	return isEnabled;
}

void CompositeStyle::Enable(bool enable)
{
	auto callback = [&](IStyle& style) {
		style.Enable(enable);
	};

	m_enumerator(callback);
}

boost::optional<RGBAColor> CompositeStyle::GetColor() const
{
	boost::optional<RGBAColor> rgbaColor;

	auto callback = [&](IStyle& style) {
		if (!rgbaColor)
		{
			rgbaColor = style.GetColor();
		}
		else if (rgbaColor != style.GetColor())
		{
			rgbaColor = boost::none;
		}
	};

	m_enumerator(callback);

	return rgbaColor;
}

void CompositeStyle::SetColor(RGBAColor color)
{
	auto callback = [&](IStyle& style) {
		style.SetColor(color);
	};

	m_enumerator(callback);
}
