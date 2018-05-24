#pragma once

#include "IDocument.h"

class CSaveDocumentToHtml
{
public:
	CSaveDocumentToHtml(const boost::filesystem::path & path, const IDocument & document);
	void Execute() const;
	~CSaveDocumentToHtml();
private:
	boost::filesystem::path m_path;
	const IDocument &m_document;
	void InitializationPath(const boost::filesystem::path &path);
	void CopyImages() const;

};

