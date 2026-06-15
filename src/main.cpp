#include <iostream>

#include "torrent/TorrentFile.h"
#include "torrent/TorrentMetadata.h"
#include "torrent/InfoHashGenerator.h"

#include "tracker/TrackerClient.h"
#include "tracker/TrackerRequestBuilder.h"
#include "tracker/UrlEncoder.h"
#include "tracker/HttpResponse.h"

#include "peer/PeerIdGenerator.h"

#include "network/TcpClient.h"
#include "network/HttpsClient.h"

int main()
{
    try
    {
        std::cout
            << "=====================================\n"
            << "       BitTorrent Client\n"
            << "=====================================\n\n";

        // CHANGE THIS PATH IF NEEDED
        std::string torrentPath =
            "../torrents/sample.torrent";

        std::cout
            << "Loading torrent: "
            << torrentPath
            << "\n\n";

        TorrentFile torrent;

        if (!torrent.load(torrentPath))
        {
            std::cerr
                << "Failed to load torrent file:\n"
                << torrentPath
                << '\n';

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

        std::string binaryHash =
            InfoHashGenerator::generate(
                root
            );

        std::string hexHash =
            InfoHashGenerator::generateHex(
                root
            );

        std::cout
            << "\n===== INFO HASH =====\n"
            << hexHash
            << '\n';

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
            << '\n';

        std::string encodedHash =
            UrlEncoder::encode(
                binaryHash
            );

        std::cout
            << "\n===== URL ENCODED HASH =====\n"
            << encodedHash
            << '\n';

        std::string request =
            TrackerRequestBuilder::build(
                tracker,
                encodedHash,
                peerId,
                12345
            );

        std::cout
            << "\n===== TRACKER REQUEST =====\n"
            << request
            << '\n';

        std::cout
            << "\n===== CONTACTING TRACKER =====\n";

        std::string rawResponse;

        if (tracker.isHttps)
        {
            rawResponse =
                HttpsClient::sendRequest(
                    tracker.host,
                    tracker.port,
                    request
                );
        }
        else
        {
            rawResponse =
                TcpClient::sendRequest(
                    tracker.host,
                    tracker.port,
                    request
                );
        }

        std::cout
            << "\n===== RAW RESPONSE =====\n"
            << rawResponse
            << '\n';

        HttpResponse response =
            HttpResponse::parse(
                rawResponse
            );

        response.print();

        std::cout
            << "\n=====================================\n"
            << "            Finished\n"
            << "=====================================\n";
    }
    catch(const std::exception& e)
    {
        std::cerr
            << "\nException: "
            << e.what()
            << '\n';
    }

    return 0;
}