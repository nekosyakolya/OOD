#pragma once
class IFlyBehavior
{
public:
	virtual void Fly() = 0;
	virtual int GetFlightNumber()const = 0;
	virtual void SetFlightNumber(int) = 0;
	virtual ~IFlyBehavior() = default;
};
