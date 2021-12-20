/*******************************************************************************
Satellite

PURPOSE: Provide GPS satellite.

CREATED: 2/22/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#include "Satellite.h"

GPS::Satellite::Satellite()
{
	Init();
}

GPS::Satellite::~Satellite()
{
}

void GPS::Satellite::setSatinfo(SatInfoVec satinfoVec)
{
}

GPS::SatInfoVec GPS::Satellite::getSatInfo()
{
	

	return _satInfo;
}

void GPS::Satellite::setSateInView(int satInView)
{
}

int GPS::Satellite::getSatInView()
{
	return 0;
}

int GPS::Satellite::getPositionFix()
{
	return _positionFix;
}

void GPS::Satellite::setPositionfix(int p)
{
	_positionFix = p;
}

unsigned int GPS::Satellite::getSatNum()
{
	return _num_sat;
}

void GPS::Satellite::setSatNum(unsigned int val)
{
	_num_sat = val;
}

void GPS::Satellite::Init()
{
	setPositionfix(1);
	for (int i = 0; i < _num_sat; i++)
	{
		_satInfo.push_back(SatelliteInfo());
	}
	
}
