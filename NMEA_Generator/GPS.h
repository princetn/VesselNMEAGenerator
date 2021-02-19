/*******************************************************************************
GPS

PURPOSE: Create a GPS sensor to generate NMEA 183 messages.

CREATED: 2/17/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#pragma once
#include "NMEA.h"
#include <memory>
#include<vector>
#include<string>
#include<queue>

using namespace NMEA;

namespace GPS { class GPSCoordinates; }
namespace GPS { class Date; }
namespace GPS { class Satellite; }



namespace GPS
{
    using Ptr_GPSCoordinates = std::shared_ptr<GPSCoordinates>;
    using WayPoint = std::vector<GPSCoordinates>;
    using Ptr_Satellite = std::shared_ptr<Satellite>;
    typedef std::shared_ptr<Date> Ptr_Date;




    class GPS :
        public NMEA
    {
        
    public:
        GPS();
        ~GPS();
        std::string NMEAMessage() override;
        enum GPSType{WAYPOINT,VECTOR}; // choose between waypoints or start-end pts.
        enum GP {GPGRMC,GPGGA,GPGSA,GPGLL}; // choose which NMEA stence to send out.
        void setGPSRate(float rate);
        void setSpeed(float speed);



    private:
        std::string GRMC();
        std::string GGA();
        std::string GSA();
        std::string GLL();

        Ptr_GPSCoordinates _start; // starting point
        Ptr_GPSCoordinates _end;
        WayPoint _waypt;
        Ptr_Date _date;
        float _speed; // m/s
        //float _gpsRate; _refresh from NMEA base class.
        GPSType _gpsType;
        Ptr_Satellite _Sat;
        std::queue<std::string> _gpsNMEAbuf; // store the NMEA data to send over udp
        
        
    protected:

    };
}

