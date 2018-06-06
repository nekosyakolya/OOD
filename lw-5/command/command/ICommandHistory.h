#pragma once
class ICommand;

class ICommandHistory
{
public:
	virtual void SetAndExecuteCommand(std::unique_ptr<ICommand>&& command) = 0;
	virtual ~ICommandHistory() = default;
};
