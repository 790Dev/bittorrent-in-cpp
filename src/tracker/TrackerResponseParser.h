#pragma once

#include <string>
#include <vector>

struct Peer
{
    std::string ip;
    int port;
    std::string peerId;
};

struct TrackerResponse
{
    int complete = 0;
    int incomplete = 0;
    int interval = 0;

    std::vector<Peer> peers;
};

class TrackerResponseParser
{
public:

    static TrackerResponse parse(
        const std::string& responseBody
    );

    static void print(
        const TrackerResponse& response
    );
};