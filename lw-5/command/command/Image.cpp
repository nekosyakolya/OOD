#include "stdafx.h"
#include "Image.h"
#include "ResizeImage.h"

CImage::CImage(IInvoker& history, const boost::filesystem::path& path, int width, int height)
	: m_height(height)
	, m_width(width)
	, m_history(history)
{
	InitializationPath(path);
}

boost::filesystem::path CImage::GetPath() const
{
	return m_path;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	m_history.SetAndExecuteCommand(std::make_unique<CResizeImage>(m_width, width, m_height, height));
}

void CImage::InitializationPath(const boost::filesystem::path& path)
{
	if (!boost::filesystem::is_regular_file(path))
	{
		throw std::logic_error("File does not exist or the file name is incorrect");
	}

	std::string extensionFile = boost::filesystem::extension(path);
	boost::algorithm::to_lower(extensionFile);

	if (extensionFile != ".jpg" && extensionFile != ".png" && extensionFile != ".gif")
	{
		throw std::logic_error("File extension is incorrect");
	}

	m_path = path;
}
