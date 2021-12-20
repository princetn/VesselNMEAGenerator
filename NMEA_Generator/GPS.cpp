/*******************************************************************************
GPS

PURPOSE: Provide GPS NMEA API. Create a GPS sensor to generate NMEA 183 messages.

CREATED: 2/17/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#include "GPS.h"
#include<string>
#include "Date.h"
#include <sstream>
#include <stdexcept>
#include "Satellite.h"
#include "Timer.h"
#include <string.h>
#include <iomanip>
#include "Format.h"

using namespace Formatter;

GPS::GPS::GPS()
{
    Init();
}

GPS::GPS::~GPS()
{
}

GPS::GPS::GPS(const GPS& gps)
{
    //throw std::exception( "GPS copy constructor need to get implemented");
     _start = gps._start; // starting point
     _end = gps._end;
     _currentCoord = gps._currentCoord;
    _waypt = gps._waypt;
    _wayptIndex = gps._wayptIndex;
    _date = gps._date;
    _speed = gps._speed; // m/s
    //float _gpsRate; _refresh from NMEA base class.
    _gpsType = gps._gpsType;
    _sat = gps._sat;
    _gpsNMEAbuf = gps._gpsNMEAbuf; // store the NMEA data to send over udp
    _status = gps._status;
    _Units = gps._Units;
    _MSLAltitude = gps._MSLAltitude;
    _PDOP = gps._PDOP;
    _HDOP = gps._HDOP;
    _VDOP = gps._VDOP;
    _Mode1 = gps._Mode1;
    _Mode = gps._Mode;
    _Mode2 = gps._Mode2;

    _timer = gps._timer;
    _queue_lock = gps._queue_lock;
    _refresh = gps._refresh;

}

std::string GPS::GPS::NMEAMessage()
{
    std::string str = "";
    bool isBuffEmpty = false;
    const int MaxIt = 2 * ceil(1 / _refresh) * 1000 / 100;
    int it = 0;
    while (!isBuffEmpty && it < MaxIt) // wait until buffer is filled.
    {
        std::lock_guard<std::mutex>(*_queue_lock);
        if (!_gpsNMEAbuf->empty())
        {
            str = _gpsNMEAbuf->front();
            _gpsNMEAbuf->pop();
            isBuffEmpty = true;


            
        }
        else
        {
            
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait a little bit and try again.

    }
    

    


    














    return str;
}

void GPS::GPS::setGPSRate(float rate)
{
    _refresh = rate;
}

void GPS::GPS::setSpeed(float speed)
{
    _speed = speed;
}

void GPS::GPS::setGPSType(GPSType t)
{
    _gpsType = t;
}

void GPS::GPS::setWayPoint(WayPoint waypt)
{
    _waypt = waypt;
}

void GPS::GPS::setVector(Ptr_GPSCoordinates start, Ptr_GPSCoordinates end)
{
    _start = start;

    _end = end;
}

char GPS::GPS::getUnits()
{
    return _Units;
}

void GPS::GPS::setUnits(char unit)
{
    _Units = unit;

}

float GPS::GPS::getMSL()
{
    return _MSLAltitude;
}

void GPS::GPS::setMSL(float altitude)
{
    _MSLAltitude = altitude;
}

float GPS::GPS::getHDOP()
{
    return _HDOP;
}

void GPS::GPS::setHDOP(float v)
{
    _HDOP = v;
}

std::string GPS::GPS::GRMC()
{
    std::string str = "";
    std::ostringstream ss;
    Format float3(3);
    ss << "RMC" << "," << _date->getUTC_Time() << "," << _status << ","
        << float3(_currentCoord->getLat()) << "," << _currentCoord->getNSChar() << "," << float3(_currentCoord->getLong())
        << "," << _currentCoord->getEWChar() << "," << float3(_currentCoord->getSpeedOverGround()) << "," 
        << float3(_currentCoord->getCourseOverGround()) << "," << _date->getNumDate() << "," << ",";

  
    
    str = ss.str();


    return str;
}

std::string GPS::GPS::GGA()
{
    std::string str = "";
    std::ostringstream ss;
    Format float3(3);
    ss << "GGA" << "," << _date->getUTC_Time() << "," << float3(_currentCoord->getLat()) << "," << _currentCoord->getNSChar() << ","
        << float3(_currentCoord->getLong()) << "," << _currentCoord->getEWChar() << "," << _sat->getPositionFix()<<","
        <<_sat->getSatInView() << "," <<float3(_currentCoord->getSpeedOverGround()) << ","
        << float3(_currentCoord->getCourseOverGround()) << "," << _date->getNumDate() << "," << ",";



    str = ss.str();


    return str;
}

std::string GPS::GPS::GSA()
{
    std::string str = "";
    std::ostringstream ss;
    Format float3(3);

    ss << "GSA" << "," << _Mode1 << "," << _Mode2 << "," ;
    for (int i = 0; i < _sat->getSatNum(); i++)
    {
        ss << _sat->getSatInfo()[i].getSatID() << "," ;

    }
    ss << float3(_PDOP) << "," << float3(_HDOP) << "," << float3(_VDOP) << ",";

        str = ss.str();

    return str;
}

std::string GPS::GPS::GLL()
{
    std::string str = "";
    std::ostringstream ss;
    Format float3(3);

    ss << "GLL,";
    ss <<float3(_currentCoord->getLat()) << "," << _currentCoord->getNSChar() << "," << float3(_currentCoord->getLong())
        << "," << _currentCoord->getEWChar() << "," << _date->getUTC_Time() << "," << _status << "," << _Mode << ",";
    str = ss.str();

    return str;
}

void GPS::GPS::SetTimer()
{
    int interval = (int)round(1.0f / _refresh * 1000.0f);
    //GPS* thisone = this;
   // Timer::Timer<GPS> timer(*this, &GPS::AddNMEAmessages, interval);

   // _timer = std::make_shared<Timer::Timer<GPS>>(new Timer::Timer<GPS>(*thisone,&GPS::AddNMEAmessages, interval));

    _timer = std::make_shared<Timer::Timer<GPS>>(Timer::Timer<GPS>(*this, &GPS::AddNMEAmessages, interval));
   // auto tmp =  new Timer::Timer<GPS>(*this, &GPS::AddNMEAmessages, interval);
    //_timer = tmp;
}

void GPS::GPS::Init()
{
    //int interval = (int)round(1.0f / _refresh * 1000.0f);
    //GPS* thisone = this;
   // Timer::Timer<GPS> timer(*this, &GPS::AddNMEAmessages, interval);

   // _timer = std::make_shared<Timer::Timer<GPS>>(new Timer::Timer<GPS>(*thisone,&GPS::AddNMEAmessages, interval));
    
    //_timer = std::make_shared<Timer::Timer<GPS>>(Timer::Timer<GPS>(*this,&GPS::AddNMEAmessages,interval));
    _queue_lock = new std::mutex();
    _gpsNMEAbuf = new std::queue<std::string>();


    _date = std::make_shared<Date>(Date());
    //_currentCoord = _start;
    _sat = std::make_shared<Satellite>(Satellite());



}

void GPS::GPS::ComputeCurrentCoordinate()
{

    switch (_gpsType)
    {
    case GPSType::VECTOR:
        if (!_currentCoord)
        {
            _currentCoord = CalculateCoordinateBetweenTwoPts(_start, _end);
        }
        else
        {
            _currentCoord = CalculateCoordinateBetweenTwoPts(_currentCoord, _end);
        }
            

        break;
    case GPSType::WAYPOINT:
        // TODO: Implement way point.
        throw std::runtime_error("Waypoint is not implemented yet!");
        break;
    default: 
        throw std::runtime_error("You need to define the GPS type!");
    }


   
}

GPS::Ptr_GPSCoordinates GPS::GPS::CalculateCoordinateBetweenTwoPts(Ptr_GPSCoordinates start, Ptr_GPSCoordinates end)
{ // haversine to calculate the next coordinate knowning 
  //the heading (end-start), speed, delta time and a start point
   
    Ptr_GPSCoordinates coor = std::make_shared<GPSCoordinates>(*start);
    const float R = 6371e3;
    float theta1 = start->getLat() * start->getNSsign() * (float)PI / 180.0f;
    float theta2 = end->getLat() * end->getNSsign() * (float)PI / 180.0f;
    float dlambda = (end->getLong() * end->getEWsign() - start->getLong() * start->getEWsign()) * (float)PI / 180.0f;
    float dtheta = theta2 - theta1;

    float a = sin(dtheta / 2) * sin(dtheta / 2) + cos(theta1) * cos(theta2) * sin(dlambda / 2) * sin(dlambda / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float d = R * c; // distance.

    float gamma = _speed * (1 / _refresh) / d;
    gamma = (gamma > 1) ? 1 : gamma;


    float lat = start->getLat() * start->getNSsign() * (1-gamma) + gamma * end->getLat() * end->getNSsign();
    float lon = end->getLong() * end->getEWsign() * gamma + (1 - gamma) * start->getLong() * start->getEWsign();
    
    coor->setLat(abs(lat));
    coor->setLong(abs(lon));
    coor->setEWHeading((lon >= 0) ? GPSCoordinates::EWHeading::E : GPSCoordinates::EWHeading::W);
    coor->setNSHeading((lat >= 0) ? GPSCoordinates::NSHeading::N : GPSCoordinates::NSHeading::S);



    return coor;
}

std::string GPS::GPS::MakeNMEASentence(std::string str)
{
    std::ostringstream ss;
    ss << "GP" << str;
    str = ss.str();
    unsigned int n = str.length();
    char* s = new char[n+(unsigned int)1];
    strcpy_s(s,(n+(unsigned int)1)*sizeof(char), str.c_str());
    ss << "*"<<checksum(s) << "\r\n";
    
    str = "$"+ss.str();
    /*std::cout << s;
    std::cout << str;*/
    delete[] s;



    return str;
}

