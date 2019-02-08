#pragma once

class Filterer
{
	size_t maxValue;

public:
	explicit Filterer(const size_t maxValue): maxValue(maxValue)
	{
	}

	size_t Negative(const size_t value) const;
	size_t Tresholding(const size_t value, const size_t treshold) const;
	static size_t BlackTresholding(const size_t value, const size_t treshold);
	size_t WhiteTresholding(const size_t value, const size_t treshold) const;
	size_t GammaCorrection(const size_t value, const double gamma) const;
	size_t LevelChange(const size_t value, const size_t blackTreshold, const size_t whiteTreshold) const;
};
