#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertParagraph.h"
#include "DeleteItem.h"


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
	for (size_t i = 0; i < m_items.size(); ++i)
	{
		std::cout << i << " " << GetItem(i).GetParagraph()->GetText() << std::endl;
		if (GetItem(i).GetImage() == nullptr)
		{
			std::cout << "img null " << std::endl;
		}
	}
	std::cout << "-------------------------------------- " << std::endl;

}

void CDocument::DeleteItem(size_t index)
{
	CDeleteItem command(m_items, index);
	m_history.SetAndExecuteCommand(std::make_unique<CDeleteItem>(command));

}

std::shared_ptr<IImage> CDocument::InsertImage(const boost::filesystem::path & path, int width, int height, boost::optional<size_t> position)
{
	return std::shared_ptr<IImage>();
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string & text, boost::optional<size_t> position)
{
	CInsertParagraph command(m_history, m_items, text, position);
	m_history.SetAndExecuteCommand(std::make_unique<CInsertParagraph>(command));

	size_t index = m_items.size() - 1;



	if (position != boost::none)
	{
		index = position.get();
	}

	return m_items[index].GetParagraph();
}


