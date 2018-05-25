#include "stdafx.h"
#include "CDocumentItem.h"

CDocumentItem::CDocumentItem(const std::shared_ptr<IImage>& image, const std::shared_ptr<IParagraph>& paragraph)
	: CConstDocumentItem(image, paragraph)
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
