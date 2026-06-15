#pragma once

#include <string>
#include <vector>

struct Peer
{
    std::string ip;
    int port;
};

class TrackerResponse
{
public:

    long long interval = 0;

    std::vector<Peer> peers;

    static TrackerResponse parse(
        const std::string& response
    );

    void print() const;
};