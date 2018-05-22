#pragma once
#include "IParagraph.h"
#include "CCommandHistory.h"
class CParagraph :
	public IParagraph
{
public:
	CParagraph(CCommandHistory & history);
	std::string GetText() const override;
	void SetText(const std::string& text)override;
	~CParagraph();
private:
	std::string m_text;
	CCommandHistory &m_history;
};

