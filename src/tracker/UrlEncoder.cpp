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
        if(
            (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= '0' && c <= '9')
        )
        {
            ss << c;
        }
        else
        {
            ss
                << '%'
                << std::uppercase
                << std::hex
                << std::setw(2)
                << std::setfill('0')
                << static_cast<int>(c);
        }
    }

    return ss.str();
}