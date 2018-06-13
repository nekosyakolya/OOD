#include "stdafx.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "DeleteItem.h"
#include "IDocumentSerializer.h"
#include "InsertImage.h"
#include "InsertParagraph.h"
#include "Paragraph.h"

void CDocument::SetTitle(const std::string& title)
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
	return m_items.at(index);
}

CDocumentItem CDocument::GetItem(size_t index)
{
	return m_items.at(index);
}

void CDocument::Save(const IDocumentSerializer& serializer) const
{
	serializer.Serialize(*this);
}

void CDocument::DeleteItem(size_t index)
{
	m_history.SetAndExecuteCommand(std::make_unique<CDeleteItem>(m_items, index));
}

std::shared_ptr<IImage> CDocument::InsertImage(const boost::filesystem::path& path, int width, int height, boost::optional<size_t> position)
{
	m_history.SetAndExecuteCommand(std::make_unique<CInsertImage>(m_history, m_items, path, width, height, TMP_DIRECTORY_NAME, position));

	size_t index = m_items.size() - 1;
	if (position != boost::none)
	{
		index = position.get();
	}

	return m_items[index].GetImage();
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, boost::optional<size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(m_history, text);
	m_history.SetAndExecuteCommand(std::make_unique<CInsertParagraph>(paragraph, m_items, position));

	size_t index = m_items.size() - 1;
	if (position != boost::none)
	{
		index = position.get();
	}

	return m_items[index].GetParagraph();
}

CDocument::~CDocument()
{
	try
	{
		boost::filesystem::remove_all(TMP_DIRECTORY_NAME);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
