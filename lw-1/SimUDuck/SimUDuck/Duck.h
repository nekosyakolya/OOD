#pragma once

class CDuck
{
public:
	CDuck(std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior);
	void Swim();
	void Fly() const;
	void Quack() const;
	void Dance() const;
	virtual void Display() const = 0;
	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior);
	virtual ~CDuck() = default;
private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

