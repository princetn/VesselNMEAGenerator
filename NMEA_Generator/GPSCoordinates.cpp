#include "GPSCoordinates.h"


using namespace GPS;



float GPSCoordinates::getLat()
{
    return _lat;
}

void GPSCoordinates::setLat(float lat)
{
    _lat = lat;
}

float GPSCoordinates::getLong()
{
    return _lon;
}

void GPSCoordinates::setLong(float lon)
{
    _lon = lon;
}

GPSCoordinates::EWHeading GPSCoordinates::getEWHeading()
{
    return _EW;
}

void GPSCoordinates::setEWHeading(EWHeading ew)
{
}

GPSCoordinates::NSHeading GPSCoordinates::getNSHeading()
{
    return _NS;
}

void GPSCoordinates::setNSHeading(NSHeading ns)
{
}

float GPSCoordinates::getSpeedOverGround()
{
    return _speedOverGround;
}

float GPSCoordinates::getCourseOverGround()
{
    return _courseOverGround;
}
