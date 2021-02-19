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
		void setstringDate();
		Ptr_tm getNumericDate();
		void setNumericDate();
		float getUTC_Time();
		void setUTC_Time(float t);



	private:
		Ptr_tm _numericDate;
		std::string _stringDate;
		float _UTC_time;


	};
}

