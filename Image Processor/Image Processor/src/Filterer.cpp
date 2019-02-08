#include "../inc/Filterer.h"
#include <cmath>

size_t Filterer::Negative(const size_t value) const
{
	return maxValue - value;
}

size_t Filterer::Tresholding(const size_t value, const size_t treshold) const
{
	return value <= treshold ? 0 : maxValue;
}

size_t Filterer::BlackTresholding(const size_t value, const size_t treshold)
{
	return value <= treshold ? 0 : value;
}

size_t Filterer::WhiteTresholding(const size_t value, const size_t treshold) const
{
	return value > treshold ? maxValue : value;
}

size_t Filterer::GammaCorrection(const size_t value, const double gamma) const
{
	return static_cast<size_t>(pow(value, 1 / gamma) / pow(maxValue, (1 - gamma) / gamma));
}

size_t Filterer::LevelChange(const size_t value, const size_t blackTreshold, const size_t whiteTreshold) const
{
	size_t result;
	if (value <= blackTreshold) result = 0;
	else if (value >= whiteTreshold) result = maxValue;
	else result = (value - blackTreshold) * maxValue / (whiteTreshold - blackTreshold);
	return result;
}
