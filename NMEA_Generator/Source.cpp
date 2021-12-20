/*******************************************************************************
Main

PURPOSE: Provide testing for the NMEA vessel simulator test.

CREATED: 2/17/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/
#include "Date.h"
#include<iostream>
#include <stdexcept>
#include <thread>
#include "GPS.h"
#include "GYRO.h"
#include "Heave.h"
#include "Sonar.h"
#include "UdpServer.h"

#pragma optimize( "", off )

int main(int argc, char* argv[])
{
	
	// Testing Date class:
	GPS::Date date;
	auto date1 = GPS::Date();
	

	std::cout << date.getstringDate() << std::endl;
	auto t = date.getNumericDate();
	std::cout << "Day:  " << t->tm_mday << " Month: " << t->tm_mon << " year: " << t->tm_year  << std::endl;
	std::cout << "date: " << date.getNumDate() << std::endl;
	std::cout << "UTC: " << date.getUTC_Time() << std::endl;
	
	
	// UDP server:
	UDP::UdpServer NmeaServ;

	NmeaServ.Connect("127.0.0.1", 10245);
	
	// Testing NMEA sensors
	GPS::GPS gps;
	GYRO::GYRO gyro;
	Heave::Heave heave;
	Sonar::Sonar sr;


	// GPS Init.
	gps.setGPSType(GPS::GPS::GPSType::VECTOR);
	GPS::Ptr_GPSCoordinates start,end;
	start = std::make_shared<GPS::GPSCoordinates>(GPS::GPSCoordinates(41.092489, 73.524062,GPS::GPSCoordinates::EWHeading::W, GPS::GPSCoordinates::NSHeading::N,10,110));
	end = std::make_shared<GPS::GPSCoordinates>(GPS::GPSCoordinates(42.092489, 73.524062, GPS::GPSCoordinates::EWHeading::W, GPS::GPSCoordinates::NSHeading::N, 0, 110));
	gps.setVector(start, end);
	gps.setGPSRate(1.0f);
	gps.setSpeed(10);

	//GYRO Init.
	gyro.setRefreshRate(1.0f);
	gyro.LoadGyroData();

	//Heave Init.
	heave.setRefreshRate(5.0f);
	heave.LoadHeaveData();

	//Sonar Init.
	sr.setRefreshRate(1.0f);
	sr.LoadData();


	



	try {
		Timer::Timer<GPS::GPS> timer(gps, &GPS::GPS::AddNMEAmessages, 1000);
		Timer::Timer<GYRO::GYRO> timer2(gyro, &GYRO::GYRO::AddNMEAmessages, 1000);
		Timer::Timer<Heave::Heave> timer3(heave, &Heave::Heave::AddNMEAmessages, 1000);
		Timer::Timer<Sonar::Sonar> timer4(sr, &Sonar::Sonar::AddNMEAmessages, 1000);

		//spwaning 4 timer daemon threads for generating 4 sensor signals.
		timer.Start();
		timer2.Start();
		timer3.Start();
		timer4.Start();


		clock_t begin = clock();
		bool paused = false;
		while (true)
		{
			// gyro sig:
			auto str = gyro.NMEAMessage();
			std::cout << str << std::endl;
			NmeaServ.Send(str);
			//heave sig:
			str = heave.NMEAMessage();
			std::cout << str << std::endl;
			NmeaServ.Send(str);
			str = sr.NMEAMessage();
			std::cout << str << std::endl;
			NmeaServ.Send(str);


			if (!paused)
			{

				auto str = gps.NMEAMessage();
				std::cout << str << std::endl;
				NmeaServ.Send(str);
			}
			if ((clock() - begin) / CLOCKS_PER_SEC > 10 && !paused) // pause the daemon gps thread.
			{
				
				paused = true;
				timer.Pause();
			
				begin = clock();


			}
			else if ((clock() - begin) / CLOCKS_PER_SEC > 10 && paused)
			{
				begin = clock();
				paused = false;
				timer.Resume();

			}

		}
	}
	catch (std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}







	return 0;
}