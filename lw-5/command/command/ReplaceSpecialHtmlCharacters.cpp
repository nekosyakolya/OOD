#include "stdafx.h"
#include "ReplaceSpecialHtmlCharacters.h"

const std::vector<std::pair<std::string, std::string>> CReplaceSpecialHtmlCharacters::CHARACTERS_TABLE = {
	{ "&", "&amp;" },
	{ "\"", "&quot;" },
	{ "\'", "&apos;" },
	{ "<", "&lt;" },
	{ ">", "&gt;" }
};

CReplaceSpecialHtmlCharacters::CReplaceSpecialHtmlCharacters()
{
}

void CReplaceSpecialHtmlCharacters::Execute(std::string& text)
{
	for (auto &it : CHARACTERS_TABLE)
	{
		boost::algorithm::replace_all(text, it.first, it.second);
	}
}

CReplaceSpecialHtmlCharacters::~CReplaceSpecialHtmlCharacters()
{
}
