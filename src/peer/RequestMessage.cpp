#include "RequestMessage.h"

static void appendInt(
    std::string& data,
    int value
)
{
    data.push_back((value >> 24) & 0xFF);
    data.push_back((value >> 16) & 0xFF);
    data.push_back((value >> 8) & 0xFF);
    data.push_back(value & 0xFF);
}

std::string RequestMessage::build(
    int pieceIndex,
    int begin,
    int length
)
{
    std::string msg;

    appendInt(msg, 13);

    msg.push_back(6);

    appendInt(msg, pieceIndex);
    appendInt(msg, begin);
    appendInt(msg, length);

    return msg;
}