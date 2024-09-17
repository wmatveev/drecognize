#ifndef POSITION_H
#define POSITION_H

#include "ILocation.hpp"


class Position : public ILocation
{
    public:
        Position();

        std::string getLongitude() override { return longitude; }
        std::string getLatitude()  override { return latitude;  }
        std::string getAltitude()  override { return altitude;  }

        void setLongitude(const std::string &lon) override { longitude  = lon; }
        void setLatitude(const std::string  &lat) override { latitude   = lat; }
        void setAltitude(const std::string  &alt) override { altitude   = alt; }
        void setSatellites(const std::string &sat)         { if (!sat.empty()) satellites = std::stoi(sat); }

    private:
        int satellites; // Количество спутников

        std::string longitude; // Долгота
        std::string latitude;  // Широта
        std::string altitude;  // Высота
};

#endif // POSITION_H
