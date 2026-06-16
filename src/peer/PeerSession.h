#pragma once

#include <string>

#include "PeerInfo.h"

class PeerSession
{
public:

    static bool connectToPeer(
        const PeerInfo& peer
    );

    static bool sendHandshake(
        const PeerInfo& peer,
        const std::string& infoHash,
        const std::string& peerId
    );

    static std::string receiveBytes(
        int count
    );

    static int getSocket();

    static void disconnect();

private:

    static int socketFd;
};