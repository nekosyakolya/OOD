#pragma once
class ICommand;

class ICommandHistory
{
public:
	virtual bool CanUndo() const = 0;
	virtual void Undo() = 0;
	virtual bool CanRedo() const = 0;
	virtual void Redo() = 0;
	virtual void SetAndExecuteCommand(std::unique_ptr<ICommand>&& command) = 0;
	virtual ~ICommandHistory() = default;
};
