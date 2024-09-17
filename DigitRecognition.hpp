#ifndef DIGITRECOGNITION_H
#define DIGITRECOGNITION_H

#include "Position.hpp"
#include "Target.hpp"
#include "Digit.hpp"

class DigitRecognition
{
    public:
        DigitRecognition();

        std::pair<Position, Target> process(const GeoDataImages &geoDataImages);

    private:
        std::string recognize(const cv::Mat &image);
        bool postProcess();
};

#endif // DIGITRECOGNITION_H
