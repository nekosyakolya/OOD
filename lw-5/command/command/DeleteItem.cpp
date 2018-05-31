#include "stdafx.h"
#include "DeleteItem.h"

CDeleteItem::CDeleteItem(std::vector<CDocumentItem>& items, size_t index)
	: m_items(items)
	, m_index(index)
	, m_image(nullptr)
	, m_paragraph(nullptr)
{
}

CDeleteItem::~CDeleteItem()
{
	//если выполнена и это картинка то из images удаляем
	if (m_executed && m_image)
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

void CDeleteItem::DoExecute()
{
	if (m_index >= m_items.size())
	{
		//кидаем искл
		throw std::logic_error("Index should be less than the size of the document");
	}

	m_image = m_items[m_index].GetImage();
	m_paragraph = m_items[m_index].GetParagraph();

	m_items.erase(m_items.begin() + m_index);
}

void CDeleteItem::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_index, CDocumentItem(m_image, m_paragraph));
}
