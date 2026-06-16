#pragma once

class PieceRequester
{
public:

    static void sendRequest(
        int pieceIndex,
        int begin,
        int length
    );
};
