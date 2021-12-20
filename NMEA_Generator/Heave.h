/*******************************************************************************
Heave

PURPOSE: Provide Heave sensor NMEA.

CREATED: 4/23/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#pragma once
#include "NMEA.h"
#include <queue>
#include <mutex>
#include <string>
#include <memory>
#include "Date.h"
#include "Event.h"


using namespace NMEA;

namespace Heave
{
    typedef std::shared_ptr<GPS::Date> ptr_Date;
    

    class Heave :
        public NMEA
    {
    public:
        Heave();
        Heave(const Heave& hv);
        ~Heave();

        void AddNMEAmessages();
        std::string NMEAMessage() override;
        void LoadHeaveData();

        Event<Object>* event = NULL;

        void setHeading(float v);
        float getHeading();
        
        void setHFlag(char v);
        char getHFlag();
        
        void setRoll(float v);
        float getRoll();
        
        void setPitch(float v);
        float getPitch();

        void setHeave(float v);
        float getHeave();
        
        void setRollAcc(float v);
        float getRollAcc();
        
        void setPitchAcc(float v);
        float getPitchAcc();
        
        void setHeadingAcc(float v);
        float getHeadingAcc();

        void setAidingStatus(unsigned char v);
        unsigned char getAidingStatus();

        void setIMUStatus(unsigned char v);
        unsigned char getIMUStatus();

        void setRefreshRate(float f);
        float getRefreshRate();

        


    private:
        void Init();

        std::string SHR();
        std::string MakeNMEASentence(std::string str);




        ptr_Date _date;

        float _heading;
        
        char _hflag = 'T';

        float _roll;

        float _pitch;

        float _heave;

        float _rollacc;

        float _pitchacc;

        float _headingacc;

        unsigned char _aidingStatus = 1;
        unsigned char _IMUstatus = 0;













        std::mutex* _mtx;
        std::queue<std::string>* _NMEAbuf;

    protected:

    };
}

