#ifndef TARGET_H
#define TARGET_H

#include "ILocation.hpp"


class Target : public ILocation
{
public:
    Target();

    std::string getLongitude() override { return longitude; }
    std::string getLatitude()  override { return latitude;  }
    std::string getAltitude()  override { return altitude;  }
    std::string getDistance()  const    { return distance;  }

    void setLongitude(const std::string &lon) override { longitude = lon;  }
    void setLatitude(const std::string  &lat) override { latitude  = lat;  }
    void setAltitude(const std::string  &alt) override { altitude  = alt;  }
    void setDistance(const std::string& dist)          { distance  = dist; }

private:
    int satellites; // Количество спутников

    std::string longitude; // Долгота
    std::string latitude;  // Широта
    std::string altitude;  // Высота
    std::string distance;  // Дистанция
};

#endif // TARGET_H
