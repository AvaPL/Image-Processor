#pragma once
#include <vector>

using std::vector;

//TODO: Add ForwardIterator.

template <typename T>
class PixelMap
{
	vector<vector<T>> pixels;

public:
	explicit PixelMap(int width = 0, int height = 0) : pixels(vector<vector<T>>(width, vector<T>(height)))
	{
	}

	~PixelMap() = default;
	PixelMap(const PixelMap&) = default;

	PixelMap(PixelMap&& pixelMapToMove) noexcept : pixels(std::move(pixelMapToMove.pixels))
	{
	};
	PixelMap& operator =(const PixelMap&) = default;
	PixelMap& operator =(PixelMap&& pixelMapToMove) noexcept;
	T& operator()(int row, int column) { return pixels.at(column).at(row); };
	int Width() const { return pixels.size(); }
	int Height() const { return pixels.at(0).size(); }
};

template <typename T>
PixelMap<T>& PixelMap<T>::operator=(PixelMap&& pixelMapToMove) noexcept
{
	this->pixels = std::move(pixelMapToMove.pixels);
	return *this;
}