void GPS::GPS::AddNMEAmessages()
{
    
    ComputeCurrentCoordinate();
    /// <summary>
    /// GRMC
    /// </summary>
    std::string str = GRMC();
    str = MakeNMEASentence(str);
    std::lock_guard<std::mutex>(*_queue_lock);
    _gpsNMEAbuf->push(str);

    /// <summary>
    /// GGA
    /// </summary>
    str = GGA();
    str = MakeNMEASentence(str);
    //std::lock_guard<std::mutex>(*_queue_lock);
    _gpsNMEAbuf->push(str);

    /// <summary>
    /// GSA
    /// </summary>
    str = GSA();
    str = MakeNMEASentence(str);
    //std::lock_guard<std::mutex>(*_queue_lock);
    _gpsNMEAbuf->push(str);

    /// <summary>
    /// GLL
    /// </summary>
    str = GLL();
    str = MakeNMEASentence(str);
    //std::lock_guard<std::mutex>(*_queue_lock);
    _gpsNMEAbuf->push(str);
  


}

void GPS::GPS::start()
{
    if (_timer == NULL)
        SetTimer();
    _timer->Start();
}

void GPS::GPS::stop()
{
    _timer->Stop();
}

void GPS::GPS::pause()
{
    _timer->Pause();
}

void GPS::GPS::resume()
{
    _timer->Resume();
}

