/*******************************************************************************
GYRO

PURPOSE: Provide GYRO sensor NMEA.

CREATED: 4/13/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#pragma once
#include "NMEA.h"
#include <queue>
#include <mutex>
#include <string>
#include "Event.h"
#include "Object.h"

using namespace NMEA;
namespace GYRO
{
    class GYRO :
        public NMEA
    {
    public:
        GYRO();
        GYRO(const GYRO& gyro);
        ~GYRO();
        std::string NMEAMessage() override;
        void AddNMEAmessages();
        Event<Object>* event = NULL;
        float getHeading();
        void setHeading(float val);
        void setRefreshRate(float val);
        int getMillisecPeriod();
        void setRoll(float val);
        float getRoll();
        void setPitch(float val);
        float getPitch();
        char getTrue();
        void setSource(unsigned char val);
        unsigned char getSource();
        char getSelection();
        void setSelection(char val);
        char getStatus();
        void setStatus(char val);
        // here where the hooking to the ship will happen.
        void LoadGyroData();


    private:
        std::string HDT();
        std::string HRP();
        void Init();

        std::string MakeNMEASentence(std::string str);


        // https://www.manualslib.com/manual/896665/Raytheon-Std-21-Gps.html?page=103
        // link for HRP (Heading Roll Pitch) sentence
        float _heading; // 0-360, positive clockwise, true north = 0
        float _roll; // +/- 90, positive for starboard down
        float _pitch; // +- 90, positive for bow up

        unsigned char _source = 1; // 1 = single MINS, 2 = MINS2
        char _true = 'T';

        char _status = 'A';
        char _sel = 'A'; //Selection: A= sentence selected in the system
                        // V = redundant sentence


        std::queue<std::string>* _NMEAbuf; // store the NMEA data to send over udp

        std::mutex* _mtx;


    protected:

    };


}
