#include "PeerSession.h"

#include "PeerHandshake.h"

#include <winsock2.h>
#include <ws2tcpip.h>

int PeerSession::socketFd = -1;

bool PeerSession::connectToPeer(
    const PeerInfo& peer
)
{
    WSADATA wsa;

    if(
        WSAStartup(
            MAKEWORD(2,2),
            &wsa
        ) != 0
    )
    {
        return false;
    }

    addrinfo hints{};
    addrinfo* result = nullptr;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if(
        getaddrinfo(
            peer.ip.c_str(),
            std::to_string(
                peer.port
            ).c_str(),
            &hints,
            &result
        ) != 0
    )
    {
        WSACleanup();
        return false;
    }

    SOCKET sock =
        socket(
            result->ai_family,
            result->ai_socktype,
            result->ai_protocol
        );

    if(sock == INVALID_SOCKET)
    {
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    if(
        connect(
            sock,
            result->ai_addr,
            (int)result->ai_addrlen
        ) != 0
    )
    {
        closesocket(sock);
        freeaddrinfo(result);
        WSACleanup();
        return false;
    }

    socketFd = (int)sock;

    freeaddrinfo(result);

    return true;
}

bool PeerSession::sendHandshake(
    const PeerInfo& peer,
    const std::string& infoHash,
    const std::string& peerId
)
{
    std::string handshake =
        PeerHandshake::build(
            infoHash,
            peerId
        );

    int sent =
        send(
            (SOCKET)socketFd,
            handshake.data(),
            (int)handshake.size(),
            0
        );

    return sent ==
           (int)handshake.size();
}

std::string PeerSession::receiveBytes(
    int count
)
{
    std::string result;

    result.resize(count);

    int received =
        recv(
            (SOCKET)socketFd,
            result.data(),
            count,
            MSG_WAITALL
        );

    if(received <= 0)
    {
        return "";
    }

    result.resize(received);

    return result;
}

int PeerSession::getSocket()
{
    return socketFd;
}

void PeerSession::disconnect()
{
    if(socketFd != -1)
    {
        closesocket(
            (SOCKET)socketFd
        );

        socketFd = -1;
    }

    WSACleanup();
}