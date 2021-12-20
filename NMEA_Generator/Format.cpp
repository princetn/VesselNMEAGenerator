#include "Format.h"
#include <sstream>
#include <iomanip>





Formatter::Format::Format(unsigned int digits)
    :_digits(digits)
{
}

Formatter::Format::~Format()
{
}

std::string Formatter::Format::operator()(float v)
{
    std::ostringstream ss;
    ss << std::fixed;
    ss << std::setprecision(_digits);
    ss << v;


    return ss.str();
}
