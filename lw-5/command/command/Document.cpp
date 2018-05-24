#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertParagraph.h"
#include "DeleteItem.h"
#include "InsertImage.h"
#include "SaveDocumentToHtml.h"


void CDocument::SetTitle(const std::string & title)
{
	m_history.SetAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();

}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (index >= m_items.size())
	{
		throw std::logic_error("Index should be less than the size of the document");
	}
	return m_items[index];
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (index >= m_items.size())
	{
		throw std::logic_error("Index should be less than the size of the document");
	}
	return m_items[index];
}

void CDocument::Save(const boost::filesystem::path & path) const
{
	CSaveDocumentToHtml save(path, *this);
	save.Execute();


}

void CDocument::DeleteItem(size_t index)
{
	m_history.SetAndExecuteCommand(std::make_unique<CDeleteItem>(m_items, index));

}

std::shared_ptr<IImage> CDocument::InsertImage(const boost::filesystem::path & path, int width, int height, boost::optional<size_t> position)
{
	m_history.SetAndExecuteCommand(std::make_unique<CInsertImage>(m_history, m_items, path, width, height, position));

	size_t index = m_items.size() - 1;



	if (position != boost::none)
	{
		index = position.get();
	}

	return m_items[index].GetImage();
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string & text, boost::optional<size_t> position)
{
	m_history.SetAndExecuteCommand(std::make_unique<CInsertParagraph>(m_history, m_items, text, position));

	size_t index = m_items.size() - 1;



	if (position != boost::none)
	{
		index = position.get();
	}

	return m_items[index].GetParagraph();
}


