#pragma once

#include <string>

class UrlEncoder
{
public:

    static std::string encode(
        const std::string& value
    );
};