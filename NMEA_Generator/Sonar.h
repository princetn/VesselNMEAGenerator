/*******************************************************************************
Sonar

PURPOSE: Provide water depth NMEA API. Create a water depth sensor to generate NMEA 183 messages.

CREATED: 4/26/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#pragma once
#include "NMEA.h"
#include <queue>
#include <mutex>
#include <string>
#include "Event.h"

using namespace NMEA;
namespace Sonar
{
    class Sonar :
        public NMEA
    {
    public:
        Sonar();
        Sonar(const Sonar& sn);
        ~Sonar();
        void setDepth(float v);
        float getDepth();
        
        void setOffset(float v);
        float getOffset();

        void setMaxRange(float v);
        float getMaxRange();

        void setRefreshRate(float f);
        float getRefreshRate();

        void LoadData();

        void AddNMEAmessages();
        std::string NMEAMessage() override;

        Event<Object>* event;


    private:
        void Init();
        std::string MakeNMEASentence(std::string str);
        std::string DPT();

        float _depth;
        float _offset;
        float _MaxRange = 10.0;


        std::mutex* _mtx;
        std::queue<std::string>* _NMEABuf;
    protected:

    };

}