/*******************************************************************************
NMEA

PURPOSE: Create a contract interface for all the NMEA sensors.

CREATED: 2/17/2021
AUTHOR:  Amir Gasmi <argasmi@gmail.com>
*******************************************************************************/

#include "NMEA.h"


int NMEA::NMEA::checksum(const char* s) {
    int c = 0;
    int counter = 0;
    while (*s)
    {
        counter++;
        c ^= *s++;

    }
  
        

    return c;
}