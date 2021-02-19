#include "GPS.h"
#include<string>
#include "Date.h"

GPS::GPS::GPS()
{
}

GPS::GPS::~GPS()
{
}

std::string GPS::GPS::NMEAMessage()
{
    std::string str = "";

    return str;
}

void GPS::GPS::setGPSRate(float rate)
{
    _gpsRate = rate;
}

void GPS::GPS::setSpeed(float speed)
{
    _speed = speed;
}

std::string GPS::GPS::GRMC()
{
    return std::string();
}

std::string GPS::GPS::GGA()
{
    return std::string();
}

std::string GPS::GPS::GSA()
{
    return std::string();
}

std::string GPS::GPS::GLL()
{
    return std::string();
}

