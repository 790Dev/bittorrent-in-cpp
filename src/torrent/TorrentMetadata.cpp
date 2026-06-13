#include "TorrentMetadata.h"

#include <iostream>
#include <variant>

TorrentMetadata
TorrentMetadata::fromBencode(
    const BencodeValue& root
)
{
    TorrentMetadata metadata;

    auto rootDict =
        std::get<BencodeDict>(
            root.value
        );

    if(rootDict.count("announce"))
    {
        metadata.announce =
            std::get<std::string>(
                rootDict["announce"].value
            );
    }

    if(rootDict.count("info"))
    {
        auto infoDict =
            std::get<BencodeDict>(
                rootDict["info"].value
            );

        if(infoDict.count("name"))
        {
            metadata.name =
                std::get<std::string>(
                    infoDict["name"].value
                );
        }

        if(infoDict.count("piece length"))
        {
            metadata.pieceLength =
                std::get<long long>(
                    infoDict["piece length"].value
                );
        }

        if(infoDict.count("pieces"))
        {
            metadata.pieces =
                std::get<std::string>(
                    infoDict["pieces"].value
                );
        }
    }

    return metadata;
}

void TorrentMetadata::print() const
{
    std::cout << "\n";
    std::cout << "===== TORRENT METADATA =====\n";

    std::cout
        << "Name         : "
        << name
        << '\n';

    std::cout
        << "Tracker      : "
        << announce
        << '\n';

    std::cout
        << "Piece Length : "
        << pieceLength
        << '\n';

    std::cout
        << "Pieces Bytes : "
        << pieces.size()
        << '\n';
}