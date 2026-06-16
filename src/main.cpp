#include <iostream>
#include <winsock2.h>

#include "torrent/TorrentFile.h"
#include "torrent/TorrentMetadata.h"
#include "torrent/InfoHashGenerator.h"

#include "tracker/TrackerClient.h"
#include "tracker/TrackerRequestBuilder.h"
#include "tracker/UrlEncoder.h"
#include "tracker/HttpResponse.h"
#include "tracker/TrackerResponseParser.h"

#include "peer/PeerIdGenerator.h"
#include "peer/PeerInfo.h"
#include "peer/PeerHandshake.h"
#include "peer/PeerSession.h"

#include "network/TcpClient.h"
#include "network/HttpsClient.h"

#include "peer/PeerMessage.h"
#include "peer/PeerMessageReceiver.h"
#include "peer/BitfieldParser.h"
#include "peer/InterestedMessage.h"
#include "peer/RequestMessage.h"
#include "peer/PieceMessage.h"
#include "peer/PieceDownloader.h"
#include "torrent/PieceHashVerifier.h"

int main()
{
    try
    {
        std::cout
            << "=====================================\n"
            << "       BitTorrent Client\n"
            << "=====================================\n\n";

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
            << "\n===== TRACKER REQUEST =====\n";

        std::cout
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

        HttpResponse response =
            HttpResponse::parse(
                rawResponse
            );

        response.print();

        if (response.statusCode == 200)
        {
            TrackerResponse trackerResponse =
                TrackerResponseParser::parse(
                    response.body
                );

            TrackerResponseParser::print(
                trackerResponse
            );

            if(!trackerResponse.peers.empty())
            {std::cout
    << "\n===== PEER TEST =====\n";

                    bool foundValidPeer = false;

                    for(
                        size_t i = 0;
                        i < trackerResponse.peers.size() &&
                        i < 10;
                        i++
                    )
                    {
                        PeerInfo peer;

                        peer.ip =
                            trackerResponse.peers[i].ip;

                        peer.port =
                            trackerResponse.peers[i].port;

                        peer.peerId =
                            trackerResponse.peers[i].peerId;

                        std::cout
                            << "\nTrying Peer "
                            << i + 1
                            << "/"
                            << trackerResponse.peers.size()
                            << '\n';

                        std::cout
                            << "Peer : "
                            << peer.ip
                            << ':'
                            << peer.port
                            << '\n';

                        bool connected =
                            PeerSession::connectToPeer(
                                peer
                            );

                        if(!connected)
                        {
                            std::cout
                                << "Connection failed\n";

                            continue;
                        }

                        std::cout
                            << "Connected\n";

                        bool sent =
                            PeerSession::sendHandshake(
                                peer,
                                binaryHash,
                                peerId
                            );

                        if(!sent)
                        {
                            std::cout
                                << "Handshake send failed\n";

                            PeerSession::disconnect();

                            continue;
                        }

                        std::cout
                            << "Handshake sent\n";

                        std::string peerResponse =
                            PeerSession::receiveBytes(
                                68
                            );

                        std::cout
                            << "Bytes received : "
                            << peerResponse.size()
                            << '\n';

                        bool valid =
                            PeerHandshake::validate(
                                peerResponse,
                                binaryHash
                            );

                        if(valid)
                        {
                            std::cout
                                << "Handshake VALID\n";

                            foundValidPeer = true;

                            bool gotBitfield = false;
                            bool gotUnchoke = false;

                            std::cout
                                << "\nWaiting for peer messages...\n";

                            while(true)
                            {
                                PeerMessage msg =
                                    PeerMessageReceiver::receive(
                                        PeerSession::getSocket()
                                    );

                                PeerMessageParser::print(
                                    msg
                                );

                                if(msg.length == 0)
                                {
                                    continue;
                                }

                                if(msg.id == 5)
                                {
                                    gotBitfield = true;

                                    std::string payload(
                                        msg.payload.begin(),
                                        msg.payload.end()
                                    );

                                    auto bitfield =
                                        BitfieldParser::parse(
                                            payload
                                        );

                                    BitfieldParser::print(
                                        bitfield
                                    );
                                }

                                if(msg.id == 1)
                                {
                                    gotUnchoke = true;
                                }

                                if(gotBitfield)
                                {
                                    break;
                                }
                            }

                            std::cout
                                << "\nSending INTERESTED...\n";

                            std::string interested =
                                InterestedMessage::build();

                            int sent =
                                send(
                                    (SOCKET)PeerSession::getSocket(),
                                    interested.data(),
                                    (int)interested.size(),
                                    0
                                );

                            if(sent > 0)
                            {
                                std::cout
                                    << "INTERESTED sent\n";
                            }
                            else
                            {
                                std::cout
                                    << "Failed to send INTERESTED\n";
                            }

                            if(!gotUnchoke)
                            {
                                std::cout
                                    << "\nWaiting for unchoke message...\n";

                                while(true)
                                {
                                    PeerMessage nextMessage =
                                        PeerMessageReceiver::receive(
                                            PeerSession::getSocket()
                                        );

                                    PeerMessageParser::print(
                                        nextMessage
                                    );

                                    if(nextMessage.length == 0)
                                    {
                                        continue;
                                    }

                                    if(nextMessage.id == 1)
                                    {
                                        gotUnchoke = true;
                                        break;
                                    }
                                }
                            }

                            if(gotUnchoke)
                            {
                                std::cout
                                    << "\nDownloading full piece 0...\n";

                                auto pieceData =
                                    PieceDownloader::downloadPiece(
                                        0,
                                        metadata.pieceLength
                                    );

                                std::cout
                                    << "Downloaded bytes : "
                                    << pieceData.size()
                                    << '\n';

                                std::string expectedHash =
                                    metadata.getPieceHash(
                                        0
                                    );

                                bool verified =
                                    PieceHashVerifier::verify(
                                        pieceData,
                                        expectedHash
                                    );

                                if(verified)
                                {
                                    std::cout
                                        << "PIECE VERIFIED\n";
                                }
                                else
                                {
                                    std::cout
                                        << "PIECE FAILED\n";
                                }
                            }

                            break;
                        }

                        std::cout
                            << "Handshake INVALID\n";

                        PeerSession::disconnect();
                    }

                    if(!foundValidPeer)
                    {
                        std::cout
                            << "\nNo responsive peer found.\n";
                    }
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