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
	static size_t Contouring(const size_t value, const size_t valueBelow, const size_t valueToTheRight);
	static size_t HorizontalBlur(const size_t valueToTheLeft, const size_t value, const size_t valueToTheRight);
	static size_t VerticalBlur(const size_t valueAbove, const size_t value, const size_t valueBelow);
	size_t HistogramStretching(const size_t value, const size_t existingMinValue, const size_t existingMaxValue) const;
};
