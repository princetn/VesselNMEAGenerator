/*******************************************************************************
Date

PURPOSE: Provide actual date for GPS NMEA.

CREATED: 2/17/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#include "Date.h"
#include<string>

GPS::Date::Date()
{
    setUTC_Time(0);
    _stringDate = "Fe 19 2021";
    _numericDate = std::make_shared<tm>(tm());
}

GPS::Date::~Date()
{
    _stringDate.erase();
    _numericDate.reset();
}

std::string GPS::Date::getstringDate()
{
    // current date/time based on current system
    time_t now = time(0);
    tm* buf = new tm;
    char str[26];
    // convert now to string form
    localtime_s(buf, &now);
     asctime_s(str,sizeof str,buf);
     
    _stringDate = str;




    return _stringDate;
}

void GPS::Date::setstringDate()
{
}

GPS::Ptr_tm GPS::Date::getNumericDate()
{
    // current date/time based on current system
    time_t now = time(0);
    tm* buf = new tm;
    //char str[26];
    // convert now to string form
    localtime_s(buf, &now);

    _numericDate = Ptr_tm(buf);


    return _numericDate;
}

void GPS::Date::setNumericDate()
{
}

float GPS::Date::getUTC_Time()
{
    return _UTC_time;
}

void GPS::Date::setUTC_Time(float t)
{
    _UTC_time =t;
}
