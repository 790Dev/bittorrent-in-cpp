#include "PieceRequester.h"

#include "RequestMessage.h"
#include "PeerSession.h"

#include <winsock2.h>

void PieceRequester::sendRequest(
    int pieceIndex,
    int begin,
    int length
)
{
    std::string msg =
        RequestMessage::build(
            pieceIndex,
            begin,
            length
        );

    send(
        (SOCKET)PeerSession::getSocket(),
        msg.data(),
        (int)msg.size(),
        0
    );
}
