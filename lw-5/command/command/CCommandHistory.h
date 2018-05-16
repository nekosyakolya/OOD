#pragma once

#include "stdafx.h"
#include "ICommand.h"

class CCommandHistory
{
public:
	bool CanUndo() const;
	void Undo();
	bool CanRedo() const;
	void Redo();
	void SetAndExecuteCommand(std::unique_ptr<ICommand>&& command);

private:
	std::deque<std::unique_ptr<ICommand>> m_commands;
	size_t m_nextCommandIndex = 0;
	const size_t MAX_SIZE = 10;
};
