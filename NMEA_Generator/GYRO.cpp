/*******************************************************************************
GYRO

PURPOSE: Provide GYRO sensor NMEA.

CREATED: 4/14/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#include "GYRO.h"
#include <sstream>
#include <cstring>
#include "Format.h"

using namespace Formatter;

GYRO::GYRO::GYRO()
{
    Init();
}

GYRO::GYRO::GYRO(const GYRO& gyro)
{
    _status = gyro._status;
    _source = gyro._source;
    _sel = gyro._sel;
    _mtx = gyro._mtx;
    _refresh = gyro._refresh;
    _true = gyro._true;
    _heading = gyro._heading;
    _roll = gyro._roll;
    _pitch = gyro._pitch;

    _NMEAbuf = gyro._NMEAbuf;
}

GYRO::GYRO::~GYRO()
{
}

std::string GYRO::GYRO::NMEAMessage()
{
    std::string str ="";
    
    bool isBuffEmpty = false;
    const int MaxIt = 2 * ceil(1 / _refresh) * 1000 / 100;
    int it = 0;
    while (!isBuffEmpty && it < MaxIt) // wait until buffer is filled.
    {
        std::lock_guard<std::mutex>(*_mtx); // lock buffer before we check so bizarre behavior!
        if (!_NMEAbuf->empty())
        {
            str = _NMEAbuf->front();
            _NMEAbuf->pop();
            isBuffEmpty = true;

        }
        else
        {
            
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // wait a little bit and try again.
    }

    return str;
}

void GYRO::GYRO::AddNMEAmessages()
{
    std::lock_guard<std::mutex>(*_mtx);
    /// <summary>
    /// HRP sentence
    /// </summary>
    std::string str = HRP();
    str = MakeNMEASentence(str);
    _NMEAbuf->push(str);

    /// <summary>
    /// HDT
    /// </summary>
    str = HDT();
    str = MakeNMEASentence(str);
    _NMEAbuf->push(str);
   if (event != NULL)
    {
        event->Invoke();
    }
}

float GYRO::GYRO::getHeading()
{
    return _heading;
}

void GYRO::GYRO::setHeading(float val)
{
    _heading = val;
}

void GYRO::GYRO::setRefreshRate(float val)
{
    _refresh = val;
}

int GYRO::GYRO::getMillisecPeriod()
{
    return (int)(1000/_refresh);
}

void GYRO::GYRO::setRoll(float val)
{
    _roll = val;
}

float GYRO::GYRO::getRoll()
{
    return _roll;
}

void GYRO::GYRO::setPitch(float val)
{
    _pitch = val;
}

float GYRO::GYRO::getPitch()
{
    return _pitch;
}

char GYRO::GYRO::getTrue()
{
    return _true;
}

void GYRO::GYRO::setSource(unsigned char val)
{
    _source = val;
}

unsigned char GYRO::GYRO::getSource()
{
    return _source;
}

char GYRO::GYRO::getSelection()
{
    return _sel;
}

void GYRO::GYRO::setSelection(char val)
{
    _sel = val;
}

char GYRO::GYRO::getStatus()
{
    return _status;
}

void GYRO::GYRO::setStatus(char val)
{
    _status = val;
}

void GYRO::GYRO::LoadGyroData()
{// here you would implement how to get the data from a text stream or a server connected to the ship simulator.

    setHeading(300.1);
    setRoll(11.1);
    setPitch(4.3);


}

std::string GYRO::GYRO::HDT()
{
    //std::string str = "";
    std::ostringstream ss;
    Format format1(1);

    ss << "HDT" << "," << format1(getHeading()) << "," << getTrue();

    return ss.str();
}

std::string GYRO::GYRO::HRP()
{
    std::ostringstream ss;
    Format format1(1);
    ss << "HRP" << "," << +getSource() << "," << format1(getHeading()) << "," << format1(getRoll())
        << "," << format1(getPitch()) << "," << format1(0.0) << "," << format1(0.0) << ","
        << format1(0.0) << "," << getStatus() << "," << getSelection();
    return ss.str();
}

void GYRO::GYRO::Init()
{
    _mtx = new std::mutex();
    _NMEAbuf = new std::queue<std::string>();
}

std::string GYRO::GYRO::MakeNMEASentence(std::string str)
{
    std::ostringstream ss;
    ss << "GY" << str;
    str = ss.str();
    unsigned int n = str.length();
    char* s = new char[n + (unsigned int)1];
    strcpy_s(s, (n + (unsigned int)1) * sizeof(char), str.c_str());
    ss << "*" << checksum(s) << "\r\n";

    str = "$" + ss.str();
    /*std::cout << s;
    std::cout << str;*/
    delete[] s;



    return str;
}
