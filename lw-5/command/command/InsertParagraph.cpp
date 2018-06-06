#include "stdafx.h"
#include "InsertParagraph.h"
#include "Paragraph.h"

CInsertParagraph::CInsertParagraph(std::shared_ptr<IParagraph>&& paragraph, std::vector<CDocumentItem>& items, boost::optional<size_t> position)
	: m_items(items)
	, m_position(position)
	, m_paragraph(paragraph)
{
}

void CInsertParagraph::DoExecute()
{
	if (m_position == boost::none)
	{

		m_items.emplace_back(CDocumentItem(nullptr, m_paragraph));
	}
	else if (m_position > m_items.size())
	{
		throw std::invalid_argument("Index should be less than the size of the document");
	}
	else
	{
		m_items.emplace(m_items.begin() + m_position.get(), CDocumentItem(nullptr, m_paragraph));
	}
}

void CInsertParagraph::DoUnexecute()
{
	if (m_position == boost::none)
	{
		m_items.pop_back();
	}
	else
	{
		m_items.erase(m_items.begin() + m_position.get());
	}
}
