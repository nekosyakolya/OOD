#pragma once
#include "AbstractCommand.h"
#include "CDocumentItem.h"

#include "CCommandHistory.h"

class CInsertParagraph :
	public CAbstractCommand
{
public:
	CInsertParagraph(CCommandHistory &history, std::vector<CDocumentItem>& items, const std::string& text, boost::optional<size_t> position);
private:
	void DoExecute() override;
	void DoUnexecute() override;
	std::vector<CDocumentItem> &m_items;
	boost::optional<size_t> m_position;
	std::shared_ptr<IParagraph> m_paragraph;

	void InitializationParagraph(CCommandHistory &history, const std::string& text);
};

