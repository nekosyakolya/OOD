#pragma once
#include "ICommand.h"
#include "ICommandHistory.h"

class CCommandHistory : public ICommandHistory
{
public:
	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;
	void SetAndExecuteCommand(std::unique_ptr<ICommand>&& command) override;

private:
	std::deque<std::unique_ptr<ICommand>> m_commands;
	size_t m_nextCommandIndex = 0;

	const size_t MAX_SIZE = 10;
};
