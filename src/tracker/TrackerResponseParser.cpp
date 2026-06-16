#include "TrackerResponseParser.h"

#include "../bencode/BencodeParser.h"

#include <iostream>

TrackerResponse TrackerResponseParser::parse(
    const std::string& responseBody
)
{
    TrackerResponse result;

    size_t pos = 0;

    BencodeValue root =
        BencodeParser::parse(
            responseBody,
            pos
        );

    auto rootDict =
        std::get<BencodeDict>(
            root.value
        );

    if(rootDict.count("complete"))
    {
        result.complete =
            (int)std::get<long long>(
                rootDict["complete"].value
            );
    }

    if(rootDict.count("incomplete"))
    {
        result.incomplete =
            (int)std::get<long long>(
                rootDict["incomplete"].value
            );
    }

    if(rootDict.count("interval"))
    {
        result.interval =
            (int)std::get<long long>(
                rootDict["interval"].value
            );
    }

    if(rootDict.count("peers"))
    {
        auto peerList =
            std::get<BencodeList>(
                rootDict["peers"].value
            );

        for(const auto& peerValue : peerList)
        {
            auto peerDict =
                std::get<BencodeDict>(
                    peerValue.value
                );

            Peer peer;

            if(peerDict.count("ip"))
            {
                peer.ip =
                    std::get<std::string>(
                        peerDict["ip"].value
                    );
            }

            if(peerDict.count("port"))
            {
                peer.port =
                    (int)std::get<long long>(
                        peerDict["port"].value
                    );
            }

            if(peerDict.count("peer id"))
            {
                peer.peerId =
                    std::get<std::string>(
                        peerDict["peer id"].value
                    );
            }

            result.peers.push_back(
                peer
            );
        }
    }

    return result;
}

void TrackerResponseParser::print(
    const TrackerResponse& response
)
{
    std::cout
        << "\n===== TRACKER RESPONSE =====\n";

    std::cout
        << "Seeders    : "
        << response.complete
        << '\n';

    std::cout
        << "Leechers   : "
        << response.incomplete
        << '\n';

    std::cout
        << "Interval   : "
        << response.interval
        << '\n';

    std::cout
        << "Peers      : "
        << response.peers.size()
        << '\n';

    std::cout
        << "\n===== PEER LIST =====\n";

    int count = 0;

    for(const auto& peer : response.peers)
    {
        std::cout
            << peer.ip
            << " : "
            << peer.port
            << '\n';

        count++;

        if(count >= 10)
        {
            break;
        }
    }
}