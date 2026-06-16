#include "PeerClient.h"

#include "PeerHandshake.h"

#include <winsock2.h>
#include <ws2tcpip.h>

std::string PeerClient::connectAndHandshake(
    const PeerInfo& peer,
    const std::string& infoHash,
    const std::string& peerId
)
{
    WSADATA wsa;

    WSAStartup(
        MAKEWORD(2,2),
        &wsa
    );

    addrinfo hints{};
    addrinfo* result = nullptr;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(
        peer.ip.c_str(),
        std::to_string(
            peer.port
        ).c_str(),
        &hints,
        &result
    );

    SOCKET sock =
        socket(
            result->ai_family,
            result->ai_socktype,
            result->ai_protocol
        );

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

        return "";
    }

    std::string handshake =
        PeerHandshake::build(
            infoHash,
            peerId
        );

    send(
        sock,
        handshake.data(),
        (int)handshake.size(),
        0
    );

    char buffer[1024];

    int received =
        recv(
            sock,
            buffer,
            sizeof(buffer),
            0
        );

    std::string response;

    if(received > 0)
    {
        response.assign(
            buffer,
            received
        );
    }

    closesocket(sock);

    freeaddrinfo(result);

    WSACleanup();

    return response;
}