#include "NMEA.h"


int NMEA::NMEA::checksum(const char* s) {
    int c = 0;

    while (*s)
        c ^= *s++;

    return c;
}