#include "HttpResponse.h"

#include <iostream>
#include <sstream>

HttpResponse HttpResponse::parse(
    const std::string& rawResponse
)
{
    HttpResponse response;

    std::istringstream stream(rawResponse);

    std::string line;

    // Status Line
    if(std::getline(stream,line))
    {
        std::stringstream statusStream(line);

        std::string httpVersion;

        statusStream
            >> httpVersion
            >> response.statusCode;
    }

    // Headers
    while(std::getline(stream,line))
    {
        if(line == "\r" || line.empty())
        {
            break;
        }

        size_t colon =
            line.find(':');

        if(colon == std::string::npos)
        {
            continue;
        }

        std::string key =
            line.substr(
                0,
                colon
            );

        std::string value =
            line.substr(
                colon + 1
            );

        if(!value.empty() &&
           value.front() == ' ')
        {
            value.erase(
                value.begin()
            );
        }

        if(!value.empty() &&
           value.back() == '\r')
        {
            value.pop_back();
        }

        response.headers[key] =
            value;
    }

    // Body
    std::string bodyLine;

    while(std::getline(stream,bodyLine))
    {
        response.body += bodyLine;
        response.body += '\n';
    }

    return response;
}

void HttpResponse::print() const
{
    std::cout
        << "\n===== HTTP RESPONSE =====\n";

    std::cout
        << "Status Code : "
        << statusCode
        << "\n\n";

    std::cout
        << "Headers:\n";

    for(const auto& header : headers)
    {
        std::cout
            << header.first
            << " : "
            << header.second
            << '\n';
    }

    std::cout
        << "\nBody:\n"
        << body
        << '\n';
}