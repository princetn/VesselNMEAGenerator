/*******************************************************************************
NMEA

PURPOSE: Create a contract interface for all the NMEA sensors.

CREATED: 2/17/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/


#pragma once

#include<string>

namespace NMEA
{

	class NMEA
	{
	public:
		virtual std::string NMEAMessage() = 0;
		const int NMEA_MAX_SIZE = 80; // maximum sentence length.

	private:

	protected:
		int checksum(const char* s);
		float _refresh; // frequency in Hz.


	};
}

