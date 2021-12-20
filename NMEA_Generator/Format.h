#pragma once
#include <string>

namespace Formatter
{
    class Format
    {
    public:
        Format(unsigned int digits = 6);
        ~Format();
        std::string operator() (float v);


    private:
        unsigned int _digits;

    };

}