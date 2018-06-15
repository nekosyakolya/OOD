#include "stdafx.h"
#include "HtmlToFileSerializer.h"
#include "ReplaceSpecialHtmlCharacters.h"

HtmlToFileSerializer::HtmlToFileSerializer(const boost::filesystem::path& path)
{
	SetPath(path);
}

void HtmlToFileSerializer::Serialize() const
{
	CopyImages();
	OutputHtml();
}

void HtmlToFileSerializer::SetTitle(const std::string & title)
{
	m_title = title;
	CReplaceSpecialHtmlCharacters::Execute(m_title);
}

void HtmlToFileSerializer::InsertItem(const CConstDocumentItem & item)
{
	m_items.emplace_back(item);
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

void HtmlToFileSerializer::CopyImages() const
{
	boost::filesystem::path imagesFolderPath = (m_path.parent_path() /= boost::filesystem::path("images"));
	boost::filesystem::create_directory(imagesFolderPath);

	for (size_t i = 0; i < m_items.size(); ++i)

	{
		auto item = m_items.at(i);
		if (auto it = item.GetImage())
		{
			boost::filesystem::path path = it->GetPath();
			boost::filesystem::path newPath = imagesFolderPath;
			newPath /= boost::filesystem::path(path.filename());

			if (!boost::filesystem::exists(newPath))
			{
				boost::filesystem::copy_file(boost::filesystem::complete(path), newPath);
			}
		}
	}
}

void HtmlToFileSerializer::OutputHead(std::ofstream& out) const
{
	out << "<head>" << std::endl;
	out << "<title>" << m_title << "</title>" << std::endl;
	out << "</head>" << std::endl;
}

void HtmlToFileSerializer::OutputBody(std::ofstream& out) const
{
	out << "<body>" << std::endl;

	for (size_t i = 0; i < m_items.size(); ++i)
	{
		auto item = m_items.at(i);
		if (auto image = item.GetImage())
		{
			boost::filesystem::path path = (boost::filesystem::path("images") /= (image->GetPath()).filename());

			out << boost::format(R"(<img src=%1% width="%2%" height="%3%" />)") % path % image->GetWidth() % image->GetHeight() << std::endl;
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

void HtmlToFileSerializer::OutputHtml() const
{
	std::ofstream output(m_path.string());

	output << "<html>" << std::endl;
	OutputHead(output);
	OutputBody(output);
	output << "</html>" << std::endl;
}
