#pragma once
#include "IInvoker.h"
#include "IParagraph.h"

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
