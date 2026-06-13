#pragma once

#include <string>

#include "../bencode/BencodeValue.h"

class TorrentMetadata
{
public:

    std::string announce;
    std::string name;

    long long pieceLength = 0;

    std::string pieces;

    static TorrentMetadata fromBencode(
        const BencodeValue& root
    );

    void print() const;
};