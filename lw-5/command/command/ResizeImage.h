#pragma once
#include "AbstractCommand.h"
class CResizeImage : public CAbstractCommand
{
public:
	CResizeImage(int& targetWidth, int const& newWidth, int& targetHeight, int const& newHeight);

private:
	void DoExecute() override;
	void DoUnexecute() override;
	int& m_targetWidth;
	int m_newWidth;
	int& m_targetHeight;
	int m_newHeight;
};
