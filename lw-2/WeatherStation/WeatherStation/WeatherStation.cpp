﻿#include "stdafx.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	statsDisplay.AddWeatherCalculator([](const SWeatherInfo& wd) {
		return wd.temperature;
	}, "temperature");

	statsDisplay.AddWeatherCalculator([](const SWeatherInfo& wd) {
		return wd.humidity;
	}, "humidity");

	statsDisplay.AddWeatherCalculator([](const SWeatherInfo& wd) {
		return wd.pressure;
	}, "pressure");

	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	return EXIT_SUCCESS;
}
