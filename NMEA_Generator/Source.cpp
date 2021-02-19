#include "GPS.h"
#include "Date.h"
#include<iostream>


int main(int argc, char* argv[])
{
	GPS::Date date;
	auto date1 = GPS::Date();

	std::cout << date.getstringDate() << std::endl;
	auto t = date.getNumericDate();
	std::cout << t->tm_year<< ", "<<t->tm_year<<std::endl;
	

	return 0;
	
	

	
	

}