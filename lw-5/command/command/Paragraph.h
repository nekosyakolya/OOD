#pragma once
#include "ICommandHistory.h"
#include "IParagraph.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(ICommandHistory& history, const std::string& text);
	std::string GetText() const override;
	void SetText(const std::string& text) override;

private:
	std::string m_text;
	ICommandHistory& m_history;
};
