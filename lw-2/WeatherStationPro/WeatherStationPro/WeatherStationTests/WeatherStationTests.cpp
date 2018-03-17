#include "stdafx.h"
class CTestObserver : public IObserver<SWeatherInfo>
{
public:
	CTestObserver(const CWeatherData& in, const CWeatherData& out, std::stringstream& strm) :
		m_in(in),
		m_out(out),
		m_strm(strm)
	{
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		if (&observable == &m_in)
		{
			m_strm << "in station";
		}
		else if (&observable == &m_out)
		{
			m_strm << "out station";
		}
	}

	const CWeatherData & m_in;
	const CWeatherData & m_out;
	std::stringstream& m_strm;
};

class CTestObserverPriority : public IObserver<SWeatherInfo>
{
public:
	CTestObserverPriority(std::stringstream& strm, unsigned priority = 0)
		: m_priority(priority)
		, m_strm(strm)
	{
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		m_strm << m_priority;
	}
	unsigned m_priority = 0;
	std::stringstream& m_strm;
};

class CTestSafeNotificationObservers : public IObserver<SWeatherInfo>
{
public:
	CTestSafeNotificationObservers(std::stringstream& strm)
		: m_strm(strm)
	{
	}

private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>& observable) override
	{
		m_strm << "[update]";
		observable.RemoveObserver(*this);
	};
	std::stringstream& m_strm;
};

BOOST_AUTO_TEST_SUITE(Weather_station)
	BOOST_AUTO_TEST_CASE(observer_identifies_changed_subject)
	{
		CWeatherData in;
		CWeatherData out;
		std::stringstream strm;

		CTestObserver testObserver(in, out, strm);
		in.RegisterObserver(testObserver);
		out.RegisterObserver(testObserver);
		
		{
			in.SetMeasurements(4, 0.8, 761, 10, 90);
			BOOST_CHECK_EQUAL(strm.str(), "in station");
		}
		strm.str("");
		{
			out.SetMeasurements(4, 0.8, 761, 10, 90);
			BOOST_CHECK_EQUAL(strm.str(), "out station");
		}

		{
			CWeatherData other;
			other.RegisterObserver(testObserver);
			strm.str("");

			other.SetMeasurements(4, 0.8, 761, 10, 90);
			BOOST_CHECK_EQUAL(strm.str(), "");
		}
	}


	BOOST_AUTO_TEST_CASE(observers_have_priority)
	{

		{
			CWeatherData wd;

			std::stringstream strm;

			CTestObserverPriority first(strm);
			CTestObserverPriority second(strm);

			wd.RegisterObserver(second);
			wd.RegisterObserver(first);

			wd.NotifyObservers();

			BOOST_CHECK_EQUAL(strm.str(), "00");
		}

		{
			CWeatherData wd;

			std::stringstream strm;

			CTestObserverPriority first(strm);
			CTestObserverPriority second(strm, 5);
			CTestObserverPriority third(strm, 5);
			CTestObserverPriority fourth(strm, 2);

			wd.RegisterObserver(second, 5);
			wd.RegisterObserver(first);
			wd.RegisterObserver(third, 5);
			wd.RegisterObserver(fourth, 2);

			wd.NotifyObservers();

			BOOST_CHECK_EQUAL(strm.str(), "0255");
		}

	}

	BOOST_AUTO_TEST_CASE(safe_notification_of_observers)
	{

		{
			CWeatherData wd;

			std::stringstream strm;

			CTestSafeNotificationObservers first(strm);
			CTestSafeNotificationObservers second(strm);

			wd.RegisterObserver(second);
			wd.RegisterObserver(first);

			wd.NotifyObservers();

			strm.clear();
			wd.NotifyObservers();

			BOOST_CHECK_EQUAL(strm.str(), "[update][update]");
		}



	}
BOOST_AUTO_TEST_SUITE_END()


