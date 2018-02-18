#pragma once

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double speed = 0;
	double directionWind = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class IStatsCalculator
{
public:
	virtual void Display() = 0;
	virtual void Update(double value) = 0;
	virtual ~IStatsCalculator() = default;
};


class StatsCalculator : public IStatsCalculator
{
public:
	explicit StatsCalculator(const std::string& name):
		m_name(name)
	{
	};
	void Update(double value) override
	{
		if (m_min > value)
		{
			m_min = value;
		}
		if (m_max < value)
		{
			m_max = value;
		}
		m_acc += value;
		++m_countAcc;
	};
	void Display() override
	{
		std::cout << "Max " << m_name << " " << m_max << std::endl;
		
		std::cout << "Min " << m_name << " " << m_min << std::endl;

		std::cout << "Average " << m_name << " " << ((m_countAcc == 0) ? 0 : m_acc / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	};
private:
	std::string m_name;
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};

class StatsDirectionCalculator : public IStatsCalculator
{
public:
	explicit StatsDirectionCalculator(const std::string& name) :
		m_name(name)
	{
	};
	void Update(double value) override
	{
		m_acc += value;
		++m_countAcc;
	};
	void Display() override
	{
		std::cout << "Average " << m_name << " " << ((m_countAcc == 0) ? 0 : m_acc / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	};
private:
	std::string m_name;
	double m_acc = 0;
	unsigned m_countAcc = 0;
};




class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	using WeatherParamExtractor = std::function<double(const SWeatherInfo& data)>;
	void AddWeatherCalculator(const WeatherParamExtractor& extractor, std::unique_ptr<IStatsCalculator> calculator)
	{
		m_calculators.emplace_back(std::move(calculator), extractor);
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		for (auto&& calc : m_calculators)
		{
			double extractedParam = calc.second(data);
			calc.first->Update(extractedParam);
			calc.first->Display();
		}

	}
	std::vector<std::pair<std::unique_ptr<IStatsCalculator>, WeatherParamExtractor>> m_calculators;

};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	double GetSpeed()const
	{
		return m_speed;
	}

	double GetDirectionWind()const
	{
		return m_directionWind;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double speed, double directionWind)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		m_speed = speed;
		m_directionWind = directionWind;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.speed = GetSpeed();
		info.directionWind = GetDirectionWind();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_speed = 0.0;
	double m_directionWind = 0;
};
