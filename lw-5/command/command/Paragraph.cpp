#include "stdafx.h"
#include "Paragraph.h"
#include "ChangeStringCommand.h"

CParagraph::CParagraph(CCommandHistory& history)
	: m_history(history)
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string& text)
{
	m_history.SetAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_text, text));
}

CParagraph::~CParagraph()
{
}
