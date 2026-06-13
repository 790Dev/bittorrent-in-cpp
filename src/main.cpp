#pragma once

#include <string>

struct TorrentMetadata
{
    std::string announce;
    std::string name;

    long long pieceLength;

    std::string pieces;
};