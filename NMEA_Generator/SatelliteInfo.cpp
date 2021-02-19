#include "SatelliteInfo.h"

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
