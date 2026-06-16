#include "PeerHandshake.h"

#include <cstring>

std::string PeerHandshake::build(
    const std::string& infoHash,
    const std::string& peerId
)
{
    std::string handshake;

    handshake.push_back(19);

    handshake += "BitTorrent protocol";

    handshake.append(
        8,
        '\0'
    );

    handshake += infoHash;

    handshake += peerId;

    return handshake;
}

bool PeerHandshake::validate(
    const std::string& response,
    const std::string& expectedInfoHash
)
{
    if(response.size() < 68)
    {
        return false;
    }

    std::string receivedHash =
        response.substr(
            28,
            20
        );

    return receivedHash ==
           expectedInfoHash;
}