/*******************************************************************************
Heave

PURPOSE: Provide Heave sensor NMEA.

CREATED: 4/23/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#include "Heave.h"
#include <sstream>
#include "Format.h"
#include <cmath>

using namespace Formatter;

Heave::Heave::Heave()
{
    Init();
}

Heave::Heave::Heave(const Heave& hv)
{
    _NMEAbuf = hv._NMEAbuf;
    _mtx = hv._mtx;

    _date = hv._date;

    _heading = hv._heading;

    _hflag = hv._hflag;

    _roll = hv._roll;

    _pitch = hv._pitch;

    _heave = hv._heave;

    _rollacc = hv._rollacc;

    _pitchacc = hv._pitchacc;

    _headingacc = hv._headingacc;

    _aidingStatus = hv._aidingStatus;
    _IMUstatus = hv._IMUstatus;
}

Heave::Heave::~Heave()
{
}

void Heave::Heave::AddNMEAmessages()
{
    std::lock_guard<std::mutex>(*_mtx);
    /// <summary>
    /// SHR sentence
    /// </summary>
    std::string str = SHR();
    str = MakeNMEASentence(str);
    _NMEAbuf->push(str);
    if (event != NULL)
    {
        event->Invoke();
    }
}

std::string Heave::Heave::NMEAMessage()
{
    std::string str = "";

    bool isBuffEmpty = false;
    const int MaxIt = 2 * ceil(1/_refresh) * 1000 / 100;
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

void Heave::Heave::LoadHeaveData()
{// here you would implement how to get the data from a text stream or a server connected to the ship simulator.

    setHeading(300.0);
    setRoll(3.123);
    setPitch(0.34);

    setHeadingAcc(0.03);
    setRollAcc(0.01);
    setPitchAcc(0.02);

    setHeave(3.13);


}

void Heave::Heave::setHeading(float v)
{
    _heading = v;
}

float Heave::Heave::getHeading()
{
    return _heading;
}

void Heave::Heave::setHFlag(char v)
{
    _hflag = v;
}

char Heave::Heave::getHFlag()
{
    return _hflag;
}

void Heave::Heave::setRoll(float v)
{
    _roll = v;
}

float Heave::Heave::getRoll()
{
    return _roll;
}

void Heave::Heave::setPitch(float v)
{
    _pitch = v;
}

float Heave::Heave::getPitch()
{
    return _pitch;
}

void Heave::Heave::setHeave(float v)
{
    _heave = v;
}

float Heave::Heave::getHeave()
{
    return _heave;
}

void Heave::Heave::setRollAcc(float v)
{
    _rollacc = v;
}

float Heave::Heave::getRollAcc()
{
    return _rollacc;
}

void Heave::Heave::setPitchAcc(float v)
{
    _pitchacc = v;
}

float Heave::Heave::getPitchAcc()
{
    return _pitchacc;
}

void Heave::Heave::setHeadingAcc(float v)
{
    _headingacc = v;
}

float Heave::Heave::getHeadingAcc()
{
    return _headingacc;
}

void Heave::Heave::setAidingStatus(unsigned char v)
{
    _aidingStatus = v;
}

unsigned char Heave::Heave::getAidingStatus()
{
    return _aidingStatus;
}

void Heave::Heave::setIMUStatus(unsigned char v)
{
    _IMUstatus = v;
}

unsigned char Heave::Heave::getIMUStatus()
{
    return _IMUstatus;
}

void Heave::Heave::setRefreshRate(float f)
{
    _refresh = f;
}

float Heave::Heave::getRefreshRate()
{
    return _refresh;
}

void Heave::Heave::Init()
{
    _mtx = new std::mutex();
    _NMEAbuf = new std::queue<std::string>();
    _date = std::make_shared<GPS::Date>(GPS::Date());

}

std::string Heave::Heave::SHR()
{
    std::ostringstream ss;
    Format format2(2);
    Format format3(3);
    const std::string delemiter = ",";
    ss << "SHR" << delemiter << _date->getUTC_Time() << delemiter << format2(getHeading()) << delemiter << getHFlag()
        << delemiter << format2(getRoll()) << delemiter << format2(getPitch()) << delemiter << format2(getHeave()) << delemiter <<
        format3(getRollAcc()) << delemiter << format3(getPitchAcc()) << delemiter << format3(getHeadingAcc()) << delemiter << +getAidingStatus()
        << delemiter << +getIMUStatus();

    return ss.str();
}

std::string Heave::Heave::MakeNMEASentence(std::string str)
{
    std::ostringstream ss;
    ss << "PA" << str;
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
