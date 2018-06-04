#pragma once
#include "AbstractCommand.h"
#include "CDocumentItem.h"

class CInsertParagraph : public CAbstractCommand
{
public:
	CInsertParagraph(std::shared_ptr<IParagraph>&& paragraph, std::vector<CDocumentItem>& items, boost::optional<size_t> position);

private:
	void DoExecute() override;
	void DoUnexecute() override;

	std::vector<CDocumentItem>& m_items;
	boost::optional<size_t> m_position;
	std::shared_ptr<IParagraph> m_paragraph;
};
