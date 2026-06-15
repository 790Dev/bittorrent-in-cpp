#pragma once

#include <string>

class HttpsClient
{
public:

    static std::string sendRequest(
        const std::string& host,
        int port,
        const std::string& request
    );
};