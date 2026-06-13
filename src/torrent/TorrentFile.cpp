#include "TorrentMetadata.h"

#include <iostream>
#include <variant>

TorrentMetadata TorrentMetadata::fromBencode(
    const BencodeValue& root
)
{
    TorrentMetadata metadata;

    auto rootDict =
        std::get<BencodeDict>(
            root.value
        );

    // announce
    if(rootDict.count("announce"))
    {
        metadata.announce =
            std::get<std::string>(
                rootDict["announce"].value
            );
    }

    // info dictionary
    auto infoDict =
        std::get<BencodeDict>(
            rootDict["info"].value
        );

    // name
    if(infoDict.count("name"))
    {
        metadata.name =
            std::get<std::string>(
                infoDict["name"].value
            );
    }

    // piece length
    if(infoDict.count("piece length"))
    {
        metadata.pieceLength =
            std::get<long long>(
                infoDict["piece length"].value
            );
    }

    // pieces
    if(infoDict.count("pieces"))
    {
        metadata.pieces =
            std::get<std::string>(
                infoDict["pieces"].value
            );
    }

    return metadata;
}

void TorrentMetadata::print() const
{
    std::cout << "\n===== TORRENT INFO =====\n";

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