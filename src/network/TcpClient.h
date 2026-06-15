#pragma once

#include <string>

class TcpClient
{
public:

    static std::string sendRequest(
        const std::string& host,
        int port,
        const std::string& request
    );
};