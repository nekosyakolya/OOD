#pragma once
#include "IPainter.h"

class CPainter : public IPainter
{
public:
	void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) override;
};
