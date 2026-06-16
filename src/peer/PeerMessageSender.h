#pragma once

class PeerMessageSender
{
public:

    static void sendRequest(
        int pieceIndex,
        int begin,
        int length
    );
};
