#pragma once
#include "IImage.h"
#include "IParagraph.h"

class CConstDocumentItem
{
public:
	CConstDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& paragraph);
	std::shared_ptr<const IImage> GetImage() const;
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> m_image;
	std::shared_ptr<IParagraph> m_paragraph;
};
