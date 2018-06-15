#pragma once

#include "IDocumentSerializer.h"

class HtmlToFileSerializer : public IDocumentSerializer
{
public:
	HtmlToFileSerializer(const boost::filesystem::path&);
	void Serialize() const override;

	void SetTitle(const std::string&) override;
	void InsertItem(const CConstDocumentItem &) override;

private:
	boost::filesystem::path m_path;

	void SetPath(const boost::filesystem::path& path);
	void CopyImages() const;

	void OutputHead(std::ofstream& out) const;
	void OutputBody(std::ofstream& out) const;
	void OutputHtml() const;

	std::string m_title;
	std::vector<CConstDocumentItem> m_items;

};
