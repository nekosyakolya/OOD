#pragma once

struct SWeatherInfo
{
	double temperature = 0.0;
	double humidity = 0.0;
	double pressure = 0.0;
	double speed = 0.0;
	double windDirection = 0.0;
};

struct Point
{
	double x = 0.0;
	double y = 0.0;
	Point & operator+=(const Point & point)
	{
		x += point.x;
		y += point.y;
		return *this;
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

class StatsWindDirectionCalculator : public IStatsCalculator
{
public:
	explicit StatsWindDirectionCalculator(const std::string& name) :
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
		Point current;
		const double radians = ConvertDegreesToRadians(value);
		current.x = cos(radians);
		current.y = sin(radians);

		m_point += current;

	};
	void Display() override
	{
		std::cout << "Max " << m_name << " " << m_max << std::endl;

		std::cout << "Min " << m_name << " " << m_min << std::endl;

		std::cout << "Average " << m_name << " " << CalculateWindDirection() << std::endl;
		std::cout << "----------------" << std::endl;
	};
private:
	std::string m_name;
	Point m_point;
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();

	const double CalculateWindDirection() const
	{
		double result = ConvertRadiansToDegrees(atan2(m_point.y, m_point.x));
		return result >= 0.0 ? result : 360 + result;
	}

	const double ConvertDegreesToRadians(double degrees) const
	{
		return degrees * M_PI / 180.0;
	}
	const double ConvertRadiansToDegrees(double degrees) const
	{
		return degrees * 180.0 / M_PI;
	}
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

	double GetWindDirection()const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double speed, double windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		m_speed = speed;
		m_windDirection = windDirection;

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
		info.windDirection = GetWindDirection();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_speed = 0.0;
	double m_windDirection = 0.0;
};


class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(const CWeatherData& in, const CWeatherData& out) :
		m_in(in),
		m_out(out)
	{
	}
	using WeatherParamExtractor = std::function<double(const SWeatherInfo& data)>;
	void AddWeatherCalculator(const IObservable<SWeatherInfo>& observable, const WeatherParamExtractor& extractor, std::unique_ptr<IStatsCalculator> calculator)
	{
		if (&observable == &m_in)
		{
			m_calculatorsInner.emplace_back(std::move(calculator), extractor);
		}
		else if (&observable == &m_out)
		{
			m_calculatorsOut.emplace_back(std::move(calculator), extractor);
		}
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& observable) override
	{
		if (&observable == &m_in)
		{
			std::cout << "in station" << std::endl;
			for (auto&& calc : m_calculatorsInner)
			{
				double extractedParam = calc.second(data);
				calc.first->Update(extractedParam);
				calc.first->Display();
			}
		}
		else if (&observable == &m_out)
		{
			std::cout << "out station" << std::endl;
			for (auto&& calc : m_calculatorsOut)
			{
				double extractedParam = calc.second(data);
				calc.first->Update(extractedParam);
				calc.first->Display();
			}
		}


	}
	const CWeatherData & m_in;
	const CWeatherData & m_out;
	std::vector<std::pair<std::unique_ptr<IStatsCalculator>, WeatherParamExtractor>> m_calculatorsInner;
	std::vector<std::pair<std::unique_ptr<IStatsCalculator>, WeatherParamExtractor>> m_calculatorsOut;

};



class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(const CWeatherData& in, const CWeatherData& out) :
		m_in(in),
		m_out(out)
	{
	}
private:
	const CWeatherData & m_in;
	const CWeatherData & m_out;
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& observable) override
	{
		if (&observable == &m_in)
		{
			std::cout << "in station" << std::endl;
		}
		else if (&observable == &m_out)
		{
			std::cout << "out station" << std::endl;
		}

		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Speed " << data.speed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		std::cout << "----------------" << std::endl;
	}
};
