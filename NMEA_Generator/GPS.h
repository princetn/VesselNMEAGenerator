/*******************************************************************************
GPS

PURPOSE: Create a GPS sensor to generate NMEA 183 messages.

CREATED: 2/17/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#pragma once
#include "NMEA.h"
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include "GPSCoordinates.h"
#include <math.h>
#include "Object.h"
#include "Timer.h"
#include <mutex>


#define PI acos(-1.0)



using namespace NMEA;

//namespace GPS { class GPSCoordinates; }
namespace GPS { class Date; }
namespace GPS { class Satellite; }
namespace GPS { class GPS; }


namespace GPS
{
    using Ptr_GPSCoordinates = std::shared_ptr<GPSCoordinates>;
    using WayPoint = std::vector<GPSCoordinates>;
    using Ptr_Satellite = std::shared_ptr<Satellite>;
    typedef std::shared_ptr<Date> Ptr_Date;
    typedef std::shared_ptr<Timer::Timer<GPS>> Ptr_Timer;




    class GPS :
        public NMEA, public Object
    {
        
    public:
        GPS();
        ~GPS();
        GPS(const GPS& gps);
        std::string NMEAMessage() override;
        enum GPSType{WAYPOINT,VECTOR}; // choose between waypoints or start-end pts.
        enum GP {GPGRMC,GPGGA,GPGSA,GPGLL}; // choose which NMEA stence to send out.
        void setGPSRate(float rate);
        void setSpeed(float speed);
        void setGPSType(GPSType t);
        void setWayPoint(WayPoint waypt);
        void setVector(Ptr_GPSCoordinates start, Ptr_GPSCoordinates end);
        char getUnits();
        void setUnits(char unit);
        float getMSL();
        void setMSL(float altitude);
        float getHDOP();
        void setHDOP(float v);
        void AddNMEAmessages();
        void start();
        void stop();
        void pause();
        void resume();
        




    private:
        //friend class Timer;
        std::string GRMC();
        std::string GGA();
        std::string GSA();
        std::string GLL();
        void SetTimer();
        void Init();

        void ComputeCurrentCoordinate();
        Ptr_GPSCoordinates CalculateCoordinateBetweenTwoPts(Ptr_GPSCoordinates start, Ptr_GPSCoordinates end);

        std::string MakeNMEASentence(std::string str);

        

        Ptr_GPSCoordinates _start; // starting point
        Ptr_GPSCoordinates _end;
        Ptr_GPSCoordinates _currentCoord;
        WayPoint _waypt;
        int _wayptIndex = 0;
        Ptr_Date _date;
        float _speed; // m/s
        //float _gpsRate; _refresh from NMEA base class.
        GPSType _gpsType;
        Ptr_Satellite _sat;
        std::queue<std::string>* _gpsNMEAbuf; // store the NMEA data to send over udp
        char _status = 'A';
        char _Units = 'M';
        float _MSLAltitude = 0.0f;
        float _PDOP = 1.8f;
        float _HDOP = 1.0f;
        float _VDOP = 1.5f;
        char _Mode1 ='A';
        char _Mode = 'A';
        unsigned int _Mode2 = 3;

        Ptr_Timer _timer = NULL;
        std::mutex* _queue_lock;

        
        
    protected:

    };



}

