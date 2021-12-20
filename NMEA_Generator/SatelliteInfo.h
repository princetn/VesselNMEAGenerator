/*******************************************************************************
SatelliteInfo

PURPOSE: Provide GPS satellite info.

CREATED: 2/19/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#pragma once
namespace GPS
{
	class SatelliteInfo
	{
	public:
		SatelliteInfo();
		~SatelliteInfo();
		void setSatID(int satId);
		int getSatID();
		void setElevation(int el);
		int getElevation();
		void setAzimuth(int az);
		int getAzimuth();
		void setSNR(int snr);
		int getSNR();

	private:
		void Init();
		int _satID;
		int _el; // 0-90
		int _az; //0-359
		int _SNR; // dBHz 0-99

	protected:

	};
}
