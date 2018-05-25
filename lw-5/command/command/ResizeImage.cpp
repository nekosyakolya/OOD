#include "stdafx.h"
#include "ResizeImage.h"

CResizeImage::CResizeImage(int& targetWidth, int const& newWidth, int& targetHeight, int const& newHeight)
	: m_targetHeight(targetHeight)
	, m_targetWidth(targetWidth)
	, m_newHeight(newHeight)
	, m_newWidth(newWidth)
{
}

void CResizeImage::DoExecute()
{
	std::swap(m_targetHeight, m_newHeight);
	std::swap(m_targetWidth, m_newWidth);
}

void CResizeImage::DoUnexecute()
{
	DoExecute();
}
