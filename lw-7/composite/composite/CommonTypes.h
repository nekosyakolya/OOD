#pragma once

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
	bool Rect::operator!=(const Rect& rect)
	{
		return rect.left != left && rect.top != top && rect.width != width && rect.height != height;
	}
};

using RectD = Rect<double>;
using RGBAColor = uint32_t;
