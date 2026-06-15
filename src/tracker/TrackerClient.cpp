#include "TrackerClient.h"

#include <iostream>
#include <stdexcept>

TrackerInfo TrackerClient::parseUrl(
    const std::string& url
)
{
    TrackerInfo info;

    std::string workingUrl = url;

    const std::string httpPrefix = "http://";

    if(
        workingUrl.find(httpPrefix) == 0
    )
    {
        workingUrl =
            workingUrl.substr(
                httpPrefix.size()
            );
    }

    size_t slashPos =
        workingUrl.find('/');

    std::string hostPort;

    if(slashPos == std::string::npos)
    {
        hostPort = workingUrl;
        info.path = "/";
    }
    else
    {
        hostPort =
            workingUrl.substr(
                0,
                slashPos
            );

        info.path =
            workingUrl.substr(
                slashPos
            );
    }

    size_t colonPos =
        hostPort.find(':');

    if(colonPos == std::string::npos)
    {
        info.host = hostPort;
        info.port = 80;
    }
    else
    {
        info.host =
            hostPort.substr(
                0,
                colonPos
            );

        info.port =
            std::stoi(
                hostPort.substr(
                    colonPos + 1
                )
            );
    }

    return info;
}

void TrackerClient::printInfo(
    const TrackerInfo& info
)
{
    std::cout
        << "\n===== TRACKER INFO =====\n";

    std::cout
        << "Host : "
        << info.host
        << '\n';

    std::cout
        << "Port : "
        << info.port
        << '\n';

    std::cout
        << "Path : "
        << info.path
        << '\n';
}