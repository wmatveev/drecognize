#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include "Digit.hpp"

#include <string>
#include <opencv2/opencv.hpp>


class ImageProcessing
{
    public:
        ImageProcessing(std::string path);

        void imageNormalize(GeoDataImages& geoDataImages);

    private:
        std::string pathToImage;
        cv::Mat image;

        int calculateHistogram();
        void drawHistogram(const int &histSize, const cv::Mat &histImage, const int &bin_w, const int &histH, const cv::Mat &hist);
        int  calculateBrightnessLevel(const cv::Mat& image, int step = 10);
        bool isBrightImage(const cv::Mat& hist, int histSize);

        std::pair<double, double> calculateBrightnessAndContrast(cv::Mat image);
        cv::Mat applyMaskBasedOnBrightness(cv::Mat image, int brightnessLevel);
};

#endif // IMAGEPROCESSING_H
