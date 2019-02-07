#pragma once
#include <vector>
#include "Image.h"
#include "PixelMap.h"
#include "GrayPixel.h"

using std::vector;

class PgmImage : public Image
{
	PixelMap<GrayPixel> graymap;

public:
	PgmImage(const ImageMeta& meta, PixelMap<GrayPixel> graymap);
	const PixelMap<GrayPixel>& GetPixels() const { return graymap; }
	int GetWidth() const override { return graymap.GetWidth(); }
	int GetHeight() const override { return graymap.GetHeight(); }
	shared_ptr<Image> ToPbm() override;
	shared_ptr<Image> ToPgm() override;
	shared_ptr<Image> ToPpm() override;
	shared_ptr<Image> Negative() override;
	shared_ptr<Image> Tresholding(const unsigned short treshold) override;
	shared_ptr<Image> BlackTresholding(const unsigned short treshold) override;
	shared_ptr<Image> WhiteTresholding(const unsigned short treshold) override;
	shared_ptr<Image> GammaCorrection(double gamma) override;
	shared_ptr<Image> LevelChange(const unsigned short blackTreshold, const unsigned short whiteTreshold) override;
	shared_ptr<Image> Contouring() override;
	shared_ptr<Image> HorizontalBlur() override;
	shared_ptr<Image> VerticalBlur() override;
	shared_ptr<Image> HistogramStretching() override;
};
