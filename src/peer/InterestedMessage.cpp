#include "InterestedMessage.h"

std::string InterestedMessage::build()
{
    std::string msg;

    msg.push_back(0);
    msg.push_back(0);
    msg.push_back(0);
    msg.push_back(1);

    msg.push_back(2);

    return msg;
}