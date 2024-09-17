

#include <cmath>
#include <tesseract/baseapi.h>

#include "ImageProcessing.hpp"



ImageProcessing::ImageProcessing(std::string path)
    : pathToImage{std::move(path)}
{
    image = cv::imread(pathToImage);

    if (image.empty()) {
        std::cerr << "Ошибка при загрузке изображения" << std::endl;
        return ;
    }
}


void ImageProcessing::imageNormalize(GeoDataImages& geoDataImages)
{
    double koef = 1;

    cv::Rect boundingBox = cv::Rect(425, 978, 135, 23);
    cv::Mat  img = image(boundingBox).clone();

    auto [brightness, contrast] = calculateBrightnessAndContrast(img);
    auto processedImage = applyMaskBasedOnBrightness(img, (brightness + contrast) * koef);

    geoDataImages.latitudeNPosition.boundingBox = boundingBox;
    geoDataImages.latitudeNPosition.digit = processedImage;

    /** *************************** */

    boundingBox = cv::Rect(607, 978, 135, 23);
    img = image(boundingBox).clone();

    std::tie(brightness, contrast) = calculateBrightnessAndContrast(img);
    processedImage = applyMaskBasedOnBrightness(img, (brightness + contrast) * 0.97);

    geoDataImages.longitudeEPosition.boundingBox = boundingBox;
    geoDataImages.longitudeEPosition.digit = processedImage;

    /** *************************** */

    boundingBox = cv::Rect(520, 1009, 32, 23);
    img = image(boundingBox).clone();

    std::tie(brightness, contrast) = calculateBrightnessAndContrast(img);
    processedImage = applyMaskBasedOnBrightness(img, (brightness + contrast) * 1.03);

    geoDataImages.satelliteCount.boundingBox = boundingBox;
    geoDataImages.satelliteCount.digit = processedImage;

    /** *************************** */

    boundingBox = cv::Rect(679, 1009, 100, 23);
    img = image(boundingBox).clone();

    std::tie(brightness, contrast) = calculateBrightnessAndContrast(img);
    processedImage = applyMaskBasedOnBrightness(img, (brightness + contrast) * koef);

    geoDataImages.altitudePosition.boundingBox = boundingBox;
    geoDataImages.altitudePosition.digit = processedImage;

    /** *************************** */
    /** *************************** */

    boundingBox = cv::Rect(1199, 948, 135, 23);
    img = image(boundingBox).clone();

    std::tie(brightness, contrast) = calculateBrightnessAndContrast(img);
    processedImage = applyMaskBasedOnBrightness(img, (brightness + contrast) * koef);

    geoDataImages.latitudeNTarget.boundingBox = boundingBox;
    geoDataImages.latitudeNTarget.digit = processedImage;

    /** *************************** */

    boundingBox = cv::Rect(1381, 948, 135, 23);
    img = image(boundingBox).clone();

    std::tie(brightness, contrast) = calculateBrightnessAndContrast(img);
    processedImage = applyMaskBasedOnBrightness(img, (brightness + contrast) * koef);

    geoDataImages.longitudeETarget.boundingBox = boundingBox;
    geoDataImages.longitudeETarget.digit = processedImage;

    /** *************************** */

    boundingBox = cv::Rect(1246, 978, 100, 23);
    img = image(boundingBox).clone();

    std::tie(brightness, contrast) = calculateBrightnessAndContrast(img);
    processedImage = applyMaskBasedOnBrightness(img, (brightness + contrast) * koef);

    geoDataImages.distanceToTarget.boundingBox = boundingBox;
    geoDataImages.distanceToTarget.digit = processedImage;

    /** *************************** */

    boundingBox = cv::Rect(1452, 978, 100, 23);
    img = image(boundingBox).clone();

    std::tie(brightness, contrast) = calculateBrightnessAndContrast(img);
    processedImage = applyMaskBasedOnBrightness(img, (brightness + contrast) * koef);

    geoDataImages.altitudeTarget.boundingBox = boundingBox;
    geoDataImages.altitudeTarget.digit = processedImage;

    /** *************************** */
}

