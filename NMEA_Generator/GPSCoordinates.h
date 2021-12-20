/*******************************************************************************
Date

PURPOSE: Provide actual GPS coordinate info for GPS NMEA.

CREATED: 2/18/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#pragma once

namespace GPS
{
	class GPSCoordinates
	{
	public:
		enum EWHeading { E, W };
		enum NSHeading { N, S };
		GPSCoordinates();
		GPSCoordinates(float lat, float lon,EWHeading ew,NSHeading ns,float sog, float cog);
		~GPSCoordinates();


		float getLat();
		void setLat(float lat);
		float getLong();
		void setLong(float lon);
		EWHeading getEWHeading();
		void setEWHeading(EWHeading ew);
		NSHeading getNSHeading();
		void setNSHeading(NSHeading ns);
		float getSpeedOverGround();
		float getCourseOverGround();
		float getNSsign();
		float getEWsign();
		char getEWChar();
		char getNSChar();


	private:
		void Init();
		float _lat;
		float _lon;
		EWHeading _EW;
		NSHeading _NS;
		float _speedOverGround;
		float _courseOverGround;

	protected:


	};

}
