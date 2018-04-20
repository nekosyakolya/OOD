﻿#pragma once
#include "IDesigner.h"
#include "IShapeFactory.h"

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactory& factory);
	CPictureDraft CreateDraft(std::istream& strm) override;

private:
	IShapeFactory& m_factory;
};
