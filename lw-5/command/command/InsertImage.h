#pragma once
#include "AbstractCommand.h"
#include "CDocumentItem.h"
#include "ICommandHistory.h"

class CInsertImage : public CAbstractCommand
{
public:
	CInsertImage(ICommandHistory& history, std::vector<CDocumentItem>& items, const boost::filesystem::path& path, int width, int height,
		boost::optional<size_t> position = boost::none);

	~CInsertImage() override;

private:
	void DoExecute() override;
	void DoUnexecute() override;
	std::vector<CDocumentItem>& m_items;
	boost::optional<size_t> m_position;
	std::shared_ptr<IImage> m_image;

	void SetImage(ICommandHistory& history, const boost::filesystem::path& path, int width, int height);
};
