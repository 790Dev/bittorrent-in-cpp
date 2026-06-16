#pragma once

#include <vector>
#include <string>

class BitfieldParser
{
public:

    static std::vector<bool> parse(
        const std::string& payload
    );

    static void print(
        const std::vector<bool>& bitfield
    );
};