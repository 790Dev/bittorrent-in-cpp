#include "BitfieldParser.h"

#include <iostream>

std::vector<bool> BitfieldParser::parse(
    const std::string& payload
)
{
    std::vector<bool> pieces;

    for(unsigned char byte : payload)
    {
        for(int bit = 7; bit >= 0; --bit)
        {
            pieces.push_back(
                (byte >> bit) & 1
            );
        }
    }

    return pieces;
}

void BitfieldParser::print(
    const std::vector<bool>& bitfield
)
{
    std::cout
        << "\n===== BITFIELD =====\n";

    int count = 0;

    for(bool hasPiece : bitfield)
    {
        if(hasPiece)
        {
            count++;
        }
    }

    std::cout
        << "Available Pieces : "
        << count
        << '\n';

    std::cout
        << "Total Bits       : "
        << bitfield.size()
        << '\n';
}