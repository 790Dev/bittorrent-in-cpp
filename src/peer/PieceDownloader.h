#pragma once

#include <vector>
#include <string>

class PieceDownloader
{
public:

    static std::vector<char> downloadPiece(
        int pieceIndex,
        int pieceLength
    );
};