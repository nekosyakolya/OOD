#include "stdafx.h"
#include "InsertImage.h"

#include "Image.h"

CInsertImage::CInsertImage(CCommandHistory & history, std::vector<CDocumentItem>& items, const boost::filesystem::path & path, int width, int height, boost::optional<size_t> position):
	m_items(items),
	m_position(position)

{
	InitializationImage(history, path, width, height);
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
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

}

void CInsertImage::DoExecute()
{
	//добавляем в вектор
	if (m_position >= m_items.size())
	{
		//кидаем искл
		throw std::logic_error("Index should be less than the size of the document");
	}
	//копируем в подкаталог images

	//Имя для изображения должно быть сгенерировано автоматически, а расширение остаться оригинальным.



	if (m_position == boost::none)
	{

		m_items.emplace_back(CDocumentItem(m_image, nullptr));

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

void CInsertImage::InitializationImage(CCommandHistory & history, const boost::filesystem::path & path, int width, int height)
{
	boost::filesystem::path newPath = boost::filesystem::complete(boost::filesystem::path("images", boost::filesystem::native));


	//генерим имя и копируем
	boost::filesystem::create_directory(newPath);

	std::string newName = boost::filesystem::unique_path().string() + boost::filesystem::extension(path);

	newPath /= boost::filesystem::path(newName);

	boost::filesystem::path newRelativePath = boost::filesystem::path("images");
	newRelativePath /= boost::filesystem::path(newName);


	boost::filesystem::copy_file(path, newPath);
	//копируем в подкаталог отдаем ноый путь
	m_image = std::make_shared<CImage>(history, newRelativePath, width, height);
}
