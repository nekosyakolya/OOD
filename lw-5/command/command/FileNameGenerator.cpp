#include "stdafx.h"
#include "FileNameGenerator.h"

const std::string CFileNameGenerator::ALPHABET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
CFileNameGenerator::CFileNameGenerator()
{
	srand((unsigned)time(NULL));

}

std::string CFileNameGenerator::Execute()
{
	std::string result = "";
	auto size = rand() % 14 + 6;
	for (int i = 0; i != size; ++i)
	{
		auto index = rand() % ALPHABET.size();
		result += ALPHABET[index];

	}
	return result;
}


CFileNameGenerator::~CFileNameGenerator()
{
}
