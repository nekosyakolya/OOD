#pragma once

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
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

template <typename T>
class IStatistics
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IStatistics() = default;
};

class CStatistics : public IStatistics<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		UpdateStatistics(data);
		Display();
	};
	virtual void Display() = 0;
	virtual void UpdateStatistics(SWeatherInfo const& data) = 0;
};

class CWeatherStatistics : public CStatistics
{
public:
	void Update(double  data)
	{
		if (m_min > data)
		{
			m_min = data;
		}
		if (m_max < data)
		{
			m_max = data;
		}
		m_acc += data;
		++m_countAcc;
	};

	double GetMax() const
	{
		return m_max;
	};

	double GetMin() const
	{
		return m_min;
	}

	double GetAverage() const
	{
		return (m_countAcc == 0) ? 0 : (m_acc / m_countAcc);
	}
private:
	virtual void Display() = 0;
	virtual void UpdateStatistics(SWeatherInfo const& data) = 0;

	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};


class CTemperatureStatistics : public CWeatherStatistics
{
private:
	void Display() override
	{
		std::cout << "Max Temp " << GetMax() << std::endl;
		std::cout << "Min Temp " << GetMin() << std::endl;
		std::cout << "Average Temp " << GetAverage() << std::endl;
		std::cout << "----------------" << std::endl;
	};
	void UpdateStatistics(SWeatherInfo const& data) override
	{
		Update(data.temperature);
	};
};

class CPressureStatistics : public CWeatherStatistics
{
private:
	void Display() override
	{
		std::cout << "Max Pressure " << GetMax() << std::endl;
		std::cout << "Min Pressure " << GetMin() << std::endl;
		std::cout << "Average Pressure " << GetAverage() << std::endl;
		std::cout << "----------------" << std::endl;
	};
	void UpdateStatistics(SWeatherInfo const& data) override
	{
		Update(data.pressure);
	};
};

class CHumidityStatistics : public CWeatherStatistics
{
private:
	void Display() override
	{
		std::cout << "Max Humidity " << GetMax() << std::endl;
		std::cout << "Min Humidity " << GetMin() << std::endl;
		std::cout << "Average Humidity " << GetAverage() << std::endl;
		std::cout << "----------------" << std::endl;
	};
	void UpdateStatistics(SWeatherInfo const& data) override
	{
		Update(data.humidity);
	};
};



class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay()
	{
		std::unique_ptr<IStatistics<SWeatherInfo>> temperatureStatistics = 
			std::make_unique<CTemperatureStatistics>();

		m_statistics.push_back(std::move(temperatureStatistics));


		std::unique_ptr<IStatistics<SWeatherInfo>> pressureStatistics =
			std::make_unique<CPressureStatistics>();

		m_statistics.push_back(std::move(pressureStatistics));

		std::unique_ptr<IStatistics<SWeatherInfo>> humidityStatistics =
			std::make_unique<CHumidityStatistics>();

		m_statistics.push_back(std::move(humidityStatistics));

	};

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		for (auto & sensorStatistics : m_statistics)
		{
			sensorStatistics->Update(data);
		}

	}
	std::vector<std::unique_ptr<IStatistics<SWeatherInfo>>> m_statistics;

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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
