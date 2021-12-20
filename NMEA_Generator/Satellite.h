/*******************************************************************************
Satellite

PURPOSE: Provide GPS satellite.

CREATED: 2/19/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#pragma once
#include<memory>
#include<vector>
#include "SatelliteInfo.h"

namespace GPS
{
	//class SatelliteInfo;
	typedef std::shared_ptr<SatelliteInfo> Ptr_SatInfo;
	typedef std::vector<SatelliteInfo> SatInfoVec;

	class Satellite
	{
	public:
		Satellite();
		~Satellite();

		void setSatinfo(SatInfoVec satinfoVec);
		SatInfoVec getSatInfo();
		void setSateInView(int satInView);
		int getSatInView();
		int getPositionFix();
		void setPositionfix(int p);
		unsigned int getSatNum();
		void setSatNum(unsigned int val);

		

	private:
		void Init();
		unsigned int _num_sat = 12;
		SatInfoVec _satInfo;
		int _sateInView;
		int _positionFix;

	protected:

	};
}
