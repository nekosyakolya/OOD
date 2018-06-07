#pragma once

namespace with_state
{

struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual std::string ToString() const = 0;
	virtual ~IState() = default;
};

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual size_t GetBallCount() const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;

	std::ostream& m_out;
};

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;

	std::ostream& m_out;
};

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;

	std::ostream& m_out;
};

class CNoQuarterState : public IState
{
public:
	CNoQuarterState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;
	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;

	std::ostream& m_out;
};

class CGumballMachine : private IGumballMachine
{
public:
	CGumballMachine(size_t numBalls, std::ostream& out);

	void EjectQuarter();

	void InsertQuarter();
	void TurnCrank();
	std::string ToString() const;

private:
	size_t GetBallCount() const override;
	void ReleaseBall() override;
	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

	size_t m_count = 0;
	CSoldState m_soldState;
	CSoldOutState m_soldOutState;
	CNoQuarterState m_noQuarterState;
	CHasQuarterState m_hasQuarterState;
	IState* m_state;
	std::ostream& m_out;
};
} // namespace with_state
