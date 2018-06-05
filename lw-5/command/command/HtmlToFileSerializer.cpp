#include "stdafx.h"
#include "HtmlToFileSerializer.h"
#include "ReplaceSpecialHtmlCharacters.h"

HtmlToFileSerializer::HtmlToFileSerializer(const boost::filesystem::path& path)
{
	SetPath(path);
}

void HtmlToFileSerializer::Serialize(const IDocument& document) const
{
	CopyImages(document);
	OutputHtml(document);
}

void HtmlToFileSerializer::SetPath(const boost::filesystem::path& path)
{
	std::string fileExtension = boost::filesystem::extension(path);
	boost::algorithm::to_lower(fileExtension);

	if (fileExtension != ".html")
	{
		throw std::logic_error("File extension is incorrect");
	}

	m_path = boost::filesystem::complete(path);
	boost::filesystem::path directory = m_path;
	directory.remove_filename();

	if (!boost::filesystem::exists(directory))
	{
		boost::filesystem::create_directory(directory);
	}
}

void HtmlToFileSerializer::CopyImages(const IDocument& document) const
{
	boost::filesystem::path imagesFolderPath = (m_path.parent_path() /= boost::filesystem::path("images"));
	boost::filesystem::create_directory(imagesFolderPath);

	auto itemsCount = document.GetItemsCount();
	for (size_t i = 0; i < itemsCount; ++i)

	{
		auto item = document.GetItem(i);
		if (auto it = item.GetImage())
		{
			boost::filesystem::path path = it->GetPath();
			boost::filesystem::path newPath = imagesFolderPath;
			newPath /= boost::filesystem::path(path.filename());

			boost::filesystem::copy_file(boost::filesystem::complete(path), newPath, boost::filesystem::copy_option::overwrite_if_exists);
		}
	}
}

void HtmlToFileSerializer::OutputHead(std::ofstream& out, const IDocument& document) const
{
	std::string title = document.GetTitle();
	CReplaceSpecialHtmlCharacters::Execute(title);

	out << "<head>" << std::endl;
	out << "<title>" << title << "</title>" << std::endl;
	out << "</head>" << std::endl;
}

void HtmlToFileSerializer::OutputBody(std::ofstream& out, const IDocument& document) const
{
	out << "<body>" << std::endl;
	auto size = document.GetItemsCount();

	for (size_t i = 0; i < size; ++i)
	{
		auto item = document.GetItem(i);
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

void HtmlToFileSerializer::OutputHtml(const IDocument& document) const
{
	std::ofstream output(m_path.string());

	output << "<html>" << std::endl;
	OutputHead(output, document);
	OutputBody(output, document);
	output << "</html>" << std::endl;
}
