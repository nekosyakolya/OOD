#pragma once

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

using RectD = Rect<double>;
using RGBAColor = uint32_t;
