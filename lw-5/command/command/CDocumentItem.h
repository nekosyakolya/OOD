#pragma once
#include "CConstDocumentItem.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();
};
