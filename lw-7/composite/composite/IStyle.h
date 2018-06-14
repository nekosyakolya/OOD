#pragma once


class IStyle
{
public:
	virtual boost::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual boost::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual ~IStyle() = default;
};
