#pragma once

#include <string>
#include <unordered_map>

class HttpResponse
{
public:

    int statusCode = 0;

    std::unordered_map<std::string,std::string> headers;

    std::string body;

    static HttpResponse parse(
        const std::string& rawResponse
    );

    void print() const;
};