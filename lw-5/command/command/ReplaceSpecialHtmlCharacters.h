#pragma once
class CReplaceSpecialHtmlCharacters
{
public:
	CReplaceSpecialHtmlCharacters();
	static void Execute(std::string& text);
	~CReplaceSpecialHtmlCharacters();

private:
	const static std::vector<std::pair<std::string, std::string>> CHARACTERS_TABLE;
};
