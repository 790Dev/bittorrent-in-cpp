#pragma once

#include <string>

class PeerHandshake
{
public:

    static std::string build(
        const std::string& infoHash,
        const std::string& peerId
    );

    static bool validate(
        const std::string& response,
        const std::string& expectedInfoHash
    );
};