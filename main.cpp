
#include <sys/time.h>

#include "Digit.hpp"
#include "Position.hpp"
#include "Target.hpp"
#include "ImageProcessing.hpp"
#include "DigitRecognition.hpp"



int main(int argc, char *argv[])
{
    std::string pathToFile = "/home/wmatveev/_dev/digitprot/#images/original/15_08_01.jpg";
    // std::string pathToFile = "/home/wmatveev/_dev/digitprot/#images/original/15_09_38.jpg";
    // std::string pathToFile = "/home/wmatveev/_dev/digitprot/#images/original/15_10_55.jpg";

    struct timeval start, end;
    gettimeofday(&start, nullptr);

    Position position;
    Target   target;
    GeoDataImages geoDataImages;

    auto imageProcessing = std::make_shared<ImageProcessing>(pathToFile);
    imageProcessing->imageNormalize(geoDataImages);

    auto digitRecognation = std::make_shared<DigitRecognition>();
    std::tie(position, target) = digitRecognation->process(geoDataImages);

    gettimeofday(&end, nullptr);

    long time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1000L;
    time_taken += (end.tv_usec - start.tv_usec) / 1000L;

    std::cout << "Время выполнения: " << time_taken << " миллисекунд" << std::endl;

    return 0;
}
