#pragma once

#include "IDocument.h"

class IDocumentSerializer
{
public:
	virtual void Serialize(const IDocument&) const = 0;
	virtual ~IDocumentSerializer() = default;

};
