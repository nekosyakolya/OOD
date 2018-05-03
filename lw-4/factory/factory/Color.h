#pragma once
#include <iostream>
#include <sstream>
#include <unordered_map>

enum class Color
{
	GREEN,
	RED,
	BLUE,
	YELLOW,
	PINK,
	BLACK
};

inline std::istream& operator>>(std::istream& str, Color& color)
{

	const std::unordered_map<std::string, Color> STRING_TO_COLOR = {
		{ "green", Color::GREEN },
		{ "red", Color::RED },
		{ "blue", Color::BLUE },
		{ "yellow", Color::YELLOW },
		{ "pink", Color::PINK },
		{ "black", Color::BLACK }
	};
	std::string value;
	if (str >> value)
	{
		auto result = STRING_TO_COLOR.find(value);
		if (result == STRING_TO_COLOR.end())
		{
			throw std::invalid_argument("Incorrect name of color\n");
		}

		color = result->second;
	}

	return str;
}

inline std::ostream& operator<<(std::ostream& str, const Color& value)
{
	std::string color = "";

	const std::unordered_map<Color, std::string> COLOR_TO_STRING = {
		{ Color::GREEN, "green" },
		{ Color::RED, "red" },
		{ Color::BLUE, "blue" },
		{ Color::YELLOW, "yellow" },
		{ Color::PINK, "pink" },
		{ Color::BLACK, "black" }
	};

	auto result = COLOR_TO_STRING.find(value);
	if (result != COLOR_TO_STRING.end())
	{
		color = result->second;
	}

	str << color;

	return str;
}
