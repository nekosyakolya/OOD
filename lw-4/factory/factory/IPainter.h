#pragma once

#include "CPictureDraft.h"

#include "ICanvas.h"

class IPainter
{
public:
	virtual void DrawPicture(const CPictureDraft& draft, ICanvas& canvas) = 0;
	virtual ~IPainter() = default;
};
