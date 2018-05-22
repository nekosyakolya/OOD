#include "stdafx.h"
#include "Paragraph.h"


CParagraph::CParagraph(CCommandHistory & history):
	m_history(history)
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string & text)
{
	m_text = text;
}

CParagraph::~CParagraph()
{
}
