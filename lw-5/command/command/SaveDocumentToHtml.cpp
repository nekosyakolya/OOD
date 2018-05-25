#include "stdafx.h"
#include "SaveDocumentToHtml.h"
#include "ReplaceSpecialHtmlCharacters.h"

CSaveDocumentToHtml::CSaveDocumentToHtml(const boost::filesystem::path& path, const IDocument& document)
	: m_document(document)
{
	InitializationPath(path);
}

void CSaveDocumentToHtml::Execute() const
{
	CopyImages();
	OutputHtml();
}

CSaveDocumentToHtml::~CSaveDocumentToHtml()
{
}

void CSaveDocumentToHtml::InitializationPath(const boost::filesystem::path& path)
{
	if (!boost::filesystem::is_regular_file(path))
	{
		throw std::logic_error("File does not exist or the file name is incorrect");
	}
	std::string extensionFile = boost::filesystem::extension(path);
	boost::algorithm::to_lower(extensionFile); // modifies str

	if (extensionFile != ".html")
	{
		throw std::logic_error("File extension is incorrect");
	}

	m_path = boost::filesystem::complete(path);
}

void CSaveDocumentToHtml::CopyImages() const
{
	boost::filesystem::path imagesFolderPath = (m_path.parent_path() /= boost::filesystem::path("images"));
	boost::filesystem::create_directory(imagesFolderPath);

	auto itemsCount = m_document.GetItemsCount();
	for (size_t i = 0; i < itemsCount; ++i)

	{
		auto item = m_document.GetItem(i);
		if (auto it = item.GetImage())
		{
			boost::filesystem::path path = it->GetPath();
			boost::filesystem::path newPath = imagesFolderPath;
			newPath /= boost::filesystem::path(path.filename());

			boost::filesystem::copy_file(boost::filesystem::complete(path), newPath);
		}
	}
}

void CSaveDocumentToHtml::OutputHead(std::ofstream& out) const
{
	out << "<head>" << std::endl;
	out << "<title>" << m_document.GetTitle() << "</title>" << std::endl;
	out << "</head>" << std::endl;
}

void CSaveDocumentToHtml::OutputBody(std::ofstream& out) const
{
	out << "<body>" << std::endl;
	auto size = m_document.GetItemsCount();

	for (size_t i = 0; i < size; ++i)
	{

		auto item = m_document.GetItem(i);
		if (auto image = item.GetImage())
		{
			out << boost::format(R"(<img src=%1% width="%2%" height="%3%" />)") % image->GetPath() % image->GetWidth() % image->GetHeight() << std::endl;
		}
		else
		{
			auto paragraph = item.GetParagraph();
			std::string text = paragraph->GetText();
			CReplaceSpecialHtmlCharacters::Execute(text);
			out << boost::format(R"(<p>%1%</p>)") % text << std::endl;
		}
	}
	out << "</body>" << std::endl;
}

void CSaveDocumentToHtml::OutputHtml() const
{
	std::ofstream output(m_path.string());

	output << "<html>" << std::endl;
	OutputHead(output);
	OutputBody(output);
	output << "</html>" << std::endl;
}
