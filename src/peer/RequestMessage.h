#pragma once

#include <string>

class RequestMessage
{
public:

    static std::string build(
        int pieceIndex,
        int begin,
        int length
    );
};