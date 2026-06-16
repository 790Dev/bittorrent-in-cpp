#include "PeerMessageSender.h"

#include "RequestMessage.h"
#include "PeerSession.h"

#include <winsock2.h>

void PeerMessageSender::sendRequest(
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
