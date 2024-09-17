
#include "DigitRecognition.hpp"
#include <tesseract/baseapi.h>


DigitRecognition::DigitRecognition() {}


std::pair<Position, Target> DigitRecognition::process(const GeoDataImages &geoDataImages)
{
    Position position;
    Target target;

    try {
        [this, &position, &geoDataImages]() {
            position.setLatitude  (recognize(geoDataImages.latitudeNPosition.digit));
        }();

        position.setLatitude  (recognize(geoDataImages.latitudeNPosition.digit));
        position.setLongitude (recognize(geoDataImages.longitudeEPosition.digit));
        position.setAltitude  (recognize(geoDataImages.altitudePosition.digit));
        position.setSatellites(recognize(geoDataImages.satelliteCount.digit));

        target.setLatitude (recognize(geoDataImages.latitudeNTarget.digit));
        target.setLongitude(recognize(geoDataImages.longitudeETarget.digit));
        target.setAltitude (recognize(geoDataImages.altitudeTarget.digit));
        target.setDistance (recognize(geoDataImages.distanceToTarget.digit));
    } catch (const std::exception& e) {
        std::cerr << "Поймано исключение: " << e.what() << std::endl;
    }

    return std::make_pair(position, target);
}

std::string DigitRecognition::recognize(const cv::Mat &image)
{
    if (image.empty()) {
        throw std::runtime_error("Пришел пустой cv::Mat для распознования");
    }

    tesseract::TessBaseAPI ocr;
    if (ocr.Init(NULL, "eng", tesseract::OEM_LSTM_ONLY)) {
        std::cerr << "Не удалось инициализировать Tesseract OCR!" << std::endl;
        return "";
    }

    ocr.SetVariable("tessedit_char_whitelist", "0123456789°.,'m");
    ocr.SetPageSegMode(tesseract::PSM_SINGLE_LINE);

    ocr.SetImage(image.data, image.cols, image.rows, 1, image.step);

    ocr.SetSourceResolution(300);
    std::string text = std::string(ocr.GetUTF8Text());

    std::cout << "Text: " << text << std::endl;

    ocr.End();

    cv::imshow("Изображение", image);
    cv::waitKey(0);

    return text;
}
