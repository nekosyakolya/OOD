#include "stdafx.h"
#include "Editor.h"
#include "Document.h"

CEditor::CEditor()
	: m_document(std::make_unique<CDocument>())
{
}

void CEditor::Run()
{
	Help(std::cin);

	std::string command;
	while ((std::cout << ">") && std::getline(std::cin, command))
	{
		try
		{
			std::istringstream str(command);
			std::string name;
			str >> name;

			auto it = std::find_if(EDITOR_COMMANDS.cbegin(), EDITOR_COMMANDS.cend(), [&](const EditorCommand& item) {
				return item.name == name;
			});

			if (it == EDITOR_COMMANDS.end())
			{
				throw std::logic_error("Unknown command");
			}
			it->command(str);

		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

CEditor::~CEditor()
{
}

void CEditor::InsertParagraph(std::istream& input)
{
	std::string text;
	std::string position;
	if (!((input >> position) && std::getline(input, text)))
	{
		throw std::logic_error("Incorrect arguments\nUsage: InsertParagraph <position> | end <text>");
	}

	boost::optional<size_t> index = boost::none;
	if (position != "end")
	{
		std::stringstream s(position);
		size_t tmp = 0;

		if (!(s << tmp))
		{
			throw std::logic_error("Invalid arguments format");
		}
		index.emplace(tmp);
	}
	boost::algorithm::trim_left(text);

	m_document->InsertParagraph(text, index);
}

void CEditor::InsertImage(std::istream& input)
{
	int width = 0;
	int height = 0;
	std::string path;
	std::string position;

	if (!((input >> position) && (input >> width) && (input >> height) && (std::getline(input, path))))
	{
		throw std::logic_error("Incorrect arguments\nUsage: InsertImage <position> | end <width> <height> <path>");
	}

	boost::optional<size_t> index = boost::none;
	if (position != "end")
	{
		size_t tmp = 0;
		std::stringstream s(position);
		if (!(s << tmp))
		{
			throw std::logic_error("Invalid arguments format");
		}
		index.emplace(tmp);
	}
	boost::algorithm::trim_left(path);
	m_document->InsertImage(boost::filesystem::path(path), width, height, index);
}

void CEditor::SetTitle(std::istream& input)
{
	std::string title;
	std::getline(input, title);
	boost::algorithm::trim_left(title);

	m_document->SetTitle(title);
}

void CEditor::ReplaceText(std::istream& input)
{
	size_t index;
	std::string text;

	if (!((input >> index) && std::getline(input, text)))
	{
		throw std::logic_error("Incorrect arguments\nUsage: ReplaceText <position> <text>");
	}
	auto paragraph = m_document->GetItem(index).GetParagraph();

	if (!paragraph)
	{
		throw std::logic_error("Element is not paragraph");
	}
	boost::algorithm::trim_left(text);
	paragraph->SetText(text);
}

void CEditor::ResizeImage(std::istream& input)
{
	size_t index;
	int width = 0;
	int height = 0;

	if (!((input >> index) && (input >> width) && (input >> height)))
	{
		throw std::logic_error("Incorrect arguments\nUsage: ResizeImage <position> <width> <height>");
	}
	auto image = m_document->GetItem(index).GetImage();

	if (!image)
	{
		throw std::logic_error("Element is not image");
	}
	image->Resize(width, height);
}

void CEditor::DeleteItem(std::istream& input)
{
	size_t index;
	if (!(input >> index))
	{
		throw std::logic_error("Incorrect arguments\nUsage: DeleteItem <position>");
	}

	m_document->DeleteItem(index);
}

void CEditor::Save(std::istream& input)
{
	std::string path;
	std::getline(input, path);
	boost::algorithm::trim_left(path);

	m_document->Save(path);
}

void CEditor::Redo(std::istream&)
{
	if (!m_document->CanRedo())
	{
		throw std::logic_error("Can't redo");
	}
	m_document->Redo();
}

void CEditor::Undo(std::istream&)
{
	if (!m_document->CanUndo())
	{
		throw std::logic_error("Can't undo");
	}
	m_document->Undo();
}

void CEditor::List(std::istream&)
{
	std::cout << "Title: " << m_document->GetTitle() << std::endl;
	auto size = m_document->GetItemsCount();
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << i << ". ";
		auto item = m_document->GetItem(i);

		if (auto paragraph = item.GetParagraph())
		{
			std::cout << "Paragraph: " << paragraph->GetText() << std::endl;
		}

		if (auto image = item.GetImage())
		{
			std::cout << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << std::endl;
		}
	}
}

void CEditor::Help(std::istream&)
{
	std::cout << "Editor commands list:" << std::endl;

	for (auto& item : EDITOR_COMMANDS)
	{
		std::cout << item.name << ": " << item.description << std::endl;
	}
}
