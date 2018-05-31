#pragma once
class ICommand;

class IInvoker
{
public:
	virtual void SetAndExecuteCommand(std::unique_ptr<ICommand>&& command) = 0;
	virtual ~IInvoker() = default;
};
