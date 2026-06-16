#include "PeerMessageReceiver.h"

#include <winsock2.h>

PeerMessage PeerMessageReceiver::receive(
    int socketFd
)
{
    PeerMessage msg;

    char lengthBuffer[4];

    int received =
        recv(
            (SOCKET)socketFd,
            lengthBuffer,
            4,
            MSG_WAITALL
        );

    if(received != 4)
    {
        return msg;
    }

    msg.length =
        ((unsigned char)lengthBuffer[0] << 24) |
        ((unsigned char)lengthBuffer[1] << 16) |
        ((unsigned char)lengthBuffer[2] << 8)  |
        ((unsigned char)lengthBuffer[3]);

    if(msg.length == 0)
    {   
        msg.id = -1;
        return msg;
    }

    char idBuffer;

    received =
        recv(
            (SOCKET)socketFd,
            &idBuffer,
            1,
            MSG_WAITALL
        );

    if(received != 1)
    {
        return msg;
    }

    msg.id =
        (unsigned char)idBuffer;

    int payloadLength =
        msg.length - 1;

    if(payloadLength > 0)
    {
        msg.payload.resize(
            payloadLength
        );

        recv(
            (SOCKET)socketFd,
            msg.payload.data(),
            payloadLength,
            MSG_WAITALL
        );
    }

    return msg;
}