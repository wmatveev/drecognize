#ifndef DIGIT_H
#define DIGIT_H

#include <opencv2/opencv.hpp>


struct DigitsPositionOnFrame
{
    cv::Mat  digit;
    cv::Rect boundingBox;
};

struct GeoDataImages
{
    DigitsPositionOnFrame latitudeNPosition;    // Северная широта позиции (N)
    DigitsPositionOnFrame longitudeEPosition;   // Восточная долгота позиции (E)
    DigitsPositionOnFrame altitudePosition;     // Высота позиции
    DigitsPositionOnFrame latitudeNTarget;      // Северная широта цели (N)
    DigitsPositionOnFrame longitudeETarget;     // Восточная долгота цели (E)
    DigitsPositionOnFrame altitudeTarget;       // Высота цели
    DigitsPositionOnFrame distanceToTarget;     // Расстояние до цели
    DigitsPositionOnFrame satelliteCount;       // Количество спутников
};

#endif // DIGIT_H
