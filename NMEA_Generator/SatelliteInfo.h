#pragma once
namespace GPS
{
	class SatelliteInfo
	{
	public:
		void setSatID(int satId);
		int getSatID();
		void setElevation(int el);
		int getElevation();
		void setAzimuth(int az);
		int getAzimuth();
		void setSNR(int snr);
		int getSNR();

	private:
		int _satID;
		int _el; // 0-90
		int _az; //0-359
		int _SNR; // dBHz 0-99

	protected:

	};
}
