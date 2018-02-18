#include "stdafx.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
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
		return wd.directionWind;
	}, std::make_unique<StatsDirectionCalculator>("direction wind"));

	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 0, 0);
	wd.SetMeasurements(4, 0.8, 761, 10, 90);

	/*wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, 100, 180);
	wd.SetMeasurements(-10, 0.8, 761, 10, 90);*/
	return EXIT_SUCCESS;
}
