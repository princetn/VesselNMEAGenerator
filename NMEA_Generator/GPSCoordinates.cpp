/*******************************************************************************
GPSCoordinates

PURPOSE: Provide GPS coordinates.

CREATED: 2/19/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/


#include "GPSCoordinates.h"


using namespace GPS;



GPS::GPSCoordinates::GPSCoordinates()
{
    Init();
}

GPS::GPSCoordinates::GPSCoordinates(float lat, float lon, EWHeading ew, NSHeading ns, float sog, float cog)
:_lat(lat),_lon(lon),_EW(ew),_NS(ns),_speedOverGround(sog),_courseOverGround(cog)
{
}

GPS::GPSCoordinates::~GPSCoordinates()
{
}

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

float GPS::GPSCoordinates::getNSsign()
{
    return (_NS == NSHeading::N) ? 1.0f : -1.0f;
}

float GPS::GPSCoordinates::getEWsign()
{
    return (_EW == EWHeading::E) ? 1.0f : -1.0f;
}

char GPS::GPSCoordinates::getEWChar()
{
    
    return (getEWHeading() == EWHeading::E)?'E':'W';
}

char GPS::GPSCoordinates::getNSChar()
{
    return (getNSHeading() == NSHeading::N)?'N':'S';
}

void GPS::GPSCoordinates::Init()
{
    setLat(0);
    setLong(0);
    setEWHeading(EWHeading::E);
    setNSHeading(NSHeading::N);
    _speedOverGround = 0;
    _courseOverGround = 0;
}
