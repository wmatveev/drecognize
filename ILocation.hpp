#ifndef ILOCATION_H
#define ILOCATION_H

#include <string>


class ILocation
{
    public:
        virtual ~ILocation() {}

        virtual std::string getLongitude() = 0;
        virtual std::string getLatitude()  = 0;
        virtual std::string getAltitude()  = 0;

        virtual void setLongitude(const std::string &longitude) = 0;
        virtual void setLatitude(const std::string  &latitude)  = 0;
        virtual void setAltitude(const std::string  &altitude)  = 0;
};

#endif // ILOCATION_H
