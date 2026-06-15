#include "PeerIdGenerator.h"

#include <random>
#include <string>

std::string PeerIdGenerator::generate()
{
    std::string peerId = "-CPP01-";

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(
        0,
        9
    );

    while(peerId.size() < 20)
    {
        peerId +=
            std::to_string(
                dist(gen)
            );
    }

    return peerId;
}   