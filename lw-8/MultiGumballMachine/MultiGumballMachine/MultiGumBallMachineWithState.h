#pragma once

namespace with_state
{

struct IState
{
	virtual void InsertCoin() = 0;
	virtual void EjectCoin() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;

	virtual void Refill(size_t count) = 0;

	virtual std::string ToString() const = 0;
	virtual ~IState() = default;
};

struct IGumballMachineContext
{
	virtual void ReleaseBall() = 0;
	virtual size_t GetBallCount() const = 0;
	virtual void Refill(size_t count) = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoCoinState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasCoinState() = 0;

	virtual void AddCoin() = 0;
	virtual void ReleaseCoin() = 0;
	virtual size_t GetCoins() = 0;

	virtual ~IGumballMachineContext() = default;
};

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachineContext& gumballMachine, std::ostream& out);

	void InsertCoin() override;
	void EjectCoin() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(size_t count) override;
	std::string ToString() const override;

private:
	IGumballMachineContext& m_gumballMachine;

	std::ostream& m_out;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachineContext& gumballMachine, std::ostream& out);

	void InsertCoin() override;
	void EjectCoin() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(size_t count) override;
	std::string ToString() const override;

private:
	IGumballMachineContext& m_gumballMachine;

	std::ostream& m_out;
};

class CHasCoinState : public IState
{
public:
	CHasCoinState(IGumballMachineContext& gumballMachine, std::ostream& out);

	void InsertCoin() override;
	void EjectCoin() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(size_t count) override;
	std::string ToString() const override;

private:
	IGumballMachineContext& m_gumballMachine;

	std::ostream& m_out;
};

class CNoCoinState : public IState
{
public:
	CNoCoinState(IGumballMachineContext& gumballMachine, std::ostream& out);

	void InsertCoin() override;
	void EjectCoin() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(size_t count) override;
	std::string ToString() const override;

private:
	IGumballMachineContext& m_gumballMachine;

	std::ostream& m_out;
};

class CMultiGumballMachine : private IGumballMachineContext
{
public:
	CMultiGumballMachine(size_t numBalls, std::ostream& out);

	void EjectCoin();

	void InsertCoin();
	void TurnCrank();
	std::string ToString() const;

private:
	size_t GetBallCount() const override;
	void ReleaseBall() override;

	void SetSoldOutState() override;
	void SetNoCoinState() override;
	void SetSoldState() override;
	void SetHasCoinState() override;

	size_t m_gumBalls = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoCoinState m_noCoinState;
	CHasCoinState m_hasCoinState;
	IState* m_state;
	std::ostream& m_out;

	size_t m_coin = 0;
	const size_t MAX_COUNT_OF_COINS = 5;

	void Refill(size_t count);

	void AddCoin() override;
	void ReleaseCoin() override;
	size_t GetCoins() override;
};
} // namespace with_state
