#pragma once
#include <vector>
#include "Image.h"
#include "PixelMap.h"
#include "RgbPixel.h"
#include "Filterer.h"

using std::vector;

class PpmImage : public Image
{
	PixelMap<RgbPixel> colormap;

public:
	PpmImage(const ImageMeta& meta, PixelMap<RgbPixel> colormap);
	const PixelMap<RgbPixel>& GetPixels() const { return colormap; }
	int GetWidth() const override { return colormap.GetWidth(); }
	int GetHeight() const override { return colormap.GetHeight(); }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;
	shared_ptr<Image> Negative() override;
	shared_ptr<Image> Tresholding(const unsigned short treshold) override;
	shared_ptr<Image> BlackTresholding(const unsigned short treshold) override;
	shared_ptr<Image> WhiteTresholding(const unsigned short treshold) override;
	shared_ptr<Image> GammaCorrection(const double gamma) override;
	shared_ptr<Image> LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold) override;
	shared_ptr<Image> Contouring() override;
	shared_ptr<Image> HorizontalBlur() override;
	shared_ptr<Image> VerticalBlur() override;
	shared_ptr<Image> HistogramStretching() override;

private:
	static RgbPixel ContourEveryChannel(const RgbPixel& pixel, const RgbPixel& pixelBelow,
	                                    const RgbPixel& pixelToTheRight);
	static RgbPixel BlurEveryChannelHorizontaly(const RgbPixel& pixelToTheLeft, const RgbPixel& pixel,
	                                            const RgbPixel& pixelToTheRight);
	static RgbPixel BlurEveryChannelVerticaly(const RgbPixel& pixelAbove, const RgbPixel& pixel,
	                                          const RgbPixel& pixelBelow);
	static RgbPixel StretchEveryChannelsHistogram(const Filterer& filterer, const RgbPixel& pixel,
	                                       const RgbPixel& minExistingValues, const RgbPixel& maxExistingValues);
	RgbPixel FindMinExistingValues();
	RgbPixel FindMaxExistingValues();
};
