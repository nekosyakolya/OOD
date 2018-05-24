#include "stdafx.h"
#include "SaveDocumentToHtml.h"
#include "ReplaceSpecialHtmlCharacters.h"



CSaveDocumentToHtml::CSaveDocumentToHtml(const boost::filesystem::path & path, const IDocument & document):
	m_document(document)
{
	InitializationPath(path);
}

void CSaveDocumentToHtml::Execute() const
{
	CopyImages();
	
	std::ofstream output(m_path.string()); ///??????
	
	output << "<html>" << std::endl;
	output << "<head>" << std::endl;
	output << "<title>" << m_document.GetTitle() << "</title>" << std::endl;
	output << "</head>" << std::endl;
	output << "<body>" << std::endl;

	for (size_t i = 0; i <m_document.GetItemsCount(); ++i)
	{

		if (!m_document.GetItem(i).GetImage())
		{
			std::string text = m_document.GetItem(i).GetParagraph()->GetText();
			CReplaceSpecialHtmlCharacters::Execute(text);

			output << "<p>" << text << "</p>" << std::endl;
	}
		else
		{			output << "<img src=" << m_document.GetItem(i).GetImage()->GetPath() << " width=\""
				<< m_document.GetItem(i).GetImage()->GetWidth() << "\" height=\""
				<< m_document.GetItem(i).GetImage()->GetHeight() << "\" />"
				<< std::endl;
		}
	}
	output << "</body>" << std::endl;

	output << "</html>" << std::endl;
}

CSaveDocumentToHtml::~CSaveDocumentToHtml()
{
}

void CSaveDocumentToHtml::InitializationPath(const boost::filesystem::path & path)
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
		if(auto it = item.GetImage())
		{
			boost::filesystem::path path = it->GetPath();
			boost::filesystem::path newPath = imagesFolderPath;
			newPath /= boost::filesystem::path(path.filename());

			boost::filesystem::copy_file(boost::filesystem::complete(path), newPath);
		}
	}
}
