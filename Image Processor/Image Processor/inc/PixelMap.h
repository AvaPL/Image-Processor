#pragma once
#include <vector>

using std::vector;

template <typename PixelType>
class PixelMap
{
	vector<vector<PixelType>> pixels;

public:
	explicit PixelMap(size_t width, size_t height) : pixels(vector<vector<PixelType>>(width, vector<PixelType>(height)))
	{
	}

	~PixelMap() = default;
	PixelMap(const PixelMap&) = default;

	PixelMap(PixelMap&& pixelMapToMove) noexcept : pixels(std::move(pixelMapToMove.pixels))
	{
	};
	PixelMap& operator =(const PixelMap&) = default;
	PixelMap& operator =(PixelMap&& pixelMapToMove) noexcept;
	PixelType& operator()(size_t row, size_t column) { return pixels.at(column).at(row); };
	const PixelType& operator()(size_t row, size_t column) const { return pixels.at(column).at(row); }
	size_t GetWidth() const { return pixels.size(); }
	size_t GetHeight() const { return pixels.at(0).size(); }

	class PixelMapIterator
	{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = PixelType;
		using difference_type = ptrdiff_t;
		using pointer = PixelType *;
		using reference = PixelType &;

		PixelMapIterator(PixelMap& pixelMap, const int currentRow, const int currentColumn): pixelMap(pixelMap),
		                                                                                     currentRowIndex(
			                                                                                     currentRow),
		                                                                                     currentColumnIndex(
			                                                                                     currentColumn)
		{
		}

		PixelMapIterator& operator++();
		PixelMapIterator operator++(int);
		reference operator*() { return pixelMap(currentRowIndex, currentColumnIndex); };
		pointer operator->() { return &pixelMap(currentRowIndex, currentColumnIndex); };
		bool operator==(const PixelMapIterator& otherIterator);
		bool operator!=(const PixelMapIterator& otherIterator);
	private:
		PixelMap& pixelMap;
		size_t currentRowIndex;
		size_t currentColumnIndex;
	};

	PixelMapIterator begin() { return PixelMapIterator(*this, 0, 0); }
	PixelMapIterator end();
};

template <typename PixelType>
PixelMap<PixelType>& PixelMap<PixelType>::operator=(PixelMap&& pixelMapToMove) noexcept
{
	this->pixels = std::move(pixelMapToMove.pixels);
	return *this;
}

template <typename PixelType>
typename PixelMap<PixelType>::PixelMapIterator& PixelMap<PixelType>::PixelMapIterator::operator++()
{
	++currentColumnIndex;
	if (currentColumnIndex == pixelMap.GetWidth())
	{
		++currentRowIndex;
		currentColumnIndex = 0;
	}
	return *this;
}

template <typename PixelType>
typename PixelMap<PixelType>::PixelMapIterator PixelMap<PixelType>::PixelMapIterator::operator++(int)
{
	const int previousStepRowIndex = currentRowIndex;
	const int previousStepColumnIndex = currentColumnIndex;
	if (currentColumnIndex == pixels.size())
	{
		++currentRowIndex;
		currentColumnIndex = 0;
	}
	return PixelMapIterator(pixelMap, previousStepRowIndex, previousStepColumnIndex);
}

template <typename PixelType>
bool PixelMap<PixelType>::PixelMapIterator::operator==(const PixelMapIterator& otherIterator)
{
	return currentRowIndex == otherIterator.currentRowIndex && currentColumnIndex == otherIterator.currentColumnIndex;
}

template <typename PixelType>
bool PixelMap<PixelType>::PixelMapIterator::operator!=(const PixelMapIterator& otherIterator)
{
	return currentRowIndex != otherIterator.currentRowIndex || currentColumnIndex != otherIterator.currentColumnIndex;
}

template <typename PixelType>
typename PixelMap<PixelType>::PixelMapIterator PixelMap<PixelType>::end()
{
	//Iterator returned by end() points to the element next to the last element. Last element 
	//index is (height - 1, width - 1). Incrementing the iterator at last element will change 
	//index to row past the last one and first column, so index will be (height, 0).
	return PixelMapIterator(*this, GetHeight(), 0);
}
