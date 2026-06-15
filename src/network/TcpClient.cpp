#include "TcpClient.h"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

std::string TcpClient::sendRequest(
    const std::string& host,
    int port,
    const std::string& request
)
{
    WSADATA wsaData;

    if(
        WSAStartup(
            MAKEWORD(2,2),
            &wsaData
        ) != 0
    )
    {
        throw std::runtime_error(
            "WSAStartup failed"
        );
    }

    struct addrinfo hints{};
    struct addrinfo* result = nullptr;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int status =
        getaddrinfo(
            host.c_str(),
            std::to_string(port).c_str(),
            &hints,
            &result
        );

    if(status != 0)
    {
        WSACleanup();

        throw std::runtime_error(
            "getaddrinfo failed"
        );
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

        throw std::runtime_error(
            "socket creation failed"
        );
    }

    if(
        connect(
            sock,
            result->ai_addr,
            static_cast<int>(
                result->ai_addrlen
            )
        ) == SOCKET_ERROR
    )
    {
        closesocket(sock);
        freeaddrinfo(result);
        WSACleanup();

        throw std::runtime_error(
            "connect failed"
        );
    }

    freeaddrinfo(result);

    send(
        sock,
        request.c_str(),
        static_cast<int>(
            request.size()
        ),
        0
    );

    char buffer[4096];

    std::string response;

    int bytesReceived;

    while(
        (bytesReceived =
            recv(
                sock,
                buffer,
                sizeof(buffer),
                0
            )) > 0
    )
    {
        response.append(
            buffer,
            bytesReceived
        );
    }

    closesocket(sock);

    WSACleanup();

    return response;
}