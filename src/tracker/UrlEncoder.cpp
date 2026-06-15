#include "UrlEncoder.h"

#include <sstream>
#include <iomanip>

std::string UrlEncoder::encode(
    const std::string& value
)
{
    std::stringstream ss;

    for(unsigned char c : value)
    {
        ss
            << '%'
            << std::uppercase
            << std::hex
            << std::setw(2)
            << std::setfill('0')
            << (int)c;
    }

    return ss.str();
}