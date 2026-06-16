#include "PieceDownloader.h"

#include "PeerMessageSender.h"
#include "PeerMessageReceiver.h"
#include "PeerSession.h"

std::vector<char>
PieceDownloader::downloadPiece(
    int pieceIndex,
    int pieceLength
)
{
    std::vector<char> pieceData;

    const int BLOCK_SIZE = 16384;

    for(
        int offset = 0;
        offset < pieceLength;
        offset += BLOCK_SIZE
    )
    {
        int requestLength =
            std::min(
                BLOCK_SIZE,
                pieceLength - offset
            );

        PeerMessageSender::sendRequest(
            pieceIndex,
            offset,
            requestLength
        );

        PeerMessage msg =
            PeerMessageReceiver::receive(
                PeerSession::getSocket()
            );

        if(msg.id != 7)
        {
            continue;
        }

        pieceData.insert(
            pieceData.end(),
            msg.payload.begin() + 8,
            msg.payload.end()
        );
    }

    return pieceData;
}