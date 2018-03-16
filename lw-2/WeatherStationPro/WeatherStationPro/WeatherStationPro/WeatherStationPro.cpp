#include "stdafx.h"

int main()
{
	CWeatherData in;
	CWeatherData out;

	CDisplay display(in, out);
	in.RegisterObserver(display, 1);
	out.RegisterObserver(display, 1);

	CStatsDisplay statsDisplay(in, out);
	statsDisplay.AddWeatherCalculator(in, [](const SWeatherInfo& wd) {
		return wd.temperature;
	}, std::make_unique<StatsCalculator>("temperature"));

	statsDisplay.AddWeatherCalculator(in, [](const SWeatherInfo& wd) {
		return wd.humidity;
	}, std::make_unique<StatsCalculator>("humidity"));

	statsDisplay.AddWeatherCalculator(in, [](const SWeatherInfo& wd) {
		return wd.pressure;
	}, std::make_unique<StatsCalculator>("pressure"));

	statsDisplay.AddWeatherCalculator(in, [](const SWeatherInfo& wd) {
		return wd.speed;
	}, std::make_unique<StatsCalculator>("speed"));

	statsDisplay.AddWeatherCalculator(in, [](const SWeatherInfo& wd) {
		return wd.windDirection;
	}, std::make_unique<StatsWindDirectionCalculator>("wind direction"));


	statsDisplay.AddWeatherCalculator(out, [](const SWeatherInfo& wd) {
		return wd.temperature;
	}, std::make_unique<StatsCalculator>("temperature"));

	statsDisplay.AddWeatherCalculator(out, [](const SWeatherInfo& wd) {
		return wd.humidity;
	}, std::make_unique<StatsCalculator>("humidity"));

	statsDisplay.AddWeatherCalculator(out, [](const SWeatherInfo& wd) {
		return wd.pressure;
	}, std::make_unique<StatsCalculator>("pressure"));

	statsDisplay.AddWeatherCalculator(out, [](const SWeatherInfo& wd) {
		return wd.speed;
	}, std::make_unique<StatsCalculator>("speed"));

	statsDisplay.AddWeatherCalculator(out, [](const SWeatherInfo& wd) {
		return wd.windDirection;
	}, std::make_unique<StatsWindDirectionCalculator>("wind direction"));


	in.RegisterObserver(statsDisplay, 14);
	out.RegisterObserver(statsDisplay, 5);

	in.SetMeasurements(4, 0.8, 761, 10, 0);
	
	out.SetMeasurements(4, 0.8, 761, 10, 0);

	in.SetMeasurements(4, 0.8, 761, 10, 90);

	return EXIT_SUCCESS;
}
