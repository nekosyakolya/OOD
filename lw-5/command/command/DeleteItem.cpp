#include "stdafx.h"
#include "DeleteItem.h"




CDeleteItem::CDeleteItem(std::vector<CDocumentItem>& items, size_t index):
	m_items(items),
	m_index(index),
	m_image(nullptr),
	m_paragraph(nullptr)
{
}

CDeleteItem::~CDeleteItem()
{

	//���� ��������� � ��� �������� �� �� images �������
	if (m_executed && m_image != nullptr)
	{

	}
}

void CDeleteItem::DoExecute()
{
	if (m_index >= m_items.size())
	{
		//������ ����
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
