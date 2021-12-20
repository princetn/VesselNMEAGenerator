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
    Init();

    
}

GPS::Date::~Date()
{
    _stringDate.erase();
    _structDate.reset();
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

void GPS::Date::setstringDate(std::string str)
{
    _stringDate = str;
}

GPS::Ptr_tm GPS::Date::getNumericDate()
{
    // current date/time based on current system
    time_t now = time(0);
    tm* buf = new tm;
    //char str[26];
    // convert now to string form
    localtime_s(buf, &now);

    *_structDate = *buf;


    return _structDate;
}

void GPS::Date::setNumericDate()
{
}

float GPS::Date::getUTC_Time()
{
    /*
    time_t now = time(0);
    tm* buf = new tm;
    gmtime_s(buf, &now);
    */
    UpdateDateGM();

    _UTC_time = _structDate->tm_hour * 10000 + _structDate->tm_min * 100 + _structDate->tm_sec;
    return _UTC_time;
}

void GPS::Date::setUTC_Time(float t)
{
    _UTC_time =t;
}

float GPS::Date::getNumDate()
{
    UpdateDateLocal();
    auto res = _structDate->tm_year - 100 + (_structDate->tm_mon + 1) * 100 + _structDate->tm_mday * 10000 + 0.01f;
    return res;
}

void GPS::Date::Init()
{
    setUTC_Time(0);
    _stringDate = "Fe 19 2021";
    _structDate = std::make_shared<tm>(tm());


    getstringDate();
    getNumericDate();
    getUTC_Time();



}

void GPS::Date::UpdateDateGM()
{
    time_t now = time(0);
    tm* buf = new tm;
    gmtime_s(buf, &now);

    *_structDate = (*buf); // copy updated tm

}

void GPS::Date::UpdateDateLocal()
{
    time_t now = time(0);
    tm* buf = new tm;
    localtime_s(buf, &now);

    *_structDate = *buf; // copy updated tm
}
