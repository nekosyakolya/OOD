#pragma once
#include "stdafx.h"
class CFileNameGenerator
{
public:
	CFileNameGenerator();
	static std::string Execute();
	~CFileNameGenerator();
private:
	const static std::string ALPHABET;
};

