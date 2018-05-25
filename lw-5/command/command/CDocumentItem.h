#pragma once
#include "CConstDocumentItem.h"

class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& paragraph);
	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<IParagraph> GetParagraph();
};
