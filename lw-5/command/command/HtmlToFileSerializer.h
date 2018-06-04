#pragma once

#include "IDocumentSerializer.h"

class HtmlToFileSerializer : public IDocumentSerializer
{
public:
	HtmlToFileSerializer(const boost::filesystem::path&);
	void Serialize(const IDocument&) const override;

private:
	boost::filesystem::path m_path;

	void SetPath(const boost::filesystem::path& path);
	void CopyImages(const IDocument& document) const;

	void OutputHead(std::ofstream& out, const IDocument& document) const;
	void OutputBody(std::ofstream& out, const IDocument& document) const;
	void OutputHtml(const IDocument& document) const;
};
