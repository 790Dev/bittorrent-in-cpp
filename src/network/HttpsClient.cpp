#include "HttpsClient.h"

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <winsock2.h>
#include <ws2tcpip.h>

#include <string>

std::string HttpsClient::sendRequest(
    const std::string& host,
    int port,
    const std::string& request
)
{
    WSADATA wsa;

    WSAStartup(
        MAKEWORD(2,2),
        &wsa
    );

    SSL_library_init();

    SSL_load_error_strings();

    const SSL_METHOD* method =
        TLS_client_method();

    SSL_CTX* ctx =
        SSL_CTX_new(method);

    if(!ctx)
    {
        WSACleanup();
        return "";
    }

    addrinfo hints{};
    addrinfo* result = nullptr;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo(
        host.c_str(),
        std::to_string(port).c_str(),
        &hints,
        &result
    );

    SOCKET sock =
        socket(
            result->ai_family,
            result->ai_socktype,
            result->ai_protocol
        );

    connect(
        sock,
        result->ai_addr,
        (int)result->ai_addrlen
    );

    SSL* ssl =
        SSL_new(ctx);

    SSL_set_fd(
        ssl,
        (int)sock
    );

    SSL_connect(ssl);

    SSL_write(
        ssl,
        request.c_str(),
        (int)request.size()
    );

    char buffer[4096];

    std::string response;

    int bytes;

    while(
        (bytes =
            SSL_read(
                ssl,
                buffer,
                sizeof(buffer)
            )
        ) > 0
    )
    {
        response.append(
            buffer,
            bytes
        );
    }

    SSL_shutdown(ssl);

    SSL_free(ssl);

    SSL_CTX_free(ctx);

    closesocket(sock);

    freeaddrinfo(result);

    WSACleanup();

    return response;
}