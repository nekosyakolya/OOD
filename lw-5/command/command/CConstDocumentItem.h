#pragma once

#include "stdafx.h"
#include "IImage.h"
#include "IParagraph.h"

class CConstDocumentItem
{
public:
	std::shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;
};
