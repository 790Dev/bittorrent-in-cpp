#include "PeerMessage.h"

#include <iostream>

PeerMessage PeerMessageParser::parse(
    const std::string& data
)
{
    PeerMessage msg;

    if(data.size() < 4)
    {
        return msg;
    }

    msg.length =
        ((unsigned char)data[0] << 24) |
        ((unsigned char)data[1] << 16) |
        ((unsigned char)data[2] << 8)  |
        ((unsigned char)data[3]);

    if(msg.length == 0)
    {
        msg.id = 255;
        return msg;
    }

    msg.id =
        (unsigned char)data[4];

    for(
        size_t i = 5;
        i < data.size();
        i++
    )
    {
        msg.payload.push_back(
            data[i]
        );
    }

    return msg;
}

void PeerMessageParser::print(
    const PeerMessage& msg
)
{
    std::cout
        << "\n===== PEER MESSAGE =====\n";

    std::cout
        << "Length : "
        << msg.length
        << '\n';

    if(msg.length == 0)
    {
        std::cout
            << "Type   : KEEP-ALIVE\n";
    }
    else
    {
        std::cout
            << "ID     : "
            << (int)msg.id
            << '\n';

        switch(msg.id)
        {
            case 0:
                std::cout
                    << "Type   : CHOKE\n";
                break;

            case 1:
                std::cout
                    << "Type   : UNCHOKE\n";
                break;

            case 2:
                std::cout
                    << "Type   : INTERESTED\n";
                break;

            case 3:
                std::cout
                    << "Type   : NOT INTERESTED\n";
                break;

            case 4:
                std::cout
                    << "Type   : HAVE\n";
                break;

            case 5:
                std::cout
                    << "Type   : BITFIELD\n";
                break;

            case 6:
                std::cout
                    << "Type   : REQUEST\n";
                break;

            case 7:
                std::cout
                    << "Type   : PIECE\n";
                break;

            default:
                std::cout
                    << "Type   : UNKNOWN\n";
        }
    }

    std::cout
        << "Payload Bytes : "
        << msg.payload.size()
        << '\n';
}