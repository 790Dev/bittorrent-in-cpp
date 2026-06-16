#pragma once

#include <string>

#include "PeerInfo.h"

class PeerClient
{
public:

    static std::string connectAndHandshake(
        const PeerInfo& peer,
        const std::string& infoHash,
        const std::string& peerId
    );
};