cv::Mat ImageProcessing::applyMaskBasedOnBrightness(cv::Mat image,int brightnessLevel)
{
    // std::cout << "Уровень яркости изображения: " << brightnessLevel << std::endl;

    cv::Scalar lower_bound(brightnessLevel, brightnessLevel, brightnessLevel);
    // cv::Scalar lower_bound(150, 150, 150);

    cv::Scalar upper_bound(255, 255, 255);

    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            cv::Vec3b color = image.at<cv::Vec3b>(y, x);

            if (color[0] >= lower_bound[0] && color[1] >= lower_bound[1] && color[2] >= lower_bound[2]) {
                image.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
            } else {
                image.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
            }
        }
    }

    cv::Mat img_gray;
    cv::cvtColor(image, img_gray, cv::COLOR_BGR2GRAY);

    cv::Mat img_8bit;
    img_gray.convertTo(img_8bit, CV_8U);

    return img_8bit;
}

int ImageProcessing::calculateHistogram()
{
    cv::Mat img_gray;
    cv::cvtColor(image, img_gray, cv::COLOR_BGR2GRAY);

    int   histSize = 256;       // Количество уровней яркости
    float range[]  = {0, 256};  // Диапазон яркостей
    const float* histRange = {range};
    cv::Mat hist;

    cv::calcHist(&img_gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);

    // Нормализуем гистограмму для отображения
    int histW = 512, histH = 400;

    cv::Mat histImage(histH, histW, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::normalize(hist, hist, 0, histImage.rows, cv::NORM_MINMAX);

    /* Раскомментировать, если нужно нарисовать гистограмму * /
    int bin_w = std::round((double) histW / histSize);
    drawHistogram(histSize, histImage, bin_w, histH, hist);
    / **/

    return calculateBrightnessLevel(hist, 1);
}

void ImageProcessing::drawHistogram(const int &histSize, const cv::Mat &histImage, const int &bin_w, const int &histH, const cv::Mat &hist)
{
    for (int i = 1; i < histSize; i++) {
        cv::line(histImage,
                 cv::Point(bin_w * (i - 1), histH - std::round(hist.at<float>(i - 1))),
                 cv::Point(bin_w * i, histH - std::round(hist.at<float>(i))),
                 cv::Scalar(255, 255, 255), 2, 8, 0);
    }

    cv::imshow("Гистограмма", histImage);
    cv::waitKey(0);
}

int ImageProcessing::calculateBrightnessLevel(const cv::Mat& image, int step)
{
    cv::Scalar meanBrightness = cv::mean(image);

    int brightness = static_cast<int>(meanBrightness[0]);
    brightness = std::round(brightness / static_cast<float>(step)) * step;

    return brightness;
}

std::pair<double, double> ImageProcessing::calculateBrightnessAndContrast(cv::Mat image)
{
    cv::Mat gray;
    if (image.channels() == 3) {
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    } else {
        gray = image;
    }

    // Вычисляем среднее значение яркости и стандартное отклонение
    cv::Scalar meanBrightness, stdDev;
    cv::meanStdDev(gray, meanBrightness, stdDev);

    // Возвращаем среднее значение яркости и стандартное отклонение
    return {meanBrightness[0], stdDev[0]};
}

bool ImageProcessing::isBrightImage(const cv::Mat &hist, int histSize)
{
    float brightnessThreshold = 0.5;
    float brightnessSum = 0.0;

    for (int i = histSize / 2; i < histSize; ++i) {
        brightnessSum += hist.at<float>(i);
    }

    // Если суммарная яркость выше порога, изображение светлое
    return (brightnessSum / cv::sum(hist)[0]) > brightnessThreshold;
}

