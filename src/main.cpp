#include <iostream>

#include "torrent/TorrentFile.h"
#include "torrent/TorrentMetadata.h"
#include "torrent/InfoHashGenerator.h"

#include "tracker/TrackerClient.h"
#include "tracker/UrlEncoder.h"
#include "tracker/TrackerRequestBuilder.h"
#include "tracker/HttpResponse.h"

#include "peer/PeerIdGenerator.h"

#include "network/TcpClient.h"

int main()
{
    try
    {
        std::cout
            << "=====================================\n"
            << "       BitTorrent Client\n"
            << "=====================================\n\n";

        TorrentFile torrent;

        if (!torrent.load("../torrents/sample.torrent"))
        {
            std::cerr
                << "Failed to load torrent file\n";

            return 1;
        }

        std::cout
            << "Torrent file loaded successfully\n";

        BencodeValue root =
            torrent.parse();

        std::cout
            << "Torrent file parsed successfully\n";

        TorrentMetadata metadata =
            TorrentMetadata::fromBencode(
                root
            );

        metadata.print();

        std::string infoHash =
            InfoHashGenerator::generate(
                root
            );

        std::cout
            << "\n===== INFO HASH =====\n"
            << infoHash
            << "\n";

        TrackerInfo tracker =
            TrackerClient::parseUrl(
                metadata.announce
            );

        TrackerClient::printInfo(
            tracker
        );

        std::string peerId =
            PeerIdGenerator::generate();

        std::cout
            << "\n===== PEER ID =====\n"
            << peerId
            << "\n";

        std::string encodedHash =
            UrlEncoder::encode(
                infoHash
            );

        std::cout
            << "\n===== URL ENCODED HASH =====\n"
            << encodedHash
            << "\n";

        std::string request =
            TrackerRequestBuilder::build(
                tracker,
                encodedHash,
                peerId,
                12345
            );

        std::cout
            << "\n===== TRACKER REQUEST =====\n";

        std::cout
            << request
            << "\n";

        std::cout
            << "\n===== CONTACTING TRACKER =====\n";

        std::string rawResponse =
            TcpClient::sendRequest(
                tracker.host,
                tracker.port,
                request
            );

        std::cout
            << "\n===== RAW RESPONSE =====\n";

        std::cout
            << rawResponse
            << "\n";

        HttpResponse response =
            HttpResponse::parse(
                rawResponse
            );

        response.print();

        if (response.statusCode == 302)
        {
            std::cout
                << "\n===== REDIRECT DETECTED =====\n";

            auto it =
                response.headers.find(
                    "Location"
                );

            if (it != response.headers.end())
            {
                std::cout
                    << "Redirect URL:\n"
                    << it->second
                    << "\n";
            }
        }

        std::cout
            << "\n=====================================\n"
            << "            Finished\n"
            << "\n=====================================\n";
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "\nException: "
            << e.what()
            << '\n';

        return 1;
    }

    return 0;
}