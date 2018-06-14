#include "stdafx.h"
#include "DeleteItemCommand.h"

CDeleteItemCommand::CDeleteItemCommand(std::vector<CDocumentItem>& items, size_t index)
	: m_items(items)
	, m_index(index)
	, m_item(std::make_shared<CDocumentItem>(nullptr, nullptr))
{
}

CDeleteItemCommand::~CDeleteItemCommand()
{
	//если выполнена и это картинка то из images удаляем
	auto image = m_item->GetImage();
	if (m_executed && image)
	{
		boost::system::error_code errorCode;
		boost::filesystem::remove(image->GetPath(), errorCode);
		if (errorCode)
		{
			std::cout << errorCode.message() << std::endl;
		}
	}
}

void CDeleteItemCommand::DoExecute()
{
	m_item = std::make_shared<CDocumentItem>(m_items.at(m_index));

	m_items.erase(m_items.begin() + m_index);
}

void CDeleteItemCommand::DoUnexecute()
{
	m_items.emplace(m_items.begin() + m_index, *m_item);
}
