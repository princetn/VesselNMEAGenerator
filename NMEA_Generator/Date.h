/*******************************************************************************
Date

PURPOSE: Provide actual date for GPS NMEA.

CREATED: 2/17/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#pragma once
#include<ctime>
#include<memory>
#include<string>

//namespace std { typedef basic_string<char> string; }

namespace GPS {
	typedef std::shared_ptr<tm> Ptr_tm;
	//typedef std::shared_ptr<std::string> Ptr_string;

	class Date
	{
	public:
		Date();
		~Date();
		
		std::string getstringDate();
		void setstringDate(std::string str);
		Ptr_tm getNumericDate();
		void setNumericDate();
		float getUTC_Time();
		void setUTC_Time(float t);
		float getNumDate();
		
		//TODO: set a date in gps nmea format: numerical value for date.


	private:
		void Init();
		void UpdateDateGM();
		void UpdateDateLocal();

		Ptr_tm _structDate;
		std::string _stringDate;
		float _UTC_time;



	};
}

