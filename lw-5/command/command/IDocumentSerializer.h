#pragma once

#include "IDocument.h"


class IDocumentSerializer
{
public:
	virtual void Serialize() const = 0;
	virtual void SetTitle(const std::string&) = 0;
	virtual void InsertItem(const CConstDocumentItem &) = 0;
	virtual ~IDocumentSerializer() = default;
};
