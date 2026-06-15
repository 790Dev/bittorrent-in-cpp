#pragma once

#include <string>

struct TrackerInfo
{
    std::string host;
    int port;
    std::string path;

    bool isHttps = false;
};

class TrackerClient
{
public:

    static TrackerInfo parseUrl(
        const std::string& url
    );

    static void printInfo(
        const TrackerInfo& info
    );
};