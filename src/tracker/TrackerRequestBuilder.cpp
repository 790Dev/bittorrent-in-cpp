#include "TrackerRequestBuilder.h"

std::string TrackerRequestBuilder::build(
    const TrackerInfo& tracker,
    const std::string& encodedInfoHash,
    const std::string& peerId,
    long long left
)
{
    std::string request;

    request +=
        "GET " +
        tracker.path +
        "?info_hash=" + encodedInfoHash +
        "&peer_id=" + peerId +
        "&port=6881"
        "&uploaded=0"
        "&downloaded=0"
        "&left=" + std::to_string(left) +
        "&compact=1"
        " HTTP/1.1\r\n";

    request +=
        "Host: " +
        tracker.host +
        "\r\n";

    request +=
        "Connection: close\r\n";

    request +=
        "\r\n";

    return request;
}