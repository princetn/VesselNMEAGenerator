/*******************************************************************************
SatelliteInfo

PURPOSE: Provide GPS satellite info.

CREATED: 2/22/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#include "SatelliteInfo.h"
#include <cstdlib>
#include<ctime>

GPS::SatelliteInfo::SatelliteInfo()
{
	Init();
}

GPS::SatelliteInfo::~SatelliteInfo()
{
}

void GPS::SatelliteInfo::setSatID(int satId)
{
	_satID = satId;
}

int GPS::SatelliteInfo::getSatID()
{
	return _satID;
}

void GPS::SatelliteInfo::setElevation(int el)
{
	_el = el;
}

int GPS::SatelliteInfo::getElevation()
{
	return _el;
}

void GPS::SatelliteInfo::setAzimuth(int az)
{
	_az = az;
}

int GPS::SatelliteInfo::getAzimuth()
{
	return _az;
}

void GPS::SatelliteInfo::setSNR(int snr)
{
	_SNR = snr;
}

int GPS::SatelliteInfo::getSNR()
{
	return _SNR;
}

void GPS::SatelliteInfo::Init()
{
	time_t nTime;
	//srand((unsigned)time(&nTime));

	setAzimuth(rand()%359);
	
	setElevation(rand()%90);
	
	setSatID(rand()%17+1);
	
	setSNR(rand()%99);
}
