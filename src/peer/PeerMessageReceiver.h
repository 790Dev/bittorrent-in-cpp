#pragma once

#include "PeerMessage.h"

class PeerMessageReceiver
{
public:

    static PeerMessage receive(
        int socketFd
    );
};