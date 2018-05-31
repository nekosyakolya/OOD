#pragma once

class CReplaceSpecialHtmlCharacters
{
public:
	static void Execute(std::string& text);

private:
	const static std::vector<std::pair<std::string, std::string>> CHARACTERS_TABLE;
};
