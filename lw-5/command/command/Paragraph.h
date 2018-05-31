#pragma once
#include "IParagraph.h"
#include "IInvoker.h"

class CParagraph : public IParagraph
{
public:
	CParagraph(IInvoker& history);
	std::string GetText() const override;
	void SetText(const std::string& text) override;
	~CParagraph();

private:
	std::string m_text;
	IInvoker& m_history;
};
