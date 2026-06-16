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

    std::string getPieceHash(
        int index
    )const{
        const int HASH_SIZE = 20;

        return pieces.substr(
            index*HASH_SIZE,
            HASH_SIZE
        );
    }

    void print() const;
};