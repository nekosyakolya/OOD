#pragma once
#include "AbstractCommand.h"
#include "CDocumentItem.h"

class CDeleteItem :
	public CAbstractCommand
{
public:
	CDeleteItem(std::vector<CDocumentItem>& items, size_t index);
	~CDeleteItem();
private:
	void DoExecute() override;
	void DoUnexecute() override;
	std::vector<CDocumentItem> &m_items;
	size_t m_index;

	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;

};

