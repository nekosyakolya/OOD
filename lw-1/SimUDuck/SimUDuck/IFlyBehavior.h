#pragma once
class IFlyBehavior
{
public:
	virtual void Fly() = 0;
	virtual ~IFlyBehavior() = default;
};
