#include "stdafx.h"
#include "InsertImage.h"
#include "Image.h"

CInsertImage::CInsertImage(ICommandHistory& history, std::vector<CDocumentItem>& items, const boost::filesystem::path& path, int width, int height, boost::optional<size_t> position)
	: m_items(items)
	, m_position(position)

{
	SetImage(history, path, width, height);
}

CInsertImage::~CInsertImage()
{
	//если не выполнена , то удаляем из подкаталога файл
	if (!m_executed)
	{
		try
		{
			boost::filesystem::remove(m_image->GetPath());
		}
		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}

void CInsertImage::DoExecute()
{
	if (m_position == boost::none)
	{
		m_items.emplace_back(CDocumentItem(m_image, nullptr));
	}
	else if (m_position.get() != 0 && m_position >= m_items.size())
	{
		throw std::invalid_argument("Index should be less than the size of the document");
	}
	else
	{
		m_items.emplace(m_items.begin() + m_position.get(), CDocumentItem(m_image, nullptr));
	}
}

void CInsertImage::DoUnexecute()
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

void CInsertImage::SetImage(ICommandHistory& history, const boost::filesystem::path& path, int width, int height)
{
	boost::filesystem::path imagesFolderPath = boost::filesystem::complete(boost::filesystem::path("images", boost::filesystem::native));
	boost::filesystem::create_directory(imagesFolderPath);

	std::string extensionFile = boost::filesystem::extension(path);
	boost::algorithm::to_lower(extensionFile);

	if (extensionFile != ".jpg" && extensionFile != ".png" && extensionFile != ".gif")
	{
		throw std::logic_error("File extension is incorrect");
	}

	std::string newFileName = boost::filesystem::unique_path().string() + extensionFile;

	boost::filesystem::path newRelativePath = imagesFolderPath.stem();
	newRelativePath /= boost::filesystem::path(newFileName);

	boost::filesystem::copy_file(path, (imagesFolderPath /= boost::filesystem::path(newFileName)));
	m_image = std::make_shared<CImage>(history, newRelativePath, width, height);
}
