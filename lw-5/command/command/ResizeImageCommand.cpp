#include "stdafx.h"
#include "ResizeImageCommand.h"

CResizeImageCommand::CResizeImageCommand(int& targetWidth, int const& newWidth, int& targetHeight, int const& newHeight)
	: m_targetHeight(targetHeight)
	, m_targetWidth(targetWidth)
	, m_newHeight(newHeight)
	, m_newWidth(newWidth)
{
}

void CResizeImageCommand::DoExecute()
{
	std::swap(m_targetHeight, m_newHeight);
	std::swap(m_targetWidth, m_newWidth);
}

void CResizeImageCommand::DoUnexecute()
{
	DoExecute();
}
