#include "stdafx.h"

int main()
{
	CWeatherData in;
	CWeatherData out;

	CDisplay display(in, out);
	in.RegisterObserver(display);
	out.RegisterObserver(display);

	CStatsDisplay statsDisplay(in, out);
	statsDisplay.AddWeatherCalculator([](const SWeatherInfo& wd) {
		return wd.temperature;
	}, std::make_unique<StatsCalculator>("temperature"));

	statsDisplay.AddWeatherCalculator([](const SWeatherInfo& wd) {
		return wd.humidity;
	}, std::make_unique<StatsCalculator>("humidity"));

	statsDisplay.AddWeatherCalculator([](const SWeatherInfo& wd) {
		return wd.pressure;
	}, std::make_unique<StatsCalculator>("pressure"));

	statsDisplay.AddWeatherCalculator([](const SWeatherInfo& wd) {
		return wd.speed;
	}, std::make_unique<StatsCalculator>("speed"));

	statsDisplay.AddWeatherCalculator([](const SWeatherInfo& wd) {
		return wd.windDirection;
	}, std::make_unique<StatsWindDirectionCalculator>("wind direction"));

	in.RegisterObserver(statsDisplay);
	out.RegisterObserver(statsDisplay);

	in.SetMeasurements(4, 0.8, 761, 10, 0);
	
	out.SetMeasurements(4, 0.8, 761, 10, 0);

	in.SetMeasurements(4, 0.8, 761, 10, 90);


	return EXIT_SUCCESS;
}