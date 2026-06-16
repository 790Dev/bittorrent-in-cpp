#pragma once

#include <string>
#include <vector>

struct PeerMessage
{
    int length = 0;

    unsigned char id = 255;

    std::vector<char> payload;
};

class PeerMessageParser
{
public:

    static PeerMessage parse(
        const std::string& data
    );

    static void print(
        const PeerMessage& msg
    );
